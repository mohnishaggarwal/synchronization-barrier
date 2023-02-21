#include "barrier.h"

Barrier::Barrier(int num_threads_in) : threads_at_barrier(0), threads_leaving_barrier(0), resetting(false), number_of_threads(num_threads_in) {}

bool Barrier::wait()
{
  barrier_lock.lock();
  cout << "getting here1" << endl;

  while (resetting)
  {
    leave_barrier.wait(barrier_lock);
  }

  cout << "getting here1" << endl;

  bool last_thread = (number_of_threads - threads_at_barrier == 1) ? true : false;
  threads_at_barrier++;

  while (threads_at_barrier < number_of_threads)
  {
    enter_barrier.wait(barrier_lock);
  }
  cout << "getting here4" << endl;

  enter_barrier.broadcast();
  resetting = true;
  threads_leaving_barrier++;

  if (threads_leaving_barrier == number_of_threads)
  {
    threads_at_barrier = 0;
    resetting = false;
    leave_barrier.broadcast();
  }

  barrier_lock.unlock();
  return last_thread;
}
