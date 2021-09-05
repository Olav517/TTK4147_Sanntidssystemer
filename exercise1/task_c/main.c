#include <stdio.h>
#include <sched.h>
#include <time.h>

#include "timespec.h"


int main(int argc, char *argv[])
{
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);

  for(int i = 0; i < 100; i++){
    sched_yield();
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("Average time it takes to context switch twice: %d ns\n", timespec_cmp(end, start)/100);

  clock_gettime(CLOCK_MONOTONIC, &start);
  sched_yield();
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("A sample of time it takes to context switch twice: %d ns\n", timespec_cmp(end, start));

  return 0;

}
