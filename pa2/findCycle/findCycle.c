#include "../graphutils.h"

// A program to find a cycle in a directed graph

// You may use DFS or BFS as needed
struct element {
    graphNode_t node;
    struct element* next;
};

void push(struct element** topNode, graphNode_t newTop);
graphNode_t pop(struct element** topNode);
bool isCycleDFS(size_t graphNodeCount, AdjacencyListNode* adjacencyList, int* visited, graphNode_t* parents, graphNode_t parent, graphNode_t current);

void push(struct element** topNode, graphNode_t newTop){
    struct element* new_top = (struct element*)malloc(sizeof(struct element));
    new_top->node = newTop;
    new_top->next = (*topNode);
    (*topNode) = new_top;
}

graphNode_t pop(struct element** topNode){
    struct element* temp;
    graphNode_t temp_close;
    temp = *topNode;
    temp_close = temp->node;
    *topNode = temp->next;
    free(temp);
    return temp_close;
}

//search through graph for cycle using DFS function
bool isCycleDFS(size_t graphNodeCount, AdjacencyListNode* adjacencyList, int* visited, graphNode_t* parents, graphNode_t parent, graphNode_t current) {
    if(visited[current] == 0){
        graphNode_t temp = parent;
        struct element* stack = NULL;
        while(temp != current){
            push(&stack, temp);
            temp = parents[temp];
        }
        push(&stack, current);
        while(stack != NULL){
            graphNode_t topNode = pop(&stack);
            printf("%ld ", topNode);
        }
        return true;
    } else {
        visited[current] = 0;
    }
    parents[current] = parent;
    AdjacencyListNode* neighbor = adjacencyList[current].next;
    bool isCycle = false;

    while(neighbor){
        isCycle = isCycleDFS(graphNodeCount, adjacencyList, visited, parents, current, neighbor->graphNode);
        if(isCycle){
            break;
        }
        neighbor = neighbor->next;
    }
    visited[current] = 1;
    return isCycle;
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    bool isCyclic = false;
    int* visited = calloc(graphNodeCount, sizeof(int));
    graphNode_t* parents = calloc(graphNodeCount, sizeof(graphNode_t));

    for (unsigned source=0; source<graphNodeCount; source++) {
        for(int i = 0; i< graphNodeCount; i++){
            visited[i] = -1;
        }
        if(isCycleDFS(graphNodeCount,adjacencyList,visited,parents,adjacencyList[source].graphNode, adjacencyList[source].graphNode)){
            isCyclic = true;
            break;
        }
    }
    if (!isCyclic) { 
        printf("DAG\n"); 
    }
    freeAdjList ( graphNodeCount, adjacencyList );
    free (visited);
    free(parents);
    return EXIT_SUCCESS;
}
