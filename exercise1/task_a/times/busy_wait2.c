
#include <sys/times.h>

#include <unistd.h>


#include "my_timer.h"

void busy_wait2(int us){

  start_usclock();
  while (now_usclock() < (__intmax_t)us/10000) {} //

  return;
}

int main(int argc, char *argv[])
{
  busy_wait2(1000000);
  return 0;

}
