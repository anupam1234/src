#include <sys/epoll.h>
#include <iostream>
#include <sys/timerfd.h>
#include "anw_common.h"
#include "anw_singleton.h"
#include "anw_session.h"
#include "anw_app.h"
#include "anw_map_api.h"
#include "anw_epoll.h"

AnwEpollObj::AnwEpollObj(AnwEpollEventImplType type,  epoll_callback callback, void *priv_data)
{
  _type = type;
  _callback = callback;
  _priv_data = priv_data;
}

ANW_RSP_STATUS AnwEpollObj::callback_handler(void)
{
  _callback(_priv_data);
  return ANW_STATUS_SUCCESS;
}

AnwEpollEventImplType AnwEpollObj::get_epoll_impl_type()
{
  return _type;
}

epoll_callback AnwEpollObj::get_callback_ptr()
{
  return _callback;
}

void *AnwEpollObj::get_priv_data()
{
  return _priv_data;
}

//AnwTimer::AnwTimer(uint32_t it_value, uint32_t interval, (ANW_RSP_STATUS) (*timeout_callback) (void *))
//AnwTimer::AnwTimer(uint32_t it_value, uint32_t interval, AnwTimerImpl *anw_timer_impl)
AnwTimer::AnwTimer(AnwEpollEventImplType type, epoll_callback timeout_callback, void *priv_data, uint32_t it_value, uint32_t interval) : AnwEpollObj(type, timeout_callback, priv_data)
{
  _it_value = it_value;
  _interval = interval;
  int flags = TFD_CLOEXEC;
  _timerid = timerfd_create(CLOCK_MONOTONIC, flags);
  if( _timerid == -1 )
  {
    _valid = false;
  }
  //_timeout_callback = timeout_callback;
}

int32_t AnwTimer::get_timer_id()
{
  return _timerid;
}

ANW_RSP_STATUS AnwTimer::arm_timer()
{
  struct itimerspec curr_value;
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  AnwApp *anw_app = NULL;
  epoll_event ev;
  curr_value.it_value.tv_sec = _it_value / 1000;
  curr_value.it_value.tv_nsec = (_it_value % 1000) * 1000 * 1000;
  curr_value.it_interval.tv_sec = _interval / 1000;
  curr_value.it_interval.tv_nsec = (_interval % 1000 ) * 1000 * 1000;
  if( -1 == timerfd_settime(_timerid, 0, &curr_value, 0))
  {
    _valid = false;
    return ANW_STATUS_FAILURE;
  }
  _valid = true;
  ev.events = EPOLLIN | EPOLLPRI ;
  //ev.events = EPOLLIN | EPOLLET ;
  //_epoll_event_impl = new epoll_event_impl(ANW_EPOLL_IMPL_TYPE_TIMER, _timer_impl);
  //ev.data.ptr = _epoll_event_impl;  //pass the pointer to AnwTimerImpl
  ev.data.ptr = this; 
  anw_app = AnwApp::CreateInstance();
  if (unlikely(NULL == anw_app))
  {
    ANW_DEBUG_ASSERT(0);
    return ANW_STATUS_FAILURE;
  }

  anw_status = anw_app->add_timer(_timerid, ev);
  return anw_status;
}
