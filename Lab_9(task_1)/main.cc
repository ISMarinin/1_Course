#include <stdio.h>
#include "functions.h"

int main() {
    int i = -11;
    int j = -6;
    int l = -5;
    int newI;
    int newJ;
    int newL;
    for (int k = 0; k <= 50; ++k) {
        newI = nextI(i, j, l, k);
        newJ = nextJ(i, j, l, k);
        newL = nextL(i, j, l, k);
        
        i = newI;
        j = newJ;
        l = newL;

        if (checkInRing(i, j) == true) {
            printf ("%s", "Hitting the target\n");
            printf ("Number of steps: %d\n", k);
            printf ("The final coordinates: %d, %d\n", i, j);
            printf ("Value of the dynamic motion parameter: %d\n", l);
            return 0;
        }
    }
    printf ("%s", "Blunder\n");
    return 0;
}    