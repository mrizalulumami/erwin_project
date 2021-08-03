#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
#define tahun now.year()
#define bulan now.month()
#define tanggal now.day()
#define hari daysOfTheWeek[now.dayOfTheWeek()]
#define jam now.hour()
#define menit now.minute()
#define detik now.second()

LiquidCrystal_I2C lcd(0x27, 16,2);  // Set the LCD I2C address
char buff[10];

void setup() 
{
  Serial.begin(9600);
 
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight();
  delay(10000);
  
}

void loop() 
{
  DateTime now = rtc.now();
  
  lcd.clear ();
  
  if (jam < 10 && menit < 10) {
    sprintf (buff, "0%d:0%d", jam, menit);
  }
  else  if (jam < 10 && menit >= 10) {
    sprintf (buff, "0%d:%d", jam, menit);
  }
  else  if (jam >= 10 && menit < 10) {
    sprintf (buff, "%d:0%d", jam, menit);
  }
  else  if (jam >= 10 && menit >= 10) {
    sprintf (buff, "%d:%d", jam, menit);
  }
  
  lcd.setCursor (5, 0);
  lcd.print(buff);
  
  if (tanggal < 10 && bulan < 10) {
    sprintf (buff, "0%d-0%d-%d", tanggal, bulan, tahun);
  }
  else  if (tanggal < 10 && bulan >= 10) {
    sprintf (buff, "0%d-%d-%d", tanggal, bulan, tahun);
  }
  else  if (tanggal >= 10 && bulan < 10) {
    sprintf (buff, "%d-0%d-%d", tanggal, bulan, tahun);
  }
  else  if (tanggal >= 10 && bulan >= 10) {
    sprintf (buff, "%d-%d-%d", tanggal, bulan, tahun);
  }
  
  lcd.setCursor(3, 1);
  lcd.print(buff);
  Serial.println(buff);
  delay(100);
}
