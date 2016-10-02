#include <stdio.h>

/* Rotate LED - BR @rahard */

int LEN = 6;
int LED[] = {0,0,0,0,0,1};

void rotateleft() {
   int i;
   int temp;
   temp = LED[0];
   for (i=0; i<LEN-1; i++) { LED[i] = LED[i+1]; }
   LED[LEN-1] = temp;
}

void rotateright() {
   int i;
   int temp;
   temp = LED[LEN-1];
   for (i=LEN-1; i > 0; i--) { LED[i]=LED[i-1]; }
   LED[0]=temp;
}

void display() {
   int i;
   for (i=0; i<LEN; i++) {
      printf("%d ", LED[i]);
   }
   printf("\n");
}

int main() {
   int i;
   for (i=0; i < 10; i++) {
      display();
      /*rotateleft();*/
      rotateright();
   }
}
