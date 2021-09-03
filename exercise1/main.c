#include <stdio.h>
#include <x86intrin.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

#include "timespec.h"
#include "my_timer.h"

void busy_wait1(struct timespec t){
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  struct timespec then = timespec_add(now, t);
  while(timespec_cmp(now, then) < 0){
    for(int i = 0; i < 10000; i++){}
    clock_gettime(CLOCK_MONOTONIC, &now);
  }
}

void busy_wait2(int us){
  start_usclock();
  while (now_usclock() < us) {}
  return;
}

int main(int argc, char *argv[])
{
  printf("usleep:               ");
  __int64_t start = __rdtsc();
  usleep(1000000);
  __int64_t slutt = __rdtsc();
  printf("CPU ticks:  ");
  printf("%ld", (slutt - start));

  printf("\nmed clock_gettime(): ");
  start = __rdtsc();
  busy_wait1(timespec_normalized((time_t)1, (long)0));
  slutt = __rdtsc();
  printf("CPU ticks:  ");
  printf("%ld", (slutt - start));

  printf("\nmed times():        ");
  start = __rdtsc();
  busy_wait2(1000000);
  slutt = __rdtsc();
  printf("CPU ticks:  ");
  printf("%ld", (slutt - start));

  printf("\n");
  return 0;

}
