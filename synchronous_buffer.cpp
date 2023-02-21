#include "synchronous_buffer.h"

void synchronous_buffer::put(int item)
{
  buffer_lock.lock();
  request *new_req = new request{item, new cv, false};
  buffer.push_back(new_req);
  get_wait.signal();
  while (!new_req->fufilled)
  {
    new_req->waiter->wait(buffer_lock);
  }
  delete new_req->waiter;
  delete new_req;
  buffer_lock.unlock();
}

int synchronous_buffer::get()
{
  buffer_lock.lock();
  while (!buffer.size())
  {
    get_wait.wait(buffer_lock);
  }
  request *req_received = buffer.front();
  buffer.pop_front();
  req_received->fufilled = true;
  req_received->waiter->signal();
  int item_received = req_received->item;
  buffer_lock.unlock();
  return item_received;
}