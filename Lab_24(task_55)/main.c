#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "functions.h"

int main() {
    Stack main;
    Stack operations;
    initStack(&main);
    initStack(&operations);

    char symb;
    bool n = false;

    Token numb;
    Token act;
    Token val;

    bool flag = true;
    bool lasBKT = false;

    while (flag) {

        symb = getchar();
        
        if (symb == EOF) {
        
            flag = false;
        
            if (n) push(&main, numb);
        
            while(operations.size > 0) {
        
                push(&main, pop(&operations));
        
            }
        }

        else {
            if (!n) {
                if (symb >= '0' && symb <= '9') {
                    n = true;
                    numb.tokentype = 1;
                    numb.variable = symb - '0';
                }
                if (symb >= 'a' && symb <= 'z') {
                    val.tokentype = 2;
                    val.operator = symb;
                    push(&main, val);
                }
                if ((symb >= '*' && symb <= '/') || symb == '^') {
                    if (operations.size == 0) {
                        act.operator = symb;
                        act.tokentype = 0;
                        push(&operations, act);
                    }
                    else {
                        while (operations.size > 0 && operationPriority(peak(&operations).operator) >=
                        operationPriority(symb) && peak(&operations).operator != '(') {
                            push(&main, pop(&operations));    
                        }
                        act.operator = symb;
                        act.tokentype = 0;
                        push(&operations, act);
                    }
                }

                if (symb == '(') {
                    act.operator = symb;
                    act.tokentype = 0;
                    push (&operations, act);
                }
                if (symb == ')') {
                    lasBKT = true;
                    while (peak(&operations).operator != '(') {
                        push(&main, pop(&operations));
                    }
                    pop(&operations);
                }
            }
            else {
                if (symb >= '0' && symb <= '9') {
                    numb.variable *= 10;
                    numb.variable += (symb - 48);
                }

                if ((symb >= '*' && symb <= '/') || symb == '^') {
                    push(&main, numb);
                    n = false;

                    if (operations.size == 0) {
                        act.operator = symb;
                        act.tokentype = 0;
                        push(&operations, act);
                    }
                    else {
                        while (operations.size > 0 && operationPriority(peak(&operations).operator) >= operationPriority(symb) && 
                        peak(&operations).operator != 40) {
                            push(&main, pop(&operations));
                        }
                        act.operator = symb;
                        act.tokentype = 0;
                        push(&operations, act);
                    }
                }
                if (symb == '(') {
                    push(&main, numb);
                    n = false;
                    act.operator = symb;
                    act.tokentype = 0;
                    push(&operations, act);
                }
                if (symb == ')') {
                    push(&main, numb);
                    n = false;
                    lasBKT = true;

                    while(peak(&operations).operator != '(') {
                        push(&main, pop(&operations));
                    }
                    pop(&operations);
                }
            }
        }
    }

    if (main.size > 0) {
        printf("Stack > ");
        printStack(&main);
        Tree tr;
        defineTree(&tr);
        insert(&tr, &main);
        // printf("\nInput > ");
        // printTree(tr.root);
        printf("\nTask  > ");
        Task(tr.root);
        destroy(tr.root);
    }
    free(main.nodes);
    free(operations.nodes);
    printf("\n");
}