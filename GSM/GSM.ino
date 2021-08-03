#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <DS3231.h>
#include <Wire.h>
#include "DHTesp.h"


#define DHTPIN 16
RTClib rtc;


#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

String apn = "internet";
DHTesp dht;
SoftwareSerial SIM800L(13, 15);
int menit, jam;
//char c = ' ';
void setup() {
  //dht.setup(DHTPIN, DHTesp::DHTTYPE);
  Wire.begin(5, 4);
  SIM800L.begin(9600);
  Serial.begin(115200);

  //  rtc.begin();
  //  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));  //Setting Time
  //dht.begin();
}

void loop() {
  DateTime now = rtc.now();

  //kelembaban = dht.getHumidity();
  jam = now.hour();
  //suhu = dht.getTemperature();
  menit = now.minute();
  //  if (isnan(jam) || isnan(menit)) {
  //    Serial.println("Failed to read from DHT sensor!");
  //    return;
  //  }else{
  //    Serial.println("====Read Sensor====");
  //    Serial.print("Jam = ");
  //    Serial.print(jam);
  //    Serial.println(" ");
  //    Serial.print("Kelembaban = ");
  //    Serial.print(menit);
  //    Serial.println(" ");
  //    Serial.println("====Send to Server====");
  //    getToServer();
  //  }

  SetupModule();
  //https://rizalduinocrud.000webhostapp.com/User1.php
  SIM800L.println("AT+CIPSTART=\"TCP\",\"rizalduinocrud.000webhostapp.com\",\"80\"");
  delay(3000);
  ShowSerialData();

  SIM800L.println("AT+CIPSEND");
  delay(2000);
  Serial.println();
  ShowSerialData();
  //ReadSensor();
  String str = "GET https://rizalduinocrud.000webhostapp.com/User1.php?temp=20&hum=10";
  Serial.println(str);  delay(2000);
  SIM800L.println(str); delay(4000);
  ShowSerialData();

  SIM800L.println((char)26); delay(4000);
  SIM800L.println();
  ShowSerialData();
  SIM800L.println("AT+CIPSHUT");//close the connection
  delay(500);
  ShowSerialData();
  str = "";

  //total delay looping 50s
  delay(10000); //add 10s for 60s total delay looping
}

//
void SetupModule() {
  if (SIM800L.available())Serial.write(SIM800L.read());
  SIM800L.println("AT"); delay(1000);
  SIM800L.println("AT+CPIN?"); delay(1000);
  SIM800L.println("AT+CREG?"); delay(1000);
  SIM800L.println("AT+CGATT?"); delay(1000);
  SIM800L.println("AT+CIPSHUT"); delay(1000);
  SIM800L.println("AT+CIPSTATUS"); delay(2000);
  SIM800L.println("AT+CIPMUX=0");  delay(2000);

  //setting the APN,
  SIM800L.println("AT+CSTT=\"" + apn + "\""); delay(1000);
  ShowSerialData();
  SIM800L.println("AT+CIICR");    delay(2000);
  ShowSerialData();

  //get local IP adress
  SIM800L.println("AT+CIFSR");    delay(2000);
  ShowSerialData();

  SIM800L.println("AT+CIPSPRT=0"); delay(2000);
  ShowSerialData();
}

void ShowSerialData() {
  while (SIM800L.available() != 0)
    Serial.write(SIM800L.read());
  delay(2000);
}


//void getToServer(){
//  SIM800L.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
//  toSerial();
//  delay(800);
//
//  SIM800L.println("AT+SAPBR=3,1,\"APN\",\"Internet\"");
//  toSerial();
//  delay(800);
//
//  SIM800L.println("AT+SAPBR=3,1,\"PWD\",\"\"");
//  toSerial();
//  delay(800);
//
//  SIM800L.println("AT+SAPBR=1,1");
//  toSerial();
//  delay(1000);
//
//  SIM800L.println("AT+SAPBR=2,1");
//  toSerial();
//  delay(1000);
//
//  SIM800L.println("AT+HTTPINIT");
//  toSerial();
//  delay(1000);
//
////masukan url website
//  SIM800L.print("AT+HTTPPARA=\"URL\",\"http://rizalduinocrud.000webhostapp.com/User1.php?temp=" + String(jam) + "&hum=" + String(menit));
//  SIM800L.println("\"");
//  toSerial();
//  delay(1000);
//
//  // 0 = GET, 1 = POST, 2 = HEAD
//  SIM800L.println("AT+HTTPACTION=0");
//  delay(3000);
//  toSerial();
//
//  SIM800L.println("");
//  delay(100);
//
//  SIM800L.println("AT+HTTPTERM");
//  delay(800);
//  toSerial();
//}
