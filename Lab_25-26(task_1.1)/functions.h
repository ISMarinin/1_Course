#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>

typedef struct {

    int value;

} Token;

typedef struct {

    Token* nodes;
    unsigned capacity;
    unsigned size;

} Stack;

void initStack(Stack*);
void push(Stack*, Token);
Token pop(Stack*);
void printStack(Stack*);
bool isEmpty (Stack*);
void Task (Stack*);

#endif