#include <stdio.h>
#include "array.h"


int main(){
  double no_Mb = 0.5;
  long no_b = (long)(no_Mb*1000000.0);
  printf("Allocating..\n");
  Array myArray = array_new(no_b);
  printf("Writing..\n");
  for (int i=0; i<(no_b+1); i++){
    array_insertBack(&myArray, (long)0);
  }
  printf("Done\n");

  if (myArray.back >  myArray.capacity){
    printf("Full capacity?\n"); }
  printf("Array.back= %ld\n", myArray.back);
  printf("Array.capacity= %ld\n", myArray.capacity);
  array_destroy(myArray);
  return 0;
}
