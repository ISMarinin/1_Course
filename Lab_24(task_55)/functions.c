#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

void initStack(Stack* s) {
    s->capacity = 2;
    s->size = 0;
    s->nodes = (Token*)malloc(sizeof(Token) * s->capacity);
}

void push(Stack* s, Token element) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->nodes = (Token*)realloc(s->nodes, sizeof(Token) * s->capacity);
    }
    s->nodes[s->size++] = element;
}

Token pop (Stack* s) {
    if (!s->size) {
        Token t;
        return t;
    }
    return s->nodes[--s->size];
}

Token peak(Stack* s) {
    return s->nodes[s->size - 1];
}

int operationPriority(char a) {
    if (a == '+' || a == '-')
        return 0;
    if (a == '*' || a == '/' || a == '^')
        return 1; 
    else 
        return 2;
}

void printStack(Stack* s) {
    for (int i = 0; i < s->size; ++i) {
        if (s->nodes[i].tokentype == 0) {
            printf("%c", s->nodes[i].operator);
        }
        else if (s->nodes[i].tokentype == 1) {
            printf("%u", s->nodes[i].variable);
        }
        else 
            printf("%c", s->nodes[i].operator);
    }
}

void defineTree(Tree* tr) {
    tr->root = NULL;
}

Node* subInsert(Node* node, Stack* s) {
    if (s->size > 0) {
        if (node == NULL) {
            node = (Node*)malloc(sizeof(Node));
            node->object = pop(s);
            node->left = NULL;
            node->right = NULL;
            if (node->object.tokentype == 1 || node->object.tokentype == 2) {
                return node;
            }
        }
        if (!node->right || (node->right && node->right->object.tokentype == 0)) {
            node->right = subInsert(node->right, s);
        }
        if (!node->left || (node->left && node->left->object.tokentype == 0)) {
            node->left = subInsert(node->left, s);
        }
        return node;
    }
}

void insert(Tree* tr, Stack* s) {
    if (!tr->root) {
        tr->root = (Node*)malloc(sizeof(Node));
        tr->root->object = pop(s);
        tr->root->right = NULL;
        tr->root->left = NULL;
    }
    if (s->size > 0) {
        tr->root = subInsert(tr->root, s);
    }
}

void printElement(Token element) {
    if (element.tokentype == 0)
        printf("%c", element.operator);
    else if (element.tokentype == 1)
        printf("%u", element.variable);
    else
        printf("%c", element.operator);
}

void printTree(Node* node) {
    if (!node->left && !node->right) {
        printElement(node->object);
        return;
    }
    if (node->left) {
        printTree(node->left);
    }
    printElement(node->object);
    if(node->right) {
        printTree(node->right);
    }
}

