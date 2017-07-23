/*
Knight Rider LED

Public Domain
September 2016,2017
Budi Rahardjo (@rahard)

*/

// pin configuration for DycodeX ESPectro board
int led[] = {15, 2, 0, 4, 5, 3};
// pin configuration for Arduino UNU board
// int led[] = {13, 12, 11, 10, 9, 8};
// pin config for NodeMCU
// int led[] = {14, 12, 13, 15, 3, 1};
// pin config for Wemos D1 mini
// int led[] = {2, 0, 4, 5, 3, 1};
//int led[] = {15, 13, 12, 14, 16};
int NUMLED = 6; // number of LEDS
int WAITFOR = 100;
int i;
int LEDON=0;
int direction=1;

void setup() {
   // setup pins for output
   for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
}

void loop() {

   // turn off all LED
   for (i=0; i<NUMLED; i++) { digitalWrite(led[i], LOW); }
   // turn on LED with current counter
   digitalWrite(led[LEDON], HIGH);

   delay(WAITFOR);

   LEDON = LEDON + direction;

   // if already hit the largest number, reverse direction
   if (LEDON >= NUMLED) { 
      direction = -1;
      LEDON = NUMLED - 1;
   }

   // if already hit the lowest number
   if (LEDON < 0) {
      direction = 1;
      LEDON = 0;
   }

}
