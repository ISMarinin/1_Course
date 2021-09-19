#include <stdio.h>
#include "functions.h"

int main() {
    char smb;
    State currentState = Start;
    unsigned int wordsCount = 0;

    do  {
        smb = getchar();
        currentState = fsm(currentState, smb);
        
         if (currentState == EndWord || currentState == NewLine || currentState == End) {
           ++wordsCount;
        }
   } while (smb != EOF);
       
   printf("%u\n", wordsCount);
   return 0;
}