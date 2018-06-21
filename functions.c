#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "structs.h"

/**
 * Retorna el maximo entre dos enteros.
 * int a : primer numero.
 * int b : segundo numero.
 * salida: int.
 * T(n) = 1 ; O() = 1
*/
int max(int a, int b){
    return a > b? a : b;
}

/**
 * Obtiene la altura de un Node.
 * Node* n : Node a calcular altura.
 * Salida: int.
 * T(n) = 1 ; O() = 1;
*/
int getHeight(Node* n){
    return n == NULL? 0 : n->h;
}

/**
 * Crea un nuevo Node con altura 1 y los demas datos vacios.
 * salida: Node*.
 * T(n) = 6 ; O() = 1;
*/
Node* createNewNode(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->h = 1;
    newNode->key = NULL;
    newNode->leftChild = NULL;
    newNode ->rightChild = NULL;
    return newNode; 
}

/**
 * Rota hacia la derecha un arbol en base a un Node y retorna la nueva raiz.
 * Node* root : Node base sobre el cual rotar.
 * salida: Node*.
 * T(n) = 7 ; O() = 1;
*/
Node* rightRotation(Node* root){
    Node* newRoot = &*root->leftChild;
    Node* aux = &*root->leftChild->rightChild;

    newRoot->rightChild = root;
    root->leftChild = aux;

    newRoot->h = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));
    root->h = max(getHeight(root->leftChild), getHeight(root->rightChild));

    return newRoot;
}

/**
 * Rota hacia la izquierda un arbol en base a un Node y retorna la nueva raiz.
 * Node* root : Node base sobre el cual rotar.
 * Salida: Node*.
 * T(n) = 7 ; O() = 1.
*/
Node* leftRotation(Node* root){
    Node* newRoot = &*root->rightChild;
    Node* aux = &*root->rightChild->leftChild;

    newRoot->leftChild = root;
    root->rightChild = aux;

    newRoot->h = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));
    root->h = max(getHeight(root->leftChild), getHeight(root->rightChild));

    return newRoot;
}

/**
 * Calcula el balance de un Node del arbol.
 * Node* n : Node al cual se desea calcular el balance.
 * salida: int. Un valor mayor a 1 indica desbalance hacia la derecha.
 *              Un valor menor a -1 indica desbalance hacia la izquierda.
 * T(n) = 1 ; O() = 1;
*/
int getBalance(Node* n){
    if (n == NULL) return 0;
    return getHeight(n->rightChild) - getHeight(n->leftChild);
}

/**
 * Añade un Node al arbol (sin desbalancearlo) dada su raiz y retorna la nueva raiz.
 * Node* root : raiz del arbol.
 * Client* client : Client a agregar al arbol.
 * int option : 1 indica ordenar por ownerName.
 *              2 indica ordenar por nextControlDate.
 * salida: Node*
 * T(n) = ; O() = 
*/ 
Node* add(Node* root, Client* client){
    // Caso base
    if (root == NULL){
        Node* newNode = createNewNode();
        newNode->client = client;
        return newNode;
    }
    // Si Client->ownerName es mayor a la nameKey de root
    // Agregar a la derecha 
    if (strcmp(client->ownerName, root->nameKey) > 0){
        root->rightChild = add(root->rightChild, client);
    }
    // Si Client->ownerName es menor a la nameKey de root
    // Agregar a la izquierda
    if (strcmp(client->ownerName, root->nameKey) < 0){
        root->leftChild = add(root->leftChild, client);
    }
    // Si Client->ownerName es igual a nameKey de root (dos clientes se llaman igual)
    if (strcmp(client->ownerName, root->nameKey) == 0){
        // Añadir el cliente a una lista
    }

    // Aumentos la altura del nodo agregado
    root->h = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
    #pragma region Balancear el arbol
    int balance = getBalance(root);

    #pragma region Arbol desbalanceado hacia la izquierda 
    // Left - left
    if ((balance < -1) && (strcmp(client->ownerName, root->leftChild) < 0)){
        return rightRotation(root);
    }
    // Left - Right
    if ((balance < -1) && (strcmp(client->ownerName, root->leftChild) > 0)){
        root->leftChild = leftRotation(root->leftChild);
        return rightRotation(root);
    }
    #pragma endregion

    #pragma region Arbol desbalanceado hacia la derecha
    // Right - right
    if ((balance > 1) && (strcmp(client->ownerName, root->leftChild) > 0)){
        return leftRotation(root);
    }
    //Right - left
    if ((balance > 1) && (strcmp(client->ownerName, root->leftChild) < 0)){
        root->rightChild = rightRotation(root->rightChild);
        r leftRotation(root);
    }
    #pragma endregion
    #pragma endregion
    return root;
}