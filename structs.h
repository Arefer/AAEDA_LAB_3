#ifndef STRUCTS_H
#define STRUCTS_H

struct client{
    char* id;
    char* ownerName;
    char* lastName1;
    char* lastName2;
    char* petName;
    char* petSpecies;
    int petAge;
    char* phoneNumber;
    int controlsNumber;
    char* vaccine;
    char* nextControlDate;
    struct client* next;
};
typedef struct client Client;

struct clientList{
    Client* first;
    Client* last;
    int length;
};
typedef struct clientList ClientList;

struct node{
    int h;
    ClientList* clients;
    char* key;
    struct node* leftChild;
    struct node* rightChild;
};
typedef struct node Node;

struct avlTree{
    Node* root;
    int length;
};
typedef struct avlTree AvlTree;

struct data{
    AvlTree* namesTree;
    AvlTree* idsTree;
};
typedef struct data Data;
#endif /* STRUCTS_H */