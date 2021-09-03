#include <sys/times.h>
#include <stdio.h>

void start_usclock();
int now_usclock();

static clock_t st_time;
static clock_t now_time;
static struct tms st_cpu;
static struct tms now_cpu;

void start_usclock()
{
    st_time = times(&st_cpu);
}


/* This example assumes that the result of each subtraction
   is within the range of values that can be represented in
   an integer type. */
int now_usclock()
{
    now_time = times(&now_cpu);
    return (now_cpu.tms_utime - st_cpu.tms_utime);
}
