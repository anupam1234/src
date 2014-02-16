#ifndef _ANW_COMMON_H_
#define _ANW_COMMON_H_
#include <iostream>
#include <inttypes.h>
#include <map>

using namespace std;
#define likely(x) __builtin_expect((x),1)
#define unlikely(x) __builtin_expect((x),0)

#ifdef _ANW_DEBUG_
#define ANW_DEBUG_ASSERT(cond) assert(cond)
#else 
#define ANW_DEBUG_ASSERT(cond)
#endif //_ANW_DEBUG_

enum ANW_RSP_STATUS {
  ANW_STATUS_INVALID = 0,
  ANW_STATUS_SUCCESS,
  ANW_STATUS_FAILURE
};

typedef enum AnwEpollEventImplType
{
  ANW_EPOLL_IMPL_TYPE_INVALID,
  ANW_EPOLL_IMPL_TYPE_TIMER,
  ANW_EPOLL_IMPL_TYPE_SOCKET,
}AnwEpollEventImplType;
typedef ANW_RSP_STATUS (*epoll_callback) (void *);
#endif //_ANW_COMMON_H_
