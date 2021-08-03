
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define serv 16

Servo myservo;

LiquidCrystal_I2C lcd(0x27,20,16);

#define triggerPin_1 0
#define echoPin_1 2

unsigned int duration_1;
unsigned int distance_1;

#define triggerPin_2 13
#define echoPin_2 15

unsigned int duration_2;
unsigned int distance_2;


void setup() {
  Serial.begin(115200);
  myservo.attach(serv);

  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.noCursor();
  Wire.begin();
  
  pinMode(triggerPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(triggerPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  
}
void loop() {
  myservo.write(180);
  readSensor_1();
  readSensor_2();
  
  Serial.println(" ");
  delay(100);
}
void readSensor_1() {
  digitalWrite(triggerPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin_1, LOW);
  duration_1 = pulseIn(echoPin_1, HIGH);
  distance_1 = (duration_1 / 2) / 28.5;
  Serial.print("Sensor 1 = ");
  Serial.print(distance_1);
  Serial.println(" cm");
  
  lcd.setCursor(0, 0);
  lcd.print(distance_1);
  lcd.print(" cm");
  
}
void readSensor_2() {
  digitalWrite(triggerPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin_2, LOW);
  duration_2 = pulseIn(echoPin_2, HIGH);
  distance_2 = (duration_2 / 2) / 28.5;
  Serial.print("Sensor 2 = ");
  Serial.print(distance_2);
  Serial.println(" cm");
  
  lcd.setCursor(0, 1);
  lcd.print(distance_2);
  lcd.print(" cm");
}
