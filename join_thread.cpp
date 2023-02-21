#include "join_thread.h"

join_thread::lock_guard::lock_guard(mutex &m_in) : lock(m_in)
{
  lock.lock();
}

join_thread::lock_guard::~lock_guard()
{
  lock.unlock();
}

join_thread::join_thread(thread_startfunc_t func_in, void *args_in) : alive(true), func(func_in), args(args_in)
{
  thread starter(stub, this);
}

void join_thread::stub(void *args)
{
  join_thread *stub_args = static_cast<join_thread *>(args);
  stub_args->func(stub_args->args);
  // join_thread is dead at this point
  lock_guard lock(stub_args->waiting_lock);
  stub_args->alive = false;
}

void join_thread::join()
{
  lock_guard lock(waiting_lock);

  if (!alive)
  {
    return;
  }

  waiter *new_waiter = new waiter;
  new_waiter->waiting_cv = new cv;
  waiting.push_back(new_waiter);
  while (alive || !new_waiter->is_turn)
  {
    new_waiter->waiting_cv->wait(waiting_lock);
  }
}