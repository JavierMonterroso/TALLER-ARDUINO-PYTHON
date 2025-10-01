#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// ==========================
// Configuración del DHT11
// ==========================
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ==========================
// Configuración del ultrasónico
// ==========================
const int trigPin = 12;
const int echoPin = 11;

// ==========================
// Configuración LCD I2C
// ==========================
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // LCD
  lcd.init();
  lcd.backlight();

  // Serial (para Python)
  Serial.begin(9600);
  delay(1000);                 // pequeño tiempo para que el puerto esté listo
  Serial.println("temp,hum,dist"); // <-- encabezado opcional

  // Sensores
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema listo!");
  delay(2000);
}

void loop() {
  // ===== Lectura DHT11 =====
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error DHT11");
    delay(2000);
    return;
  }

  // ===== Lectura ultrasónico =====
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000UL); // timeout 30 ms por si no hay eco
  float distance = (duration == 0) ? NAN : (duration * 0.034f / 2.0f);

  // ======= ENVÍO A PYTHON (CSV) =======
  // Formato: temp,hum,dist
  // Ejemplo: 24.6,58.2,123.4
  if (isnan(distance)) {
    Serial.print(t, 1); Serial.print(',');
    Serial.print(h, 1); Serial.println(",NaN");
  } else {
    Serial.print(t, 1); Serial.print(',');
    Serial.print(h, 1); Serial.print(',');
    Serial.println(distance, 1);
  }

  // ======= Mostrar en LCD (5 s c/u) =======
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(t, 1); lcd.print((char)223); lcd.print("C");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humedad:");
  lcd.setCursor(0, 1);
  lcd.print(h, 1); lcd.print(" %");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
  lcd.setCursor(0, 1);
  if (isnan(distance)) {
    lcd.print("--");
  } else {
    lcd.print(distance, 1); lcd.print(" cm");
  }
  delay(5000);
}
