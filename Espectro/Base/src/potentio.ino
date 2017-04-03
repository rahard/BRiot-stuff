/* Analog input */
/* rahard 2017 */

#include <ESPectro.h>


int Adata=0;
int i=0;

void setup() {
   Serial.begin(9600);
}

void loop() {
   for (i=0; i<18; i++) {
      Adata= analogRead(i);
      Serial.print(i);
      Serial.print(" ");
      Serial.println(Adata);
      delay(250);
      }
}
