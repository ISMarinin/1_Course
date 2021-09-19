#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    unsigned variable;
    char operator;
    unsigned tokentype;
} Token;

typedef struct {
    Token* nodes;
    unsigned capacity;
    unsigned size;
} Stack;

typedef struct node{
    Token object;
    struct node* right;
    struct node* left;
} Node;

typedef struct {
    Node* root;
} Tree;


void initStack(Stack*);
void push(Stack*, Token);
Token pop (Stack*);
Token peak(Stack*);
int operationPriority(char);
void printStack(Stack*);
void defineTree(Tree*);
Node* subInsert(Node*, Stack*);
void insert(Tree*, Stack*);
void printElement(Token);
void printTree(Node*);
void Task(Node*);
void destroy(Node*);


#endif