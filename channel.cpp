#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#endif

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

#include <libssh2.h>
#include <libssh2_sftp.h>

#include "channel.h"

Channel::Channel( LIBSSH2_CHANNEL*channel)
    :m_channel(channel)
{

}

Channel::~Channel(void)
{
    if (m_channel)
    {
        libssh2_channel_free(m_channel);
        m_channel = NULL;
    }
}

std::string Channel::Read( const std::string &strend, int timeout )
{
    std::string data;
    if( NULL == m_channel )
    {
        return data;
    }

    LIBSSH2_POLLFD *fds = new LIBSSH2_POLLFD;
    fds->type = LIBSSH2_POLLFD_CHANNEL;
    fds->fd.channel = m_channel;
    fds->events = LIBSSH2_POLLFD_POLLIN | LIBSSH2_POLLFD_POLLOUT;

    if( timeout % 50 )
    {
        timeout += timeout %50;
    }
    while(timeout>0)
    {
        int rc = (libssh2_poll(fds, 1, 10));
        if (rc < 1)
        {
            timeout -= 50;
            usleep(50*1000);
            continue;
        }

        if ( fds->revents & LIBSSH2_POLLFD_POLLIN )
        {
            char buffer[64*1024] = "";
            size_t n = libssh2_channel_read( m_channel, buffer, sizeof(buffer) );
            if ( n == LIBSSH2_ERROR_EAGAIN )
            {
               //fprintf(stderr, "will read again\n");
            }
            else if (n <= 0)
            {
                return data;
            }
            else
            {
                data += string(buffer);
                if( "" == strend )
                {
                    return data;
                }
                size_t pos = data.rfind(strend);
                if( pos != std::string::npos && data.substr(pos, strend.size()) == strend  )
                {
                    return data;
                }
            }
        }
        timeout -= 50;
        usleep(50*1000);
    }

    cout<<"read data timeout"<<endl;
    return data;
}

bool Channel::Write(const std::string &data)
{
    if( NULL == m_channel )
    {
        return false;
    }

    std::string send_data = data + "\n";
    return libssh2_channel_write_ex( m_channel, 0, send_data.c_str(), send_data.size() ) == data.size();
   //return true;
}
