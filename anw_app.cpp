#include <sys/epoll.h>
#include "anw_common.h"
#include "anw_singleton.h"
#include "anw_session.h"
#include "anw_app.h"
#include "anw_map_api.h"
#include "anw_epoll.h"

AnwApp::AnwApp()
{
  session_id_counter = 0;
}

AnwApp::~AnwApp()
{
}

ANW_RSP_STATUS AnwApp::add_sess (AnwSession *anw_session)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  anw_status = anw_map_insert(anw_session->get_session_id(), anw_session, _anw_session_id_map);
  if (unlikely (anw_status == ANW_STATUS_SUCCESS)) 
  {
    anw_status = anw_map_insert(anw_session->get_socket_fd(), anw_session, _anw_sock_fd_map);
    if (unlikely (anw_status == ANW_STATUS_SUCCESS)) {
      AnwSession *anw_session = remove_sess_from_sess_id_map(anw_session->get_session_id());
      ANW_DEBUG_ASSERT(NULL != anw_session);
    }
  }
  return anw_status;
}


AnwSession *AnwApp::remove_sess_from_sess_id_map (uint64_t sess_id)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  AnwSession *anw_session = NULL;
  anw_status = anw_map_remove(sess_id, &anw_session, _anw_session_id_map); 
  return anw_session;
}

AnwSession *AnwApp::remove_sess_from_sock_fd_map (uint32_t sock_fd)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  AnwSession *anw_session = NULL;
  anw_status = anw_map_remove(sock_fd, &anw_session, _anw_sock_fd_map); 
  return anw_session;
}

AnwSession *AnwApp::find_sess_in_sess_id_map (uint64_t sess_id)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  AnwSession *anw_session = NULL;
  anw_status = anw_map_find(sess_id, &anw_session, _anw_session_id_map); 
  return anw_session;
}

AnwSession *AnwApp::find_sess_in_sock_fd_map (uint32_t sock_fd)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  AnwSession *anw_session = NULL;
  anw_status = anw_map_find(sock_fd, &anw_session, _anw_sock_fd_map); 
  return anw_session;
}

uint64_t AnwApp::assign_session_id()
{
  return ++session_id_counter;
}

ANW_RSP_STATUS AnwApp::create_session (uint32_t sock_fd)
{
  uint64_t session_id = ++session_id_counter;
  ANW_RSP_STATUS sess_insert_status = ANW_STATUS_SUCCESS;
  AnwSession *anw_session = new AnwSession(session_id, sock_fd);
  sess_insert_status = add_sess(anw_session);
  if(unlikely(sess_insert_status == ANW_STATUS_FAILURE))
  {
    delete anw_session;
  }
}  

ANW_RSP_STATUS AnwApp::process_packet (uint32_t sock_fd, uint8_t *pkt)
{
  AnwSession *anw_session = NULL;
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  anw_session = find_sess_in_sock_fd_map(sock_fd);
  if(likely(anw_session != NULL))
  {
    //anw_status = anw_session->process_packet(pkt);
  }
}

ANW_RSP_STATUS AnwApp::add_timer (uint32_t timerid, epoll_event &ev)
{
  if( -1 == epoll_ctl(_ep_fd, EPOLL_CTL_ADD, timerid, &ev))
  {
    cout << "cant add timer" << endl;
  }
}

ANW_RSP_STATUS AnwApp::initialise_app ()
{
  _ep_fd = epoll_create1(EPOLL_CLOEXEC);
}

ANW_RSP_STATUS AnwApp::create_event_loop ()
{
  epoll_event ep_event;
  uint64_t nof = 0;
  AnwEpollObj *anw_epoll_obj = NULL;
  if (unlikely(-1 == _ep_fd))
  {
    cout << "error ion creating the epoll instance " << endl;
    return ANW_STATUS_FAILURE;
  }
  do
  {
    if (unlikely (-1 == epoll_wait(_ep_fd, &ep_event, 1, -1)))
    {
      cout << "error in epoll wait" << endl;
      continue; 
    }
    anw_epoll_obj = (AnwEpollObj *)ep_event.data.ptr;
    ANW_DEBUG_ASSERT(anw_epoll_obj);
    switch(anw_epoll_obj->get_epoll_impl_type())
    {
      case ANW_EPOLL_IMPL_TYPE_TIMER:
        if (unlikely(-1 == read(((AnwTimer *)anw_epoll_obj)->get_timer_id(), (void*)&nof, sizeof(nof))))
        {
          assert(0);
        }
        //add stats here
        cout << "timer expiry" << endl;
        break;
      
  
      case ANW_EPOLL_IMPL_TYPE_SOCKET:
        cout << "event on socket" << endl;
        //add stats here
        break;
   
      default:
        ANW_DEBUG_ASSERT(0);
        continue;
    }
    //call teh callback now
    epoll_callback cbk = anw_epoll_obj->get_callback_ptr();
    cbk(anw_epoll_obj->get_priv_data());
  } while (1);
  return ANW_STATUS_SUCCESS;
}
