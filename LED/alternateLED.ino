/*
This is an alternating blinking LEDs demo
1 0 1 0 1 0
0 1 0 1 0 1

Done for ESPectro board, but can be used by other boards.
Just change the pin definition

This code is in public domain
26 Sep 2016
Budi Rahardjo (@rahard)
*/

// pin definition of ESPectro board
// I am connecting this to ProcodeCG LED board
// thus, this pin configuration
uint8_t BRD1 = 15;
uint8_t BRD2 = 2;
uint8_t BRD3 = 0;
uint8_t BRD4 = 4;
uint8_t BRD5 = 5;
uint8_t BRD6 = 3;

int TUNGGU = 500;


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(BRD1, OUTPUT);
  pinMode(BRD2, OUTPUT);
  pinMode(BRD3, OUTPUT);
  pinMode(BRD4, OUTPUT);
  pinMode(BRD5, OUTPUT);
  pinMode(BRD6, OUTPUT);
}

void loop() {
  digitalWrite(BRD1, HIGH);
  digitalWrite(BRD2, LOW);
  digitalWrite(BRD3, HIGH);
  digitalWrite(BRD4, LOW);
  digitalWrite(BRD5, HIGH);
  digitalWrite(BRD6, LOW);
  delay(TUNGGU);

  digitalWrite(BRD1, LOW);
  digitalWrite(BRD2, HIGH);
  digitalWrite(BRD3, LOW);
  digitalWrite(BRD4, HIGH);
  digitalWrite(BRD5, LOW);
  digitalWrite(BRD6, HIGH);
  delay(TUNGGU);
}
