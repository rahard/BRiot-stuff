/*
Enter - Exit

Public Domain
September 2016
Budi Rahardjo (@rahard)

*/

// pin configuration for DycodeX ESPectro board
int led[] = {15, 2, 0, 4, 5, 3};
// pin configuration for Arduino UNU board
// int led[] = {13, 12, 11, 10, 9, 8};

int x[] = {0, 0, 0, 0, 0, 0};
int NUMLED = 6; // number of LEDS
int WAITFOR = 100;
int i;

void setup() {
   // setup pins for output and reset low
   for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
   for (i=0; i<NUMLED; i++) { digitalWrite(led[i], LOW); }
}

void display() {
   for (i=0; i < NUMLED ; i++) {
      digitalWrite(led[i], x[i]);
   }
}

void loop() {
   int j;
   // populate LED
   for (j=0; j<NUMLED; j++) {
      x[j]=1;
      display();
      delay(WAITFOR);
   }
   // unpopulate LED
   for (j=0; j<NUMLED; j++) {
      x[j]=0;
      display();
      delay(WAITFOR);
   }

}
