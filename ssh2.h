 class Ssh2
 {
 public:
  Ssh2(const string &srvIp, int srvPort=22 );
  ~Ssh2(void);

  bool Connect( const string &userName, const string &userPwd);
  bool Disconnect(void);

  Channel* CreateChannel(const string &ptyType = "vanilla");

public:
  static void S_KbdCallback(const char*, int, const char*, int, int, const LIBSSH2_USERAUTH_KBDINT_PROMPT*, LIBSSH2_USERAUTH_KBDINT_RESPONSE*, void **a );
  static string s_password;

private:
  string m_srvIp;
  int    m_srvPort;
  string m_userName;
  string m_password;
  int    m_sock;
  LIBSSH2_SESSION *m_session;
  };
