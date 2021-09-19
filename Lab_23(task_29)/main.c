#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "function.h"

int main() {

    binTree bt;
    define(&bt);
    
    char symb;
    int data;

    while((symb = getchar()) != EOF) {

        if (symb == '+') {

            scanf(" %d", &data);
            add(&bt, data);
        
        }

        else if (symb == '-') {

            scanf(" %d", &data);
            delete(bt.root, data);

        }

        else if (symb == '?') {

            scanf(" %d", &data);
            if (search(bt.root, data))
                printf("Digit %d found\n", data);
            else
                printf("Digit %d not found\n", data);

        }

        else if(symb == 'f') {

            int count = CountOfLeaves(bt.root);
            printf("Count of leaves: %d\n", count);

        }

        else if (symb == 'p') { 

            printf("Traversing the tree in symmetric order: ");
            print(bt.root);
            printf("\n");

        }
    }

    destroy(bt.root);
    return 0;
}