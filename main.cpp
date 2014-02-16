#include <sys/epoll.h>
#include <iostream>
#include <sys/timerfd.h>
#include "anw_common.h"
#include "anw_singleton.h"
#include "anw_session.h"
#include "anw_app.h"
#include "anw_map_api.h"
#include "anw_epoll.h"

class TmpObj
{
  public:
    TmpObj() {count++; cout << "creating a Tmp obj" << endl;}
    ~TmpObj() {};
  private:
    int32_t count;
};

ANW_RSP_STATUS timeout_handler(void *tmp_obj)
{
  cout << "1111111111111111111111111" << endl;
}

ANW_RSP_STATUS timeout_handler_2(void *tmp_obj)
{
  cout << "22222222222222222222222222" << endl;
}
main()
{
  AnwApp *anw_app = AnwApp::CreateInstance();
  ANW_DEBUG_ASSERT(anw_app);
  anw_app->initialise_app();
  TmpObj *tmp_obj = new TmpObj;
  AnwTimer *anw_timer = new AnwTimer(ANW_EPOLL_IMPL_TYPE_TIMER, &timeout_handler,tmp_obj, (uint32_t) 1000, (uint32_t)1000);
  AnwTimer *anw_timer1 = new AnwTimer(ANW_EPOLL_IMPL_TYPE_TIMER, &timeout_handler_2,tmp_obj, (uint32_t) 1000, (uint32_t)5000);
  anw_timer->arm_timer();
  anw_timer1->arm_timer();
  anw_app->create_event_loop();
}
