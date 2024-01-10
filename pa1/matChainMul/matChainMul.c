#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

unsigned int cost (
    unsigned int matrixCount,
    unsigned int* rowSizes,
    unsigned int* colSizes
) {
    if ( matrixCount==1 ) { // Base case.
        return 0; // No multplication to be done.
    } else {

        unsigned int numPossibleSplits = matrixCount-1; // Think: if there are two matrices to multiply, there is one way to split.
        // AB: (A)(B)
        // ABC: (A)(BC) and (AB)(C)

        unsigned int costs[numPossibleSplits];
        for ( unsigned int split=0; split<numPossibleSplits; split++ ) {

            unsigned int l = rowSizes[0];
            //assert ( colSizes[split] == rowSizes[split+1] );
            unsigned int m = colSizes[split];
            unsigned int n = colSizes[matrixCount-1];

            costs[split] =
                cost( split+1, rowSizes, colSizes ) + // cost of left subchain
                l * m * n + // cost of multiplying the two chains
                cost( matrixCount-split-1, rowSizes+split+1, colSizes+split+1 ); // cost of right subchain
        }

        unsigned int minCost = costs[0];
        for ( unsigned int split=1; split<numPossibleSplits; split++ ) {
            if ( costs[split]<minCost ) {
                minCost = costs[split];
            }
        }

        return minCost;
    }
}

int main(int argc, char* argv[]) {

    unsigned int matrixCount;
    unsigned int* rowSizes;
    unsigned int* colSizes;

    int productMatrix[20][20];
    unsigned int productMatrixRow;
    unsigned int productMatrixCol;
    int temp[20][20];

    unsigned int rows, cols;
    int element;

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    if (!fscanf(fp, "%d\n", &matrixCount)) {
        perror("reading the number of matrices failed");
        exit(EXIT_FAILURE);
    }

    rowSizes = calloc( matrixCount, sizeof(int) );
    colSizes = calloc( matrixCount, sizeof(int) );

    for (unsigned int matIndex=0; matIndex<matrixCount; matIndex++) {        
        if(matIndex==0){
            if (!fscanf(fp, "%d %d\n", &rows, &cols)) {
                perror("reading the dimensions of matrix failed");
                exit(EXIT_FAILURE);
            }
            rowSizes[matIndex] = rows;
            colSizes[matIndex] = cols;
            productMatrixRow = rows;
            productMatrixCol = cols;
            for(int r = 0; r < rows; r++){
                for(int c = 0; c < cols; c++){
                    if(c==cols-1){
                        if (!fscanf(fp, "%d\n", &element)) {
                            perror("reading the dimensions of matrix failed");
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        if (!fscanf(fp, "%d ", &element)) {
                            perror("reading the dimensions of matrix failed");
                            exit(EXIT_FAILURE);
                        }
                    }
                    productMatrix[r][c] = element;
                    //printf("%d ", productMatrix[r][c]);
                }
                //printf("\n");  
            }       
        } else{
            if (!fscanf(fp, "%d %d\n", &rows, &cols)) {
                perror("reading the dimensions of matrix failed");
                exit(EXIT_FAILURE);
            }
            rowSizes[matIndex] = rows;
            colSizes[matIndex] = cols;
            int secondMatrix[rows][cols];
            for(int r = 0; r < rows; r++){
                for(int c = 0; c < cols; c++){
                    if(c==cols-1){
                        if (!fscanf(fp, "%d\n", &element)) {
                            perror("reading the dimensions of matrix failed");
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        if (!fscanf(fp, "%d ", &element)) {
                            perror("reading the dimensions of matrix failed");
                            exit(EXIT_FAILURE);
                        }
                    }
                    secondMatrix[r][c] = element;
                }
            }
            for(int r1 = 0; r1 < productMatrixRow; r1++){
                for(int c2 = 0; c2 < cols; c2++){
                    temp[r1][c2] = 0;
                    for(int k = 0; k < rows; k++){
                        temp[r1][c2] += productMatrix[r1][k] * secondMatrix[k][c2];
                    }
                }
            }

            productMatrixCol = cols;
            for(int r = 0; r < productMatrixRow; r++){
                for(int c = 0; c < productMatrixCol; c++){
                    productMatrix[r][c] = temp[r][c];
                    //printf("%d ", productMatrix[r][c]);
                }
                //printf("\n");
            }
        }
        //printf("matIndex: %d, rowSize: %d, colSize: %d\n", matIndex, rows, cols);
    }
    
    printf("%d\n", cost(matrixCount, rowSizes, colSizes) );
    for(int r = 0; r < productMatrixRow; r++){
        for(int c = 0; c < productMatrixCol; c++){
            printf("%d ", productMatrix[r][c]);
        }
        printf("\n");
    }

    free(colSizes);
    free(rowSizes);
    fclose(fp);

    exit(EXIT_SUCCESS);
}
