#include <stdio.h>

/* enter-exit LED - BR @rahard */

int LEN = 6;
int LED[] = {0,0,0,0,0,0};


void display() {
   int i;
   for (i=0; i<LEN; i++) {
      printf("%d ", LED[i]);
   }
   printf("\n");
}

int main() {
   int i;
   display();
   // populate the LED
   for (i=0; i < LEN; i++) {
      LED[i]=1;
      display();
   }
   // unpopulate the LED
   for (i=0; i<LEN; i++) {
      LED[i]=0;
      display();
   }
}
