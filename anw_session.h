#ifndef _ANW_SESSION_H_
#define _ANW_SESSION_H_

class AnwSession {
  public:
    AnwSession(uint64_t session_id, uint32_t sock_fd);
    ~AnwSession();
    //ANW_RSP_STATUS add_flow_entry (AnwFlow * anw_flow, uint64_t flow_id);
    ANW_RSP_STATUS process_packet (uint32_t sock_fd, uint8_t *pkt);
    uint64_t get_session_id();
    uint32_t get_socket_fd();
    //AnwFlow *remove_flow_by_id (uint64_t flow_id);
    //AnwFlow *find_flow (uint64_t flow_id);
  private:
    uint64_t _sess_id;
    uint32_t _sock_fd;
    //XXX ue_ip_addr
     //map<uint64_t, AnwFlow *> _anw_flow_per_sess_map;
};
#endif // _ANW_SESSION_H_
