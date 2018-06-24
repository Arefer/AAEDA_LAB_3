#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int main(int argc, char const *argv[])
{
    int resultsNum;
    AvlTree* tree = loadClients("Bultos.in");
    ClientList* results = searchClientList(tree->root, "Kevin");

    return 0;
}
