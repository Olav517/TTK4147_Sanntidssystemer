#include <stdio.h>
#include <x86intrin.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>
#include <string.h>
#include <sched.h>

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
void measure_average_read(){
  struct timespec before;
  struct timespec after;
  clock_gettime(CLOCK_MONOTONIC, &before);
  for(int i = 0; i < 10*1000*1000; i++){
    __rdtsc();
  }
  clock_gettime(CLOCK_MONOTONIC, &after);

  printf("Snittid for _rdtsc: %d ns\n", timespec_cmp(after, before)/(10*1000*1000));

  clock_gettime(CLOCK_MONOTONIC, &before);
  for(int i = 0; i < 10*1000*1000; i++){
    clock_gettime(CLOCK_MONOTONIC, &after);
  }
  printf("Snittid for clock_gettime() %d ns\n", timespec_cmp(after, before)/(10*1000*1000));

  struct tms now_cpu;
  clock_gettime(CLOCK_MONOTONIC, &before);
  for(int i = 0; i < 10*1000; i++){
    times(&now_cpu);
  }
  clock_gettime(CLOCK_MONOTONIC, &after);

  printf("Snittid for times(): %d ns\n", timespec_cmp(after, before)/(10*1000));

}

void measure_resolution(){
  double CPU_freq = 2.670000000;

  int ns_max = 50;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);
//__rdtsc()
printf("\nMeasuring resolution of rdtsc()..\n");
  int t1, t2;
  for(int i = 0; i < 10*1000*1000; i++){
     t1 = __rdtsc();
     t2 = __rdtsc();
    int ns = (t2 - t1) / CPU_freq;
    if(ns >= 0 && ns < ns_max){
      histogram[ns]++;
    }
  }
  for(int i = 0; i < ns_max; i++){
    printf("%d\n", histogram[i]);
  }
  //clock_gettime()
  printf("\nMeasuring resolution of clock_gettime()..\n");
    int t3, t4;
    for(int i = 0; i < 10*1000*1000; i++){
       t3 = __rdtsc();
       //sched_yield() //task c?
       t4 = __rdtsc();
      int ns = (t4 - t3) / CPU_freq;
      if(ns >= 0 && ns < ns_max){
        histogram[ns]++;
      }
    }
    for(int i = 0; i < ns_max; i++){
      printf("%d\n", histogram[i]);
    }
    //times()
    printf("\nMeasuring resolution of times..\n");
      struct tms st_cpu;
      struct tms en_cpu;
      __intmax_t t5, t6;
      for(int i = 0; i < 10*1000*1000; i++){
         t5 = times(&st_cpu);
         t6 = times(&en_cpu);
        __intmax_t ns = (t6 - t5) / (__intmax_t)CPU_freq; //å caste cpu_freq blir sikkert feil
        if(ns >= 0 && ns < ns_max){
          histogram[ns]++;
        }
      }
      for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
      }
}

int main(int argc, char *argv[])
{
  measure_average_read();
  measure_resolution();
  return 0;
}
