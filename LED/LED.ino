const int ledPin = 8;  // Pin donde conectamos el LED

void setup() {
  pinMode(ledPin, OUTPUT);  // Configuramos el pin como salida
}

void loop() {
  digitalWrite(ledPin, HIGH);  // Encender LED
  delay(1000);                 // Esperar 1 segundo
  digitalWrite(ledPin, LOW);   // Apagar LED
  delay(1000);                 // Esperar 1 segundo
}