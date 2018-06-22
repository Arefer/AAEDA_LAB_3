#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

int max(int a, int b);
int getHeight(Node* n);
Node* createNewNode();
ClientList* createNewClientList();
void addToList(Client* client, ClientList* list);
Node* rightRotation(Node* root);
Node* leftRotation(Node* root);
int getBalance(Node* n);
Node* add(Node* root, Client* client, char* key);
Client* createNewClient();
AvlTree* loadClients(char* filePath);
#endif /* FUNCTIONS_H */