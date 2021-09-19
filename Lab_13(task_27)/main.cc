#include <stdio.h>
#include "function.h"

int main() {
    char smb;

    struct Bitset bs;
    init (&bs);

    addElement (&bs, 'a');
    addElement (&bs, 'u');
    addElement (&bs, 'e');
    addElement (&bs, 'o');
    addElement (&bs, 'i');

    Bitset word;
    init(&word);

    char masWord[100];
    int i = 0;
    bool flag = false;

    printf ("Слова, содерщие все гласные: ");
    
    do {
        smb = getchar();
        addElement(&word, lowRegister(smb));
        masWord[i] = smb;
        i++;
        
        if (smb == ' ' || smb == '\n' || smb == EOF) {
            if (check(&word, bs)) {
                for (int j = 0; j < i - 1; ++j) {
                    printf("%c", masWord[j]);
                }
                printf (" ");
                flag = true;
            }
            init(&word);
            i = 0;
        }

    } while (smb != EOF);

    if (flag == false) {
        printf ("отсутствуют.");
    }
    printf ("\n");
    
    return 0;
}