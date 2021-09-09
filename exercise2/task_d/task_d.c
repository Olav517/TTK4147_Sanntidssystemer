#include <stdio.h>
#include "array.h"


int main(){
  double no_Mb = 0.001;
  long no_b = (long)(no_Mb*1000000.0);
  printf("Allocating..\n");
  Array myArray = array_new(no_b, 2);
  printf("Writing..\n");
  for (int i=0; i<(no_b*20000); i++){
    array_insertBack(&myArray, (long)0);
  }
  printf("Done\n");

  array_destroy(myArray);

  printf("Allocating..\n");
  Array myNArray = array_new(no_b, 1.2);
  printf("Writing..\n");
  for (int i=0; i<(no_b*20000); i++){
    array_insertBack(&myNArray, (long)0);
  }
  printf("Done\n");


  array_destroy(myNArray);
  return 0;
}
