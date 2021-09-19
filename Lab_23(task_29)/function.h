#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct node {

    int key;
    struct node* left;
    struct node* right;

} Node;

typedef struct {

    Node* root;

} binTree;

void define(binTree*);
void add(binTree*, int);
void print(Node*);
void print(Node*);
void destroy(Node*);
bool search(Node*, int);
int CountOfLeaves(Node*);
Node *createNode(Node*, int);
Node* delete(Node*, int);
Node *minElement(Node*);


#endif