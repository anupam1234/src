#ifndef _ANW_APP_H_
#define _ANW_APP_H_

class AnwApp:public Singleton <AnwApp> {
  private:
    map<uint64_t, AnwSession *> _anw_session_id_map;
    map<uint32_t, AnwSession *> _anw_sock_fd_map;
    uint64_t session_id_counter;
    int32_t _ep_fd; 
  protected:
  public:
    AnwApp();
    ~AnwApp();
    ANW_RSP_STATUS add_sess (AnwSession * anw_session);
    AnwSession *remove_sess_from_sess_id_map(uint64_t sess_id);
    AnwSession *remove_sess_from_sock_fd_map(uint32_t sock_fd);
    ANW_RSP_STATUS remove_sess(AnwSession *anw_session);
    uint64_t assign_session_d();
    AnwSession *find_sess_in_sess_id_map (uint64_t sess_id);
    AnwSession *find_sess_in_sock_fd_map (uint32_t sock_fd);
    ANW_RSP_STATUS process_packet (uint32_t sock_fd, uint8_t *pkt);
    ANW_RSP_STATUS add_timer (uint32_t timerid, epoll_event &ev);
    ANW_RSP_STATUS create_event_loop ();
    uint64_t assign_session_id();
    ANW_RSP_STATUS create_session (uint32_t sock_fd);
    ANW_RSP_STATUS initialise_app ();

};
#endif //_ANW_APP_H_
