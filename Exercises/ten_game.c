#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    char op;
    double value;
    struct Node *left;
    struct Node *right;
} Node;

double eval(Node *n){
    if (n->op == '\0') return n->value;
    double l = eval(n->left);
    double r = eval(n->right);
    switch (n->op) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return r != 0 ? l / r : 0;
    }
    return 0.0;
}

Node *make_leaf(double value){
    Node *n = malloc(sizeof(Node));
    n->op = '\0';
    n->value = value;
    n->left = n->right = NULL;
    return n;
}

