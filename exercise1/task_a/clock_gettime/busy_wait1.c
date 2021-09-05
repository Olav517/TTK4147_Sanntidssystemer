
#include <time.h>

#include "timespec.h"

void busy_wait1(struct timespec t){
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  struct timespec then = timespec_add(now, t);
  while(timespec_cmp(now, then) < 0){
    for(int i = 0; i < 10000; i++){}
    clock_gettime(CLOCK_MONOTONIC, &now);
  }
}


int main(int argc, char *argv[])
{

  busy_wait1(timespec_normalized((time_t)1, (long)0));

  return 0;

}
