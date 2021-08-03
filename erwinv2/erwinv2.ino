#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <DS3231.h>
#include <Wire.h>
#include "DHTesp.h" 
WiFiClient client;
 

#define DHTPIN 16
RTClib rtc;

const char* ssid = "sarjana_karatan";
const char* password = "12345678";

const char* host = "192.168.2.7";


#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


DHTesp dht;
SoftwareSerial SIM800L(13, 15);
int menit, jam;
//char c = ' ';
void setup() {
  //dht.setup(DHTPIN, DHTesp::DHTTYPE);
  Wire.begin(5, 4);
  SIM800L.begin(9600);
  Serial.begin(9600);

  while(WiFi.status() != WL_CONNECTED)
    {
      //progress sedang mencari WiFi
      delay(500);
      Serial.print(".");
    }
    Serial.println("Wifi Connected");
    Serial.println("IP Address : ");
    Serial.println(WiFi.localIP());

//  rtc.begin();
//  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));  //Setting Time
  //dht.begin();
}

void loop() {
  DateTime now = rtc.now();
  
  //kelembaban = dht.getHumidity();
  jam = now.hour(),DEC;
  //suhu = dht.getTemperature();
  menit=now.minute(),DEC;
  
  const int httpPort = 80;
  if(!client.connect(host, httpPort))
  {
     Serial.println("Connection Failed");
     return;
  }
   String Link;
    HTTPClient http;
    Link = "http://192.168.2.7/erwinproject/User1.php?temp=" + String(jam) + "&hum=" + String(menit);
    http.begin(client,Link);
    delay(1000);
}
void konekWifi(){
 //cek koneksi wifi
    while(WiFi.status() != WL_CONNECTED)
    {
      //progress sedang mencari WiFi
      delay(500);
      Serial.print(".");
    }
    Serial.println("Wifi Connected");
    Serial.println("IP Address : ");
    Serial.println(WiFi.localIP());
    
}

void getToServer(){
  SIM800L.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  toSerial();
  delay(800);

  SIM800L.println("AT+SAPBR=3,1,\"APN\",\"Internet\"");
  toSerial();
  delay(800);

  SIM800L.println("AT+SAPBR=3,1,\"PWD\",\"\"");
  toSerial();
  delay(800);

  SIM800L.println("AT+SAPBR=1,1");
  toSerial();
  delay(1000);

  SIM800L.println("AT+SAPBR=2,1");
  toSerial();
  delay(1000);

  SIM800L.println("AT+HTTPINIT");
  toSerial();
  delay(1000);

//masukan url website
  SIM800L.print("AT+HTTPPARA=\"URL\",\"http://192.168.2.7/erwinproject/User1.php?temp=" + String(jam) + "&hum=" + String(menit));
  SIM800L.println("\"");
  toSerial();
  delay(1000);

  // 0 = GET, 1 = POST, 2 = HEAD
  SIM800L.println("AT+HTTPACTION=0");
  delay(3000);
  toSerial();

  SIM800L.println("");
  delay(100);

  SIM800L.println("AT+HTTPTERM");
  delay(800);
  toSerial();
}
void toSerial()
{
  while (SIM800L.available() != 0)
  {
    Serial.write(SIM800L.read());
  }
}
