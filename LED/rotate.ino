/*
This code rotates the LED display
If we initialized with only one "1", it's just ordinary.
Try with two "1"s in the array. Change the code

Public Domain
September 2016
Budi Rahardjo (@rahard)

*/

// pin configuration for DycodeX ESPectro board
int led[] = {15, 2, 0, 4, 5, 3};
// pin configuration for Arduino UNU board
// int led[] = {13, 12, 11, 10, 9, 8};

// x is the content to be rotated, try with the different number of "1"s
int x[] = {0, 0, 0, 0, 1, 1};
int NUMLED = 6; // number of LEDS
int WAITFOR = 500;
int i;

void setup() {
   // setup pins for output and reset with initial configuration
   for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
   for (i=0; i<NUMLED; i++) { digitalWrite(led[i], x[i]); }
}

void display() {
   for (i=0; i < NUMLED ; i++) {
      digitalWrite(led[i], x[i]);
   }
}

void rotateleft() {
   int j;
   int temp;
   temp = x[0];
   for (j=0; j<NUMLED-1; j++) { x[j] = x[j+1]; }
   x[NUMLED-1] = temp;
}

void rotateright() {
   int j;
   int temp;
   temp = x[NUMLED-1];
   for (j=NUMLED-1; j>0 ; j--) {x[j] = x[j-1]; }
   x[0] = temp;
}

void loop() {
   display();
   delay(WAITFOR);
   // rotateleft();
   rotateright();
}
