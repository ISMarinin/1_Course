#include <stdio.h>
#include <cmath>
#include <climits>

typedef struct {
    unsigned arraySize;
    int n[(long long)log10(LLONG_MAX) + 1];
}Number;

Number Function(unsigned long long n) {
    Number numb = {.arraySize = 0};
   
    while (n > 0) {
        numb.n[numb.arraySize++] = n % 10;
        n /= 10;
    }
    return numb;
}

int main () {
    unsigned long long n;
    scanf ("%lld", &n);
    if (n > 0) {
    Number numb = Function(n);
    int temp;
    temp = numb.n[0];
    numb.n[0] = numb.n[numb.arraySize - 1];
    numb.n[numb.arraySize - 1] = temp;
    unsigned long long value = 0;
    for (int i = numb.arraySize - 1; i >= 0; --i) {
        value *= 10;
        value += numb.n[i];
    }
        printf ("%lld", value);
    }
    else if (n == 0) {
        printf ("You entered zeros");
    }
    printf ("\n");
    return 0;
}