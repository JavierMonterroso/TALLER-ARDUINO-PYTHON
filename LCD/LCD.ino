#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Cambia 0x27 por 0x3F si tu LCD usa esa dirección
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();          
  lcd.backlight();
  lcd.clear();

  // Línea 1
  lcd.setCursor(2, 0);     // columna 2, fila 0
  lcd.print("Bienvenidos");

  // Línea 2
  lcd.setCursor(0, 1);     // columna 0, fila 1
  lcd.print("Taller Arduino");
}

void loop() {
  // No hace falta nada: el mensaje queda fijo
}