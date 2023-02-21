#ifndef BARRIER_H
#define BARRIER_H

#include "thread.h"
#include <iostream>

using std::cout;
using std::endl;

class Barrier
{
private:
  // number of threads currently at the barrier
  int threads_at_barrier;
  // number of threads leaving the barrier
  int threads_leaving_barrier;
  // keep track if we are currently resetting the barrier
  bool resetting;
  // number of threads expected to check in at barrier
  int number_of_threads;
  mutex barrier_lock;
  cv enter_barrier;
  cv leave_barrier;

public:
  /* Constructs a new barrier that will allow number_of_threads
     threads to check in. */
  Barrier(int num_threads_in);

  /* Called by a thread checking in to the barrier. Should return
     true if the thread was the last thread to check in (in POSIX threads
     lingo, the "serial thread") and false otherwise. This function should
     block until all threads have checked in. */
  bool wait();

  /* Delete copy constructor and copy assignment operators */
  Barrier(const Barrier &) = delete;
  Barrier &operator=(const Barrier &) = delete;
  Barrier(Barrier &&) = delete;
  Barrier &operator=(Barrier &&) = delete;
};

#endif