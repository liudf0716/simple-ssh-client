const int CHANNEL_READ_TIMEOUT = 3000;
    
class Channel
{
public:
    Channel(LIBSSH2_CHANNEL *channel);
    ~Channel(void);

    string Read( const string &strend = "$", int timeout = CHANNEL_READ_TIMEOUT );
    bool   Write(const string &data);
private:
    Channel(const Channel&);
    Channel operator=(const Channel&);
private:
    LIBSSH2_CHANNEL *m_channel;
};