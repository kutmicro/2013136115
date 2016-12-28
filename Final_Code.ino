#include <DHT.h>
#include "DHT.h"       // DHT.h 라이브러리를 포함한다
#define DHTPIN 21      // DHT핀을 21번으로 정의한다(DATA핀)
#define DHTTYPE DHT11  // DHT타입을 DHT11로 정의한다

DHT dht(DHTPIN, DHTTYPE);  // DHT설정 - dht (디지털21, dht11)

#include <Arduino.h>
#include <Wire.h>         
#include "RTClib.h"

#if defined(ARDUINO_ARCH_SAMD)
  #define Serial SerialUSB
#endif

RTC_Millis rtc;


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "OpenCR_ILI9341.h"


// For the Adafruit shield, these are the default.
#define TFT_DC    15
#define TFT_CS    14
#define TFT_MOSI  18
#define TFT_MISO  19
#define TFT_CLK   17
#define TFT_RST   16

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#include <MusicPlayer.h>
#include <SD.h>
#include <SPI.h>

void setup () {
  Serial.begin(115200);
    
  while(!Serial);
   
  // 그래픽 lcd 실행
  Serial.println("ILI9341 Test!");
  tft.begin();

  // rtc 모듈 컴퓨터시간으로 설정
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));

  // music shield 시작
  player.begin(); 
  
  //PM_NORMAL_PLAY = 0 , PM_SHUFFLE_PLAY = 1,  PM_REPEAT_LIST = 2, PM_REPEAT_ONE = 3
  player.setPlayMode(PM_NORMAL_PLAY); // 순차적으로 재생
  player.scanAndPlayAll(); // PlayList 작성

}

void loop () {
    DateTime now = rtc.now();

  int h = dht.readHumidity();  // 변수 h에 습도 값을 저장 
  int t = dht.readTemperature();  // 변수 t에 온도 값을 저장

  unsigned long start = micros();
  tft.setCursor(0, 0);            // 커서위치 설정
  tft.fillScreen(ILI9341_BLACK);  // 바탕색 검정
  tft.setRotation(3);             // 가로화면 출력
  tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(3);  // 글자색 노랑, 글자크기 3

  // 시간 그래픽 lcd 출력
  Serial.print("Time ");
  tft.print("\n");
  tft.print(" Time : ");
  tft.print(now.hour());
  tft.print(":");
  tft.print(now.minute());
  tft.print(":");
  tft.print(now.second());
  tft.print("\n");

  // 온습도 그래픽 lcd 출력
Serial.print("Temerature ");
  tft.print(" Temerature : ");
  tft.print(t);
  tft.println("C" );
  tft.print(" Humidity : ");
  tft.print(h);
  tft.println("%");


    Serial.println();
   // delay(1000);
    player.play();
} 

