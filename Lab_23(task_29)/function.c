#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "function.h"

void define(binTree* bt) {

    bt->root = NULL;

}

void add(binTree* bt, int key) {
    
    if (!bt->root) {
        bt->root = (Node*)malloc(sizeof(Node));
        bt->root->key = key;
        bt->root->left = NULL;
        bt->root->right = NULL;

        return;
    }

    bt->root = createNode(bt->root, key);
}

void print(Node* root) { // Обход дерева в симметричном порядке 
    
    if (root == NULL)
        return;
    print(root -> left);
    if (root -> key)
        printf("%d ", root -> key);
    print(root -> right);
}

void destroy(Node* n) {

    if (n == NULL) 
        return; 
    destroy(n->left);  
    destroy(n->right); 
    free(n);  

}

bool search(Node* root, int key) {

    if (root == NULL) 
        return 0;
    else if (key == root->key) 
        return 1;
    else if (key < root->key && root->left != NULL) 
        return search(root->left, key);
    else if (key > root->key && root->right != NULL) 
        return search(root->right, key);

}

int CountOfLeaves(Node* root) {
    int count = 100;

    if (root == NULL)
        return 0;
    else if (root->left == NULL && root->right == NULL) 
        return 1;
    else     
        count = CountOfLeaves(root->left) + CountOfLeaves(root->right);
    
    return count;
}

Node* createNode(Node* node, int key) {

    if (!node) {
        node = (Node*)malloc(sizeof(Node));
        node->key = key;
        node->right = NULL;
        node->left = NULL;
        return node;
    }

    if (key < node->key)
        node->left = createNode(node->left, key);

    else 
        node->right = createNode(node->right, key);

    return node;

}

Node *minElement(Node *root) {
    
    Node *l = root;
    while (l -> left != NULL)
        l = l -> left;
    return l;
}

Node* delete(Node* root, int key){
        if (root == NULL) {
            return root;
        }

        if (root->left == NULL && root->right == NULL) {   
            printf("The tree has 1 element\n");
            return 0;
        }

        if (key < root->key) {
            root->left = delete(root->left, key);
        }

        else if (key > root->key) {
            root->right = delete(root->right, key);
        }

        else if (root->left != NULL && root->right != NULL){
            root->key = minElement(root->right)->key;
            root->right = delete(root->right, root->key);
        }

        else {
            if (root->left != NULL) {
                if (root->right == NULL) {
                    root->key = root->left->key;
                    root->left = NULL;
                    return root;
                }
                Node* left = root->left;
                free(root);
                root = left;
            }
            else if (root->right != NULL) {
                if (root->left == NULL) {
                    root->key = root->right->key;
                    root->right = NULL;         
                    return root;
                }
                Node* right = root->right;
                free(root);
                root = right;
            }
            else {
                free(root);
                root = NULL;
            }
        }
        
    return root;
}