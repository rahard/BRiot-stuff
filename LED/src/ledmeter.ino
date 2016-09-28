/*
LED Meter

Public Domain
September 2016
Budi Rahardjo (@rahard)

*/

// pin configuration for DycodeX ESPectro board
int led[] = {15, 2, 0, 4, 5, 3};
// pin configuration for Arduino UNU board
// int led[] = {13, 12, 11, 10, 9, 8};
int NUMLED = 6; // number of LEDS
int WAITFOR = 100;
int i;
int LEDON=0;

void setup() {
   // setup pins for output
   for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
}

void display(int n) {
   // protection
   if (n < 0) { n = 0; }
   if (n > NUMLED) { n = NUMLED; }

   // turn off all LED first
   for (i=0; i<NUMLED; i++) { digitalWrite(led[i], LOW); }

   // turn on LED from 1 to n; 0 means do not display
   for (i=1; i<=n; i++) {
      digitalWrite(led[i-1], HIGH);
   }
}

void loop() {
   int j;
   // increment
   for (j=0; j < NUMLED; j++) {
      display(j);
      delay(WAITFOR);
   }
   for (j=NUMLED; j >= 0; j--) {
      display(j);
      delay(WAITFOR);
   }
}
