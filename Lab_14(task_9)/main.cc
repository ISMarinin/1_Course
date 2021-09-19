#include <stdio.h>
#include "function.h"

int main() {
    int matr[MaxSize][MaxSize];
    unsigned n;
    scanf ("%d", &n);
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            scanf ("%d", &matr[i][j]);
        }
    }
    unsigned currentI = n - 1;
    unsigned currentJ = 0;
    State currentState = Start;
    while (currentState != Finish) {
        if (currentState == MoveUp) {
            --currentI;
        }
        else if (currentState == DownDiagonally) {
            ++currentJ;
            ++currentI;
        }
        else if (currentState == MoveRight) {
            ++currentJ;
        }
        else if (currentState == UpDiagonally) {
            --currentI;
            --currentJ;
        }
    printf ("%d ", matr[currentI][currentJ]);
    // printf ("\n");
    // printf ("%d\n", currentState);
    currentState = NextState(currentState, currentI, currentJ, n);
    }
    printf ("\n");
    return 0;
}