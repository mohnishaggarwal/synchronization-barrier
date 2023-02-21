#ifndef JOIN_THREAD_H
#define JOIN_THREAD_H

#include <deque>
#include "thread.h"

using std::deque;

class join_thread
{
public:
  join_thread(thread_startfunc_t func_in, void *args_in);
  void join();

private:
  static void stub(void *args);

  class lock_guard
  {
  public:
    lock_guard(mutex &m_in);
    ~lock_guard();

  private:
    mutex &lock;
  };

  struct waiter
  {
    cv *waiting_cv;
    waiter *next_waiter;
    bool is_turn;
  };

  bool alive;
  thread_startfunc_t func;
  void *args;

  deque<waiter *> waiting;
  mutex waiting_lock;
};

#endif
