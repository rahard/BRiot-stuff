// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
 
#define trigPin 20
#define echoPin 19
 
long duration;
int distance;
 
 
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(2000);
  Serial.begin(9600);
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
 
  distance = duration*0.034/2;
 
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
 
}
