#ifndef STRUCTS_H
#define STRUCTS_H

struct client{
    int id;
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
};
typedef struct client Client;

struct node{
    int h;
    Client* client;
    char* nameKey;
    char* dateKey;
    struct node* leftChild;
    struct node* rightChild;
};
typedef struct node Node;

#endif /* STRUCTS_H */