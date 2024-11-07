/* blinking RGB LED 
   Budi Rahardjo @rahard
   2024
*/

// LED has 3 pins for each Red, Green, and Blue
// for WeMos D1 mini
#define R 2
#define G 0
#define B 4

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, HIGH);
  delay(1000);
}
