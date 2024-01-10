#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {
    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    size_t nodeNum = adjMatrixToList(argv[1], &adjacencyList);
    /*
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    unsigned int dimension;
    if (!fscanf(fp, "%d\n", &dimension)) {
        perror("reading the dimension failed");
        exit(EXIT_FAILURE);
    }
    adjacencyList = malloc(sizeof(int));
    printf("%ld", sizeof(adjacencyList));
    for(int r = 0; r < dimension; r++){
        for(int c = 0; c < dimension; c++){
            if (!fscanf(fp, "%ld\n", &adjacencyList->graphNode)) {
                perror("reading the dimension failed");
                exit(EXIT_FAILURE);
            }
        }
    }
    */
    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    /* ... */
    for (size_t i = 0; i < nodeNum; i++) {
        AdjacencyListNode* dest = adjacencyList[i].next;
        while (dest) {
          if(dest->graphNode > adjacencyList[i].graphNode){
            printf("%ld %ld\n", adjacencyList[i].graphNode, dest->graphNode);
          }
          dest = dest->next;
        }
    }
    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    freeAdjList(nodeNum, adjacencyList);
    return EXIT_SUCCESS;
}
