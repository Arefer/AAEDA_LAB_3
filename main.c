#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int main(int argc, char const *argv[])
{
    int resultsNum;
    Data* d = loadClients("Bultos.in");
    Node* result = findNode(d->idsTree->root, "500");
    Node* result2 = findNode(d->namesTree->root, "Placido");
    return 0;
}