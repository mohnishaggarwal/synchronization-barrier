#include <iostream>
#include <vector>
#include "barrier.h"
#include "thread.h"

using std::cout;
using std::endl;
using std::vector;

Barrier bar(3);

void thread_func(void *arg)
{
  int id = *(static_cast<int *>(arg));
  bool last = bar.wait();
  if (last)
  {
    cout << "thread " << id << " was the last to check in at the barrier" << endl;
  }
  else
  {
    cout << "thread " << id << " was able to continue past the barrier" << endl;
  }
}

void boot_func()
{
  for (int i = 0; i < 10; i++)
  {
    thread t(reinterpret_cast<thread_startfunc_t>(thread_func), static_cast<void *>(&i));
  }
}

int main(int argc, char *argv[])
{
  cpu::boot(reinterpret_cast<thread_startfunc_t>(boot_func), nullptr, 0);
}