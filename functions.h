#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

int max(int a, int b);
int getHeight(Node* n);
Node* createNewNode();
Node* rightRotation(Node* root);
Node* leftRotation(Node* root);
int getBalance(Node* n);
#endif /* FUNCTIONS_H */