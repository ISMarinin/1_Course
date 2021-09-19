#include "functions.h"

int nextI(int i, int j, int l, int k) {
    int newI = (i + j + l) * (k + 1) % 25 - i * j * l * (k + 2) % 10 +10;
        return newI;
}
int nextJ(int i, int j, int l, int k) {
    int newJ = min((i + j + l) * (k + 3) % 25, i * j * l * (k + 4) % 25) + 10;
        return newJ;
}
int nextL(int i, int j, int l, int k) {
    int newL = 2 * sign(l) * abs((i + j + l) * (k + 5) % 10 - i * j * l * (k + 6) % 25);
        return newL;
}

bool checkInRing(int i, int j) {
    if (i <= 15 && i >= 5 && j <= -5 && j >= -15) {
        return true;
    }
    else {
        return false;
    }
}