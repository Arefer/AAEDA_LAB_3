#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

int max(int a, int b);
int getHeight(Node* n);
Node* createNewNode();
Node* copyNode(Node* n);
ClientList* createNewClientList();
void addToList(Client* client, ClientList* list);
Node* rightRotation(Node* root);
Node* leftRotation(Node* root);
int getBalance(Node* n);
int customComparer(char* key1, char* key2);
Node* add(Node* root, Client* client, char* key);
Client* createNewClient();
Data* loadClients(char* filePath);
Node* findNode(Node* root, char* query);
#endif /* FUNCTIONS_H */ 