#include <stdio.h>
#include <stdlib.h>

void main() {

  int i, j;
  FILE *outfile;
  outfile = fopen("test_input.txt", "w");

  for(i=0; i<100; i++) {
    j = rand() % 1000;
    fprintf(outfile, "INSERT %d\n", j);
  }

  fprintf(outfile, "ASCEND\n");
  fprintf(outfile, "DESCEND\n");

  for(i=0; i<100; i++) {
    j = rand() % 1000;
    fprintf(outfile, "DELETE %d\n", j);
  }
  
  fprintf(outfile, "ASCEND\n");
  fprintf(outfile, "DESCEND\n");

  fclose(outfile);
}
