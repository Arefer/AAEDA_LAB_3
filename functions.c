#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if (n == NULL) return 0;
    return n->h;
}

/**
 * Crea un nuevo Node con altura 1 y los demas datos vacios.
 * salida: Node*.
 * T(n) = 6 ; O() = 1.
*/
Node* createNewNode(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->h = 1;
    newNode->key = NULL;
    newNode->clients = NULL;
    newNode->leftChild = NULL;
    newNode ->rightChild = NULL;
    return newNode; 
}

/**
 * Copia el contenido de un Node a otro (que se crea en esta funcion).
 * Node* n : Node a copiar.
 * salida: Node*
 * T(n) = 6 ; O() = 1.
 */
Node* copyNode(Node* n){
    Node* newNode = createNewNode();
    newNode->h = n->h;
    newNode->key = n->key;
    newNode->clients = n->clients;
    newNode->leftChild = n->leftChild;
    newNode ->rightChild = n->rightChild;
    return newNode;
}

/**
 * Cre una nueva ClientList vacia.
 * salida: ClientList*.
 * T(n) = 5 ; O() = 1.
*/
ClientList* createNewClientList(){
    ClientList* list = (ClientList*)malloc(sizeof(ClientList));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list; 
}
/**
 * Añade un cliente a la lista de clientes.
 * Client* client: cliente a añadir.
 * ClientList* list: lista de clientes inicializada.
 * salida: void.
 * T(n) = 4 ; O() = 1;
 */ 
