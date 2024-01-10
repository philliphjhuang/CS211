#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to find the minimum spanning tree of a weighted undirected graph using Prim's algorithm

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    // An array that keeps track of who is the parent node of each graph node we visit
    // In Prim's algorithm, this parents array keeps track of what is the edge that connects a node to the MST.
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited; i.e., node not yet connected to MST.
    }

    graphNode_t root = rand()%graphNodeCount;
    parents[root] = root;

    // Prim's algorithm:
    // A greedy algorithm that builds the minimum spanning tree.
    // For a graph with N nodes, the minimum spanning tree will have N-1 edges spanning all nodes.
    // Prim's algorithm starts with all nodes unconnected.
    // At each iteration of Prim's algorithm, the minimum weight node that connects an unconnected node to the connected set of nodes is added to the MST.
    for (unsigned iter=0; iter<graphNodeCount-1; iter++) {
        double minimumWeight = DBL_MAX;
        graphNode_t minimumSource = -1;
        graphNode_t minimumDest = -1;
        for (graphNode_t source = 0; source < graphNodeCount; source++) {
            if (parents[source]!=-1) {
                AdjacencyListNode* neighbors = adjacencyList[source].next;
                while(neighbors){
                    if((parents[neighbors->graphNode] == -1)&&(neighbors->weight < minimumWeight)){
                        minimumWeight = neighbors->weight;
                        minimumSource = source;
                        minimumDest = neighbors->graphNode;
                    }
                    neighbors = neighbors->next;
                }
            }
        }
        parents[minimumDest] = minimumSource;
    }
    // Using the fully populated parents array, print the edges in the MST.
    for(graphNode_t i = 0; i < graphNodeCount; i++){
        if(parents[i] != -1 && parents[i]!= i){
            printf("%ld %ld\n", adjacencyList[i].graphNode, parents[i]);
        }
    }
    free (parents);
    freeAdjList ( graphNodeCount, adjacencyList );
    return EXIT_SUCCESS;
}
