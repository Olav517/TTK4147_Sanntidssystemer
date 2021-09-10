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
  double CPU_freq = 2.670000000;//*1000*1000*1000;

  int ns_max = 100;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);
//__rdtsc()
//printf("\nMeasuring resolution of rdtsc()..\n");
/*
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
  }*/
  //clock_gettime()

//  printf("\nMeasuring resolution of clock_gettime()..\n");
/*
    struct timespec t3;
    struct timespec t4;
    for(int i = 0; i < 10*1000*1000; i++){
       clock_gettime(CLOCK_MONOTONIC, &t3);
       //sched_yield() //task c?
       clock_gettime(CLOCK_MONOTONIC, &t4);
      struct timespec ts_ns = (timespec_sub(t4,t3));
      int ns = ts_ns.tv_nsec;
      if(ns >= 0 && ns < ns_max){
        histogram[ns]++;
      }
    }
    for(int i = 0; i < ns_max; i++){
      printf("%d\n", histogram[i]);
    }
    //times()
*/

    //printf("\nMeasuring resolution of times..\n");
      struct tms t5;
      struct tms t6;
      for(int i = 0; i < 10*1000*1000; i++){
        times(&t5);
        times(&t6);

        int ns = ((t6.tms_utime + t6.tms_stime) - (t5.tms_utime+t5.tms_stime)); //å caste cpu_freq blir sikkert feil
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
  //measure_average_read();
  measure_resolution();
  return 0;
}
