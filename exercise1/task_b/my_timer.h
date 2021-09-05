#include <sys/times.h>
#include <stdio.h>

void start_usclock();
__intmax_t now_usclock();

static clock_t st_time;
static clock_t now_time;
static struct tms st_cpu;
static struct tms now_cpu;

void start_usclock()
{
    printf("clock started\n" );
    st_time = times(&st_cpu);
}


/* This example assumes that the result of each subtraction
   is within the range of values that can be represented in
   an integer type. */
__intmax_t now_usclock()
{
  now_time = times(&now_cpu);

  /*printf("Real Time: %jd, User Time %jd, System Time %jd\n",
          (__intmax_t)(now_time - st_time),
          (__intmax_t)(now_cpu.tms_utime - st_cpu.tms_utime),
          (__intmax_t)(now_cpu.tms_stime - st_cpu.tms_stime));
          */

  return (__intmax_t)(now_time - st_time); //5 sekunder tilsvarer 500 her
}
