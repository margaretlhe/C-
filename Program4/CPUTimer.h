#ifndef CPUTIMER_H
#define CPUTIMER_H

#include <time.h>
#include <iostream>
#include <sys/resource.h>


using namespace std;

class CPUTimer {
private:
  double start_time;

public:
  CPUTimer(void);
  void reset(void);
  double cur_CPUTime(void);
};

class AutoCPUTimer : public CPUTimer {
public:
  ~AutoCPUTimer(void);
};

CPUTimer::CPUTimer(void)
{
  rusage rUsage;
  struct timeval tim;
  getrusage(RUSAGE_SELF, &rUsage);
  tim = rUsage.ru_utime;
  start_time = (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
  tim = rUsage.ru_stime;
  start_time += (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
}

void CPUTimer::reset(void)
{
  rusage rUsage;
  struct timeval tim;
  getrusage(RUSAGE_SELF, &rUsage);
  tim = rUsage.ru_utime;
  start_time = (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
  tim = rUsage.ru_stime;
  start_time += (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
  //tick_count = clock();
}

double CPUTimer::cur_CPUTime(void)
{
  rusage rUsage;
  struct timeval tim;
  double end_time;
  getrusage(RUSAGE_SELF, &rUsage);
  tim = rUsage.ru_utime;
  end_time = (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
  tim = rUsage.ru_stime;
  end_time += (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
  return end_time - start_time;
}

AutoCPUTimer::~AutoCPUTimer(void)
{
  //cerr << cur_CPUTime() << endl;
}

#endif