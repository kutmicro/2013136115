#include <WProgram.h> // RTC
#include <Wire.h>     // RTC
#include <DS1307.h>   // RTC
#include "DHT.h" 
 
#define DHTPIN 23       // 디지털 23번 온습도
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321 
 
DHT dht(DHTPIN, DHTTYPE); 

int rtc[7];         // RTC
int ledPin =  13; 
void setup() { 
   Serial.begin(9600); 
   Serial.println("DHTxx test!"); 
   dht.begin(); 

   DDRC|=_BV(2) |_BV(3);  // POWER:Vcc 
   PORTC |=_BV(3);  // VCC PINC3
   pinMode(ledPin, OUTPUT);  
   RTC.stop();
   RTC.set(DS1307_SEC,1);
   RTC.set(DS1307_MIN,57);
   RTC.set(DS1307_HR,17);
   RTC.set(DS1307_DOW,2);
   RTC.set(DS1307_DATE,18);
   RTC.set(DS1307_MTH,1);
   RTC.set(DS1307_YR,10);
   RTC.start();
  
 } 

void loop() { 
   delay(2000); 
   float t = dht.readTemperature(); 
   float f = dht.readTemperature(true); 
   if (isnan(t) || isnan(f)) { 
     Serial.println("Failed to read from DHT sensor!"); 
     return; 
   } 
   Serial.print("Temperature: "); 
   Serial.print(t); 
   Serial.print(" *C "); 

   RTC.get(rtc,true);
  for(int i=0; i<7; i++){
    Serial.print(rtc[i]);
    Serial.print(" ");
  }
  Serial.println();
  digitalWrite(ledPin, HIGH); 
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
 } 

