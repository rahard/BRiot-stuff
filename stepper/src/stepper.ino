/*
stepper example
2017 budi rahardjo

using: 28BY J-48 stepper motor + ULN2003

*/

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define TUNGGU 10 

int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

void setup() {
   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);
   Serial.begin(9600);
}

void halfstep(int x) {
   for (int i=0; i < 4 ; i++) {
      digitalWrite(IN1, bitRead(lookup[x],0));
      digitalWrite(IN2, bitRead(lookup[x],1));
      digitalWrite(IN3, bitRead(lookup[x],2));
      digitalWrite(IN4, bitRead(lookup[x],3));
   }
}


void maju() {
   Serial.println("counter clockwise");
   for (int i=0; i < 8 ; i++) {
      halfstep(i);
      delay(TUNGGU);
   }
}

void mundur() {
   Serial.println("clockwise");
   for (int i=7; i >= 0  ; i--) {
      halfstep(i);
      delay(TUNGGU);
   }
}

void loop() {
   int i;
   for (i=0; i < 200; i++) {
      maju();
   }
   delay(1000);
   for (i=0; i < 200; i++) {
      mundur();
   }
   delay(1000);
}
