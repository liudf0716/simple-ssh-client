#include <iostream>
#include "ssh2.h"

int main(int argc, const char * argv[])
{
    using namespace std;
    //using namespace fish;
    
    Ssh2 ssh("127.0.0.1");
    ssh.Connect("test","xxxxxx");
    Channel* channel = ssh.CreateChannel();
    channel->Write("cd/;pwd");
    cout<<channel->Read()<<endl;
    channel->Write("ssh 127.0.0.1");
    cout<<channel->Read(":")<<endl;
    channel->Write("xxxxxx");
    cout<<channel->Read()<<endl;
    channel->Write("pwd");
    cout<<channel->Read()<<endl;
    delete channel;
    return 0;
}
