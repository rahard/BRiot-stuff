/* Analog input */
/* rahard 2017 */

#include <ESPectro.h>
int Adata=0;

void setup() {
   Serial.begin(9600);
}

void loop() {
   //Adata = analogRead(A0);
   //Serial.println(Adata);
   Serial.println(analogRead(A0));
   delay(250);
}