void addToList(Client* client, ClientList* list){
    // Si la lista esta vacia
    if (list->length == 0){
        list->first = client;
        list->last = client;
        list->length += 1;
    }
    else{
        list->last->next = client;
        list->last = client;
        list->length += 1;
    }
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

    root->h = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
    newRoot->h = 1 + max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

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

    root->h = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
    newRoot->h = 1 + max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

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
 * Compara key1 y key2 como numero o como string.
 * En el caso de ser numeros, la salida es 1 cuando key1 es mayor a key2
 * y -1 en caso contrario.
 * En el caso de ser strings, se utiliza strcmp.
 * char* key1: primera key a comparar con respecto a key2.
 * char* keyy2: segunda key a comparar con respecto a key1.
 * Salida: int
 * T(n) = 4 ; 0() = 1
 */
int customComparer(char* key1, char* key2){
    int k1 = atoi(key1);
    int k2 = atoi(key2);
    // Si key1 y key2 pueden ser convertidas a numeros
    if (k1 != 0 && k2 != 0){
        if (k1 == k2) return 0;
        return k1 > k2 ? 1 : -1;
    }
    // Sino tratarlas como strings
    return strcmp(key1, key2);
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
Node* add(Node* root, Client* client, char* key){
    // Caso base
    if (root == NULL){
        Node* newNode = createNewNode();
        // Añadir el cliente a la lista de este nodo
        newNode->clients = createNewClientList();
        addToList(client, newNode->clients); 
        newNode->key = key;
        return newNode;
    }
    // Si key es mayor a la key de root
    // Agregar a la derecha 
    if (customComparer(key, root->key) > 0){
        root->rightChild = add(root->rightChild, client, key);
    }
    // Si key es menor a la key de root
    // Agregar a la izquierda
    if (customComparer(key, root->key) < 0){
        root->leftChild = add(root->leftChild, client, key);
    }
    // Si key es igual a key de root (dos clientes se llaman igual)
    if (customComparer(key, root->key) == 0){
        // Añadir el cliente a una lista
        addToList(client, root->clients);
        return root;
    }

    // Aumentamos la altura del Node agregado
    root->h = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
    #pragma region Balancear el arbol
    int balance = getBalance(root);

    #pragma region Arbol desbalanceado hacia la izquierda 
    // Left - left
    if ((balance < -1) && (customComparer(key, root->leftChild->key) < 0)){
        return rightRotation(root);
    }
    // Left - Right
    if ((balance < -1) && (customComparer(key, root->leftChild->key) > 0)){
        root->leftChild = leftRotation(root->leftChild);
        return rightRotation(root);
    }
    #pragma endregion

    #pragma region Arbol desbalanceado hacia la derecha
    // Right - right
    if ((balance > 1) && (customComparer(key, root->rightChild->key) > 0)){
        return leftRotation(root);
    }
    // Right - left
    if ((balance > 1) && (customComparer(key, root->rightChild->key) < 0)){
        root->rightChild = rightRotation(root->rightChild);
        return leftRotation(root);
    }
    #pragma endregion
    #pragma endregion
    return root;
}


/**
 * Crea un nuevo Client con sus campos inicializados.
 * salida: Client*.
 * T(n) = 10 ; O() = 1;
*/
Client* createNewClient(){
    Client* newClient = (Client*)malloc(sizeof(Client));
    newClient->ownerName = (char*)malloc(sizeof(char)*31);
    newClient->lastName1 = (char*)malloc(sizeof(char)*31);
    newClient->lastName2 = (char*)malloc(sizeof(char)*31);     
    newClient->petName = (char*)malloc(sizeof(char)*21);
    newClient->petSpecies = (char*)malloc(sizeof(char)*21);
    newClient->phoneNumber = (char*)malloc(sizeof(char)*21);
    newClient->vaccine = (char*)malloc(sizeof(char)*3);
    newClient->nextControlDate = (char*)malloc(sizeof(char)*11);
    return newClient;
}

/**
 * Carga el archivo con los clientes.
 * char* filePath : ruta del archivo a cargar.
 * salida: Node* root.
 * T(n) = ; O() = 
*/
Data* loadClients(char* filePath){
    #pragma region Variables
    // Arbol de clientes
    Data* d = (Data*)malloc(sizeof(Data));
    d->idsTree = (AvlTree*)malloc(sizeof(AvlTree));
    d->idsTree->length = 0;
    d->namesTree = (AvlTree*)malloc(sizeof(AvlTree));
    d->namesTree->length = 0;
    FILE* file;
    char* line = (char*)malloc(sizeof(char)*180);
    strcpy(line, "");
    int i = 0;
    int l = 0;
    #pragma endregion
    
    // Inicializacion del archivo
    file = fopen(filePath, "rb");
    if (file == NULL){
        printf("No es posible abrir el archivo\n");
        exit(-1);
    }
    // Cantidad de clientes 
    fscanf(file, "%d", &l);
    // Salto de linea pendiente
    fgets(line, sizeof(line), file);
    // Primera linea
    fgets(line, 180, file);
    
    while(i < l){
        char* info;
        Client* newClient = createNewClient();
        newClient->id = (char*)malloc(sizeof(char)*10);
        sprintf(newClient->id, "%d", i+1);
        #pragma region Separacion de datos
        // Nombre
        info = strtok(line, " ");
        strcpy(newClient->ownerName, info);
        // Apellido paterno
        info = strtok(NULL, " ");
        strcpy(newClient->lastName1, info);
        // Apellido materno
        info = strtok(NULL, " ");
        strcpy(newClient->lastName2, info);
        // Nombre de la mascota
        info = strtok(NULL, " ");
        strcpy(newClient->petName, info);
        // Especie de la mascota
        info = strtok(NULL, " ");
        strcpy(newClient->petSpecies, info);
        // Edad de la mascota
        info = strtok(NULL, " ");
        newClient->petAge = atoi(info);
        // Numero de contacto
        info = strtok(NULL, " ");
        strcpy(newClient->phoneNumber, info);
        // Numero de atenciones
        info = strtok(NULL, " ");
        newClient->controlsNumber = atoi(info);
        // Vacuna
        info = strtok(NULL, " ");
        strcpy(newClient->vaccine, info);
        // Fecha del proximo control
        info = strtok(NULL, " ");
        //info = strtok(NULL, "\n");
        strcpy(newClient->nextControlDate, info);
        #pragma endregion
        // Añadir el cliente al arbol de nombres
        d->namesTree->root = add(d->namesTree->root, newClient, newClient->ownerName);
        // Añadir al cliente al arbol de ids
        d->idsTree->root = add(d->idsTree->root, newClient, newClient->id);
        d->namesTree->length += 1;
        d->idsTree->length += 1;
        i++;
        fgets(line, 180, file);
    }
    fclose(file);
    free(line);
    return d;
}

/**
 * Busca un Node* con la key pasada por parametro.
 * char* key : key a buscar.
 * salida: Node*
 * T(n) = ; 0() = 
*/
Node* findNode(Node* root, char* key){
    if (root == NULL){
        return NULL;
    }
    if (customComparer(key, root->key) == 0){
        return root;
    }
    // key buscada es menor -> buscar en la izquierda
    if (customComparer(key, root->key) < 0){
        return findNode(root->leftChild, key);
    }
    // key buscada es mayor -> buscar en la derecha
    if (customComparer(key, root->key) > 0){
        return findNode(root->rightChild, key);
    }
}