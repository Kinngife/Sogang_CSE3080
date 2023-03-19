#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 50000000
#define MAX_VERTICES 10000

int numVertices;
int numEdges;
int randomSeed;
int currWeight = 0;

int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];

void main() {

    FILE *outfile;
    char outfilename[1000];
    int i, j;
    int src, dst, w;

    // parameters
    numVertices = 10000;
    numEdges = 5000000;
    randomSeed = 1;
    sprintf(outfilename, "input_large.txt");

    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    srand(randomSeed);

    outfile = fopen(outfilename, "w");
    fprintf(outfile, "%d\n", numVertices);
    fprintf(outfile, "%d\n", numEdges);

    for(i=0; i<numEdges; i++) {
        while(1) {
            src = rand() % numVertices;
            dst = rand() % numVertices;
            if(src == dst) continue;
            if(adjacencyMatrix[src][dst] > 0) continue;
            w = currWeight++;
            adjacencyMatrix[src][dst] = w;
            adjacencyMatrix[dst][src] = w;
            fprintf(outfile, "%d %d %d\n", src, dst, w);
            break;
        }
    }
    
    fclose(outfile);
    printf("file written to input_large.txt.\n");
}
