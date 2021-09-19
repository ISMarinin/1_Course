#include "functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void initStack(Stack* s) {

    s->capacity = 2;
    s->size = 0;
    s->nodes = (Token*)malloc(sizeof (Token)*s->capacity);

}

void push(Stack* s, Token element) {

    if (s->size == s->capacity) {

        s->capacity *= 2;
        s->nodes = (Token*)realloc(s->nodes, sizeof (Token)*s->capacity);

    }

    if (s->size == 0) {

        s->nodes[s->size] = element;
        s->size++;

    } 
    else {

        for (int i = s->size ; i > 0; i--) {

            s->nodes[i] = s->nodes[i-1];

        }

        s->nodes[0] = element;
        s->size++;

    }

}

Token pop(Stack* s) {

    if (s->size == 0) {

        printf("Stack is empty\n");


    } else {

        for (int i = 0; i < s->size; ++i) {
            s->nodes[i] = s->nodes[i + 1];
        }

        return s->nodes[--s->size];

    }
}

void printStack(Stack* s) {

    if (s->size == 0) {

        printf("Stack is empty\n");

    } 
    else {

        for (int i = 0; i < s->size; i++) {

            printf("%d ", s->nodes[i].value);

        }
        printf("\n");

    }

}

bool isEmpty (Stack* s) {

    if (s->size == 0) {

        return true;

    } 
    else {

        return false;

    }

}

void Task(Stack* s) {
    int maxPosition, tmp;

    for (int i = 0; i < s->size; ++i) {
        maxPosition = i;
        for (int j = i + 1; j < s->size; ++j) {
            if (s->nodes[maxPosition].value < s->nodes[j].value)
                maxPosition = j;
        }
        tmp = s->nodes[maxPosition].value;
        s->nodes[maxPosition].value = s->nodes[i].value;
        s->nodes[i].value = tmp;
    }

    if (s->nodes[0].value != s->nodes[1].value) {
        pop(s);
    }
    
    else {
        int c = s->size;
        for (int i = 0; i < c; ++i) {


            if (s->nodes[0].value != s->nodes[i].value) {
                pop(s);
                break;
            }

            pop(s);
            
        }

    }

    int minPosition;
 
    for (int i = 0; i < s->size; i++) {

        minPosition = i;
        for (int j = i + 1; j < s->size; j++) {
            if (s->nodes[minPosition].value > s->nodes[j].value)
                minPosition = j;
        }
        tmp = s->nodes[minPosition].value;
        s->nodes[minPosition].value = s->nodes[i].value;
        s->nodes[i].value = tmp;
    }
}