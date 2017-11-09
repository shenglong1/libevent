//
// Created by shenglong on 2017/11/6.
//

#ifndef LIBEVENT_MY_EVENT_H
#define LIBEVENT_MY_EVENT_H

#include "event.h"


struct event {
  event_base *base;
  int fd;
  int timer;
  int signal;
  int flags; // EV_READ, EV_PERSIST ...

  void (*event_callback_fn)(evutil_socket_t, short, void *);
  void *args;
};

struct event_base {
  event * events;

};









#endif //LIBEVENT_MY_EVENT_H
