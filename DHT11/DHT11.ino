#include "DHT.h"

#define DHTPIN 7       // pin de datos del DHT11
#define DHTTYPE DHT11  // tipo de sensor

// DHT dht(pin, tipoDHT)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando DHT11...");
  dht.begin();  // inicia el sensor
}

void loop() {
  // DHT11: no leer más rápido de ~1 Hz
  delay(1500);  // 1.5 s entre lecturas para mayor estabilidad

  
  float h = dht.readHumidity();     // humedad relativa (%)
  float t = dht.readTemperature();  // temperatura (°C)
  float f = dht.readTemperature(true); // Fahrenheit

  // Verifica errores de lectura
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo al leer del DHT11 (NaN). Revisa cableado/alimentacion.");
    return;
  }

  Serial.print("Humedad: ");
  Serial.print(h, 1);
  Serial.print(" %  |  Temp: ");
  Serial.print(t, 1);
  Serial.print(" °C  (");
  Serial.print(f, 1);
  Serial.println(" °F)");
}
