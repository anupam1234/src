#include <sys/epoll.h>
#include <iostream>
#include "anw_common.h"
#include "anw_singleton.h"
#include "anw_session.h"
#include "anw_app.h"
#include "anw_map_api.h"
#include "anw_epoll.h"

AnwSession::AnwSession(uint64_t session_id, uint32_t sock_fd)
{
  _sess_id = session_id;
  _sock_fd = sock_fd;
}

AnwSession::~AnwSession()
{
}

uint64_t AnwSession::get_session_id()
{
  return _sess_id;
}

uint32_t AnwSession::get_socket_fd()
{
  return _sock_fd;
}
#if 0
ANW_RSP_STATUS AnwSession::add_flow (AnwFlow *anw_flow, uint64_t flow_id)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  anw_status = anw_map_insert(flow_id, anw_flow, _anw_flow_per_sess_map);
  return anw_status;
}

AnwFlow *AnwSession::remove_flow_by_id (uint64_t flow_id)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  AnwFlow *anw_flow = NULL;
  anw_status = anw_map_remove(flow_id, &anw_flow, _anw_flow_per_sess_map); 
  return anw_session;
}

AnwFlow *AnwSession::find_sess (uint64_t flow_id)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  AnwFlow *anw_flow = NULL;
  anw_status = anw_map_find(flow_id, &anw_flow, _anw_flow_per_sess_map); 
  return anw_session;
}
#endif
ANW_RSP_STATUS AnwSession::process_packet (uint32_t sock_fd, uint8_t *pkt)
{
  ANW_RSP_STATUS anw_status = ANW_STATUS_SUCCESS;
  return anw_status;
}
