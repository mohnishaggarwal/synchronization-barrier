#ifndef SYNC_BUFFER_H
#define SYNC_BUFFER_H

#include <iostream>
#include <deque>
#include "thread.h"

using std::cout;
using std::deque;
using std::endl;

class synchronous_buffer
{
private:
  struct request
  {
    int item;
    cv *waiter;
    bool fufilled;
  };
  deque<request *> buffer;
  cv get_wait;
  mutex buffer_lock;

public:
  void put(int item);

  int get();
};

#endif
