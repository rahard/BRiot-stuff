/*
This (useless?) code turns off all LEDs.

Public Domain
September 2016
Budi Rahardjo (@rahard)

*/

// pin configuration for DycodeX ESPectro board
int led[] = {15, 2, 0, 4, 5, 3};
// pin configuration for Arduino UNU board
// int led[] = {13, 12, 11, 10, 9, 8};

int i;
int NUMLED=6;

void setup() {
   // setup pins for output and reset with initial configuration
   for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
   for (i=0; i<NUMLED; i++) { digitalWrite(led[i], LOW); }
}

void loop() {
}
