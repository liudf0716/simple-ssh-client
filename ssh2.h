#include <string>
#include "channel.h"

class Ssh2
 {
 public:
  Ssh2(const std::string &srvIp, int srvPort=22 );
  ~Ssh2(void);

  bool Connect( const std::string &userName, const std::string &userPwd);
  bool Disconnect(void);

  Channel* CreateChannel(const std::string &ptyType = "vanilla");

public:
  static void S_KbdCallback(const char*, int, const char*, int, int, const LIBSSH2_USERAUTH_KBDINT_PROMPT*, LIBSSH2_USERAUTH_KBDINT_RESPONSE*, void **a );
  static std::string s_password;

private:
  std::string m_srvIp;
  int    m_srvPort;
  std::string m_userName;
  std::string m_password;
  int    m_sock;
  LIBSSH2_SESSION *m_session;
  };
