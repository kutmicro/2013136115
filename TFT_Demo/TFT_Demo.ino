// Example testing sketch for various DHT humidity/temperature sensors

// Written by ladyada, public domain
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

//#define DHTTYPE DHT21   // DHT 21 (AM2301)



// Connect pin 1 (on the left) of the sensor to +5V

// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1

// to 3.3V instead of 5V!

// Connect pin 2 of the sensor to whatever your DHTPIN is

// Connect pin 4 (on the right) of the sensor to GROUND

// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor



DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}
void loop() {
  delay(2000);
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;

  }



  // Compute heat index in Fahrenheit (the default)

  float hif = dht.computeHeatIndex(f, h);

  // Compute heat index in Celsius (isFahreheit = false)

  float hic = dht.computeHeatIndex(t, h, false);



  Serial.print("Humidity: ");

  Serial.print(h);

  Serial.print(" %\t");

  Serial.print("Temperature: ");

  Serial.print(t);

  Serial.print(" *C ");

  Serial.print(f);

  Serial.print(" *F\t");

  Serial.print("Heat index: ");

  Serial.print(hic);

  Serial.print(" *C ");

  Serial.print(hif);

  Serial.println(" *F");

}
