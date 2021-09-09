#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
  //long xy_size = 1000*1000*1000; // 8 GB (sizeof(long) = 8 bytes)
  long xy_size = 787500000; // 6.3 GB
  long x_dim = 10000;
  long y_dim = xy_size/x_dim;
  long** matrix = malloc(y_dim*sizeof(long*));
  for(long y = 0; y < y_dim; y++)
  {
    matrix[y] = malloc(x_dim*sizeof(long));
    memset(matrix[y], 0, x_dim*sizeof(long));
  }

  printf("Allocation complete, starting to free memory\n");

  for(long y = 0; y < y_dim; y++)
  {
     free(matrix[y]);
  }
  free(matrix);
  return 0;
}
