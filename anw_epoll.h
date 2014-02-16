#ifndef _ANW_EPOLL_H_
#define _ANW_EPOLL_H_
class AnwEpollObj
{
  public:
    //AnwEpollObj(AnwEpollEventImplType type,  ANW_RSP_STATUS (*callback) (void *));
    AnwEpollObj(AnwEpollEventImplType type,  epoll_callback , void *priv_data);
    ~AnwEpollObj();
    AnwEpollEventImplType get_epoll_impl_type();
    epoll_callback get_callback_ptr();
    ANW_RSP_STATUS callback_handler(void);
    void * get_priv_data();
    uint32_t _it_value;
    uint32_t _interval;

  private:
    ANW_RSP_STATUS (*_callback) (void *);
    AnwEpollEventImplType _type; 
    void *_priv_data;
};

class AnwEpollEventImpl
{
  AnwEpollEventImpl(AnwEpollEventImplType type, void *data);
  ~AnwEpollEventImpl();
};
//whenever an application wants to create a timer, it needs to 
//create a timer Impl object. this obj should have 
//instantiation of timer_handler function
class AnwTimer : public AnwEpollObj
{
  private:
    bool _valid;
    ANW_RSP_STATUS (*_timeout_callback) (void *);
    epoll_callback get_callback_ptr();
    int32_t _timerid;
    //AnwEpollEventImpl _epoll_event_impl;
  public:
    AnwTimer(AnwEpollEventImplType type, epoll_callback, void *priv_data, uint32_t it_value, uint32_t interval);
    //AnwTimer(uint32_t it_value, uint32_t interval, epoll_callback);
    ~AnwTimer();
    ANW_RSP_STATUS arm_timer();
    int32_t get_timer_id();
};
#endif //_ANW_EPOLL_H_
