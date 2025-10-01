const int trigPin = 12; 
const int echoPin = 11; 

void setup() {
  
  //pinMode(pin, configuración)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  long duration = pulseIn(echoPin, HIGH);

  float distance = duration * 0.034 / 2; 
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(2000);
}