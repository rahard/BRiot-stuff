/*
simple buttons tester

there are 4 buttons in procodecg key board
read each one of them, and send them to the LEDs
no debounce yet. just straight through

2016, public domain
Budi Rahardjo (@rahard)
*/

// pin configuration for Arduino UNU board + ProcodeCG LED
int led[] = {7, 6, 5, 4, 3, 2};
//int key[] = {11, 10, 9, 8};
int key[] = {13, 12, 11, 10};
int but[] = {0, 0, 0, 0, 0, 0};
int NUMLED=6;
int NUMKEY=4;
int i;

void setup() {
   for (i=0; i<NUMKEY; i++) { pinMode(key[i], INPUT); }
   for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
}

void loop() {
   // read buttons/keys
   for (i=0; i<NUMKEY; i++) { but[i]=digitalRead(key[i]); }
   // send them to LEDs directly, no debounce
   for (i=0; i<NUMLED; i++) { digitalWrite(led[i], but[i]); }
}