void Task(Node* node) {

    if (node->object.operator == '-') {
        if (node->left->object.tokentype == 0 && node->right->object.tokentype == 0) {
            if (node->left->object.operator == '^' && node->right->object.operator == '^') {
                if (node->left->right->object.tokentype == 1 && node->right->right->object.tokentype == 1) {
                    if (node->left->right->object.variable == 2 && node->right->right->object.variable == 2) { //const
                        if (node->left->left->object.tokentype == 2 && node->right->left->object.tokentype == 2) {
                            printf("(%c-%c)*(%c+%c)", node->left->left->object.operator, node->right->left->object.operator, 
                            node->left->left->object.operator, node->right->left->object.operator);
                        }
                        else if (node->left->left->object.tokentype == 2 && node->right->left->object.tokentype == 1) {
                            printf("(%c-%d)*(%c+%d)", node->left->left->object.operator, node->right->left->object.variable, 
                            node->left->left->object.operator, node->right->left->object.variable);
                        }
                        else if (node->left->left->object.tokentype == 1 && node->right->left->object.tokentype == 2) {
                            printf("(%d-%c)*(%d+%c)", node->left->left->object.variable, node->right->left->object.operator, 
                            node->left->left->object.variable, node->right->left->object.operator);
                        }
                        else if (node->left->left->object.tokentype == 1 && node->right->left->object.tokentype == 1) {
                            printf("(%d-%d)*(%d+%d)", node->left->left->object.variable, node->right->left->object.variable, 
                            node->left->left->object.variable, node->right->left->object.variable);
                        }
                        else if (node->left->left->object.tokentype == 0 && node->right->left->object.tokentype == 0) {
                            if (node->left->left->object.operator == '+' && node->right->left->object.operator == '+') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d+%d+%d+%d)*(%d+%d-%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%d+%c)*(%d+%d-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%c+%c)*(%d+%d-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%c+%c)*(%d+%c-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c+%c+%c+%c)*(%c+%c-%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%d+%d)*(%c+%d-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d+%d)*(%c+%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d+%d)*(%c+%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%c+%d)*(%c+%d-%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%d+%c)*(%d+%c-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '+' && node->right->left->object.operator == '-') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d+%d+%d-%d)*(%d+%d-%d+%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%d-%c)*(%d+%d-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%c-%c)*(%d+%d-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%c-%c)*(%d+%c-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c+%c+%c-%c)*(%c+%c-%c+%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%d-%d)*(%c+%d-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d-%d)*(%c+%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d-%d)*(%c+%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%c-%d)*(%c+%d-%c+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%d-%c)*(%c+%d-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '-' && node->right->left->object.operator == '+') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d-%d+%d+%d)*(%d-%d-%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%d+%c)*(%d-%d-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%c+%c)*(%d-%d-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%c+%c)*(%d-%c-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c-%c+%c+%c)*(%c-%c-%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%d+%d)*(%c-%d-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d+%d)*(%c-%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d+%d)*(%c-%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%c+%d)*(%c-%d-%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%d+%c)*(%d-%c-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '-' && node->right->left->object.operator == '-') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d-%d+%d-%d)*(%d-%d-%d+%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%d-%c)*(%d-%d-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%c-%c)*(%d-%d-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%c-%c)*(%d-%c-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c-%c+%c-%c)*(%c-%c-%c+%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%d-%d)*(%c-%d-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d-%d)*(%c-%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d-%d)*(%c-%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%c-%d)*(%c-%d-%c+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%d-%c)*(%d-%c-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '+' && node->right->left->object.operator == '/') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d+%d+%d/%d)*(%d+%d-%d/%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%d/%c)*(%d+%d-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%c/%c)*(%d+%d-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%c/%c)*(%d+%c-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c+%c+%c/%c)*(%c+%c-%c/%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%d/%d)*(%c+%d-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d/%d)*(%c+%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d/%d)*(%c+%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%c/%d)*(%c+%d-%c/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%d/%c)*(%d+%c-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '/' && node->right->left->object.operator == '+') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d/%d+%d+%d)*(%d/%d-%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%d+%c)*(%d/%d-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%c+%c)*(%d/%d-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%c+%c)*(%d/%c-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c/%c+%c+%c)*(%c/%c-%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%d+%d)*(%c/%d-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d+%d)*(%c/%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d+%d)*(%c/%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%c+%d)*(%c/%d-%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%d+%c)*(%d/%c-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '+' && node->right->left->object.operator == '*') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d+%d+%d*%d)*(%d+%d-%d*%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%d*%c)*(%d+%d-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%d+%c*%c)*(%d+%d-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%c*%c)*(%d+%c-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c+%c+%c*%c)*(%c+%c-%c*%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%d*%d)*(%c+%d-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d*%d)*(%c+%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%c+%d*%d)*(%c+%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c+%d+%c*%d)*(%c+%d-%c*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d+%c+%d*%c)*(%d+%c-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '*' && node->right->left->object.operator == '+') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d*%d+%d+%d)*(%d*%d-%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%d+%c)*(%d*%d-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%c+%c)*(%d*%d-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%c+%c)*(%d*%c-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c*%c+%c+%c)*(%c*%c-%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%d+%d)*(%c*%d-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d+%d)*(%c*%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d+%d)*(%c*%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%c+%d)*(%c*%d-%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%d+%c)*(%d*%c-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '-' && node->right->left->object.operator == '/') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d-%d+%d/%d)*(%d-%d-%d/%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%d/%c)*(%d-%d-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%c/%c)*(%d-%d-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%c/%c)*(%d-%c-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c-%c+%c/%c)*(%c-%c-%c/%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%d/%d)*(%c-%d-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d/%d)*(%c-%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d/%d)*(%c-%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%c/%d)*(%c-%d-%c/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%d/%c)*(%d-%c-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '/' && node->right->left->object.operator == '-') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d/%d+%d-%d)*(%d/%d-%d+%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%d-%c)*(%d/%d-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%c-%c)*(%d/%d-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%c-%c)*(%d/%c-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c/%c+%c-%c)*(%c/%c-%c+%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%d-%d)*(%c/%d-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d-%d)*(%c/%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d-%d)*(%c/%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%c-%d)*(%c/%d-%c+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%d-%c)*(%d/%c-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '-' && node->right->left->object.operator == '*') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d-%d+%d*%d)*(%d-%d-%d*%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%d*%c)*(%d-%d-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%d+%c*%c)*(%d-%d-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%c*%c)*(%d-%c-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c-%c+%c*%c)*(%c-%c-%c*%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%d*%d)*(%c-%d-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d*%d)*(%c-%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%c+%d*%d)*(%c-%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c-%d+%c*%d)*(%c-%d-%c*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d-%c+%d*%c)*(%d-%c-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '*' && node->right->left->object.operator == '-') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d*%d+%d-%d)*(%d*%d-%d+%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%d-%c)*(%d*%d-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%c-%c)*(%d*%d-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%c-%c)*(%d*%c-%c+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c*%c+%c-%c)*(%c*%c-%c+%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%d-%d)*(%c*%d-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d-%d)*(%c*%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d-%d)*(%c*%c-%d+%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%c-%d)*(%c*%d-%c+%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%d-%c)*(%d*%c-%d+%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '*' && node->right->left->object.operator == '*') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d*%d+%d*%d)*(%d*%d-%d*%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%d*%c)*(%d*%d-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%c*%c)*(%d*%d-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%c*%c)*(%d*%c-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c*%c+%c*%c)*(%c*%c-%c*%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%d*%d)*(%c*%d-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d*%d)*(%c*%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d*%d)*(%c*%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%c*%d)*(%c*%d-%c*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%d*%c)*(%d*%c-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '*' && node->right->left->object.operator == '/') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d*%d+%d/%d)*(%d*%d-%d/%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%d/%c)*(%d*%d-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%d+%c/%c)*(%d*%d-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%c/%c)*(%d*%c-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c*%c+%c/%c)*(%c*%c-%c/%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%d/%d)*(%c*%d-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d/%d)*(%c*%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%c+%d/%d)*(%c*%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c*%d+%c/%d)*(%c*%d-%c/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d*%c+%d/%c)*(%d*%c-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '/' && node->right->left->object.operator == '/') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d/%d+%d/%d)*(%d/%d-%d/%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%d/%c)*(%d/%d-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%c/%c)*(%d/%d-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%c/%c)*(%d/%c-%c/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c/%c+%c/%c)*(%c/%c-%c/%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%d/%d)*(%c/%d-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d/%d)*(%c/%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d/%d)*(%c/%c-%d/%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%c/%d)*(%c/%d-%c/%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%d/%c)*(%d/%c-%d/%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            else if (node->left->left->object.operator == '/' && node->right->left->object.operator == '*') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%d/%d+%d*%d)*(%d/%d-%d*%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable,node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%d*%c)*(%d/%d-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%d+%c*%c)*(%d/%d-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%c*%c)*(%d/%c-%c*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%c/%c+%c*%c)*(%c/%c-%c*%c)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.operator, node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%d*%d)*(%c/%d-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d*%d)*(%c/%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%c+%d*%d)*(%c/%c-%d*%d)", node->left->left->left->object.operator, node->left->left->right->object.operator,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.operator, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1) {
                                    printf("(%c/%d+%c*%d)*(%c/%d-%c*%d)", node->left->left->left->object.operator, node->left->left->right->object.variable,
                                    node->right->left->left->object.operator, node->right->left->right->object.variable,node->left->left->left->object.operator, 
                                    node->left->left->right->object.variable, node->right->left->left->object.operator, node->right->left->right->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2) {
                                    printf("(%d/%c+%d*%c)*(%d/%c-%d*%c)", node->left->left->left->object.variable, node->left->left->right->object.operator,
                                    node->right->left->left->object.variable, node->right->left->right->object.operator,node->left->left->left->object.variable, 
                                    node->left->left->right->object.operator, node->right->left->left->object.variable, node->right->left->right->object.operator);
                                }
                                else 
                                    printf("Input is not correct");
                            } 
                        }
                        else if (node->left->left->object.tokentype == 0 && node->right->left->object.tokentype != 0) {
                            if (node->left->left->object.operator == '+') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d+%d+%d)*(%d+%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d+%d+%c)*(%d+%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d+%c+%c)*(%d+%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c+%c+%c)*(%c+%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c+%c+%d)*(%c+%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c+%d+%d)*(%c+%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c+%d+%c)*(%c+%d-%c)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d+%c+%d)*(%d+%c-%d)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            if (node->left->left->object.operator == '-') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d-%d+%d)*(%d-%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d-%d+%c)*(%d-%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d-%c+%c)*(%d-%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c-%c+%c)*(%c-%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c-%c+%d)*(%c-%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c-%d+%d)*(%c-%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c-%d+%c)*(%c-%d-%c)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d-%c+%d)*(%d-%c-%d)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            if (node->left->left->object.operator == '*') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d*%d+%d)*(%d*%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d*%d+%c)*(%d*%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d*%c+%c)*(%d*%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c*%c+%c)*(%c*%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c*%c+%d)*(%c*%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c*%d+%d)*(%c*%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c*%d+%c)*(%c*%d-%c)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d*%c+%d)*(%d*%c-%d)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                            if (node->left->left->object.operator == '/') {
                                if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d/%d+%d)*(%d/%d-%d)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d/%d+%c)*(%d/%d-%c)", node->left->left->left->object.variable, node->left->left->right->object.variable,node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%d/%c+%c)*(%d/%c-%c)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c/%c+%c)*(%c/%c-%c)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c/%c+%d)*(%c/%c-%d)", node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%c/%d+%d)*(%c/%d-%d)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->left->left->right->object.tokentype == 1 &&
                                node->right->left->object.tokentype == 2) {
                                    printf("(%c/%d+%c)*(%c/%d-%c)", node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->left->left->right->object.tokentype == 2 &&
                                node->right->left->object.tokentype == 1) {
                                    printf("(%d/%c+%d)*(%d/%c-%d)", node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                        }
                        else if (node->left->left->object.tokentype != 0 && node->right->left->object.tokentype == 0) {
                            if (node->right->left->object.operator == '+') {
                                if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%d+%d)*(%d-%d-%d)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%d+%c)*(%d-%d-%c)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%c+%c)*(%d-%c-%c)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%c+%c)*(%c-%c-%c)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%c+%d)*(%c-%c-%d)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%d+%d)*(%c-%d-%d)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%d+%c)*(%c-%d-%c)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%c+%d)*(%d-%c-%d)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                             if (node->right->left->object.operator == '-') {
                                if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%d-%d)*(%d-%d+%d)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%d-%c)*(%d-%d+%c)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%c-%c)*(%d-%c+%c)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%c-%c)*(%c-%c+%c)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%c-%d)*(%c-%c+%d)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%d-%d)*(%c-%d+%d)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%d-%c)*(%c-%d+%c)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%c-%d)*(%d-%c+%d)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                             if (node->right->left->object.operator == '*') {
                                if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%d*%d)*(%d-%d*%d)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%d*%c)*(%d-%d*%c)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%c*%c)*(%d-%c*%c)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%c*%c)*(%c-%c*%c)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%c*%d)*(%c-%c*%d)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%d*%d)*(%c-%d*%d)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%d*%c)*(%c-%d*%c)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%c*%d)*(%d-%c*%d)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                             if (node->right->left->object.operator == '/') {
                                if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%d/%d)*(%d-%d/%d)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 1 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%d/%c)*(%d-%d/%c)", node->left->left->left->object.variable, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%d+%c/%c)*(%d-%c/%c)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%c/%c)*(%c-%c/%c)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 2 &&
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%c/%d)*(%c-%c/%d)", node->left->left->left->object.operator, node->right->left->right->object.operator,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%c+%d/%d)*(%c-%d/%d)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.variable,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.variable);
                                }
                                else if (node->left->left->left->object.tokentype == 2 && node->right->left->right->object.tokentype == 1 && 
                                node->right->left->left->object.tokentype == 2) {
                                    printf("(%c+%d/%c)*(%c-%d/%c)", node->left->left->left->object.operator, node->right->left->right->object.variable,node->right->left->left->object.operator,
                                    node->left->left->left->object.operator, node->left->left->right->object.variable, node->right->left->object.operator);
                                }
                                else if (node->left->left->left->object.tokentype == 1 && node->right->left->right->object.tokentype == 2 && 
                                node->right->left->left->object.tokentype == 1) {
                                    printf("(%d+%c/%d)*(%d-%c/%d)", node->left->left->left->object.variable, node->right->left->right->object.operator,node->right->left->left->object.variable,
                                    node->left->left->left->object.variable, node->left->left->right->object.operator, node->right->left->object.variable);
                                }
                                else 
                                    printf("Input is not correct");
                            }
                        }
                        else 
                            printf("Input is not correct");
                    }
                    else
                        printf("Input is not correct");
                }
                else
                    printf("Input is not correct");
            }
            else 
                printf("Input is not correct");
        }
        else
            printf("Input is not correct");
    }
    else
        printf("Input is not correct");
        
}

void destroy(Node* n) {

    if (n == NULL) 
        return; 
    destroy(n->left);  
    destroy(n->right); 
    free(n);  

}