#include "udpsvr.hpp"

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        cout<<"./svr [ip]";
        return 0;
    }

    std::string ip=argv[1];
    uint16_t port=9090;

    UdpSvr us;
    if(!us.CreateSock())
    {
        return 0;
    }

    if(!us.Bind(ip,port))
    {
        return 0;
    }

    while(1)
    {
        std::string buf;
        struct sockaddr_in peer_addr;
        us.Recv(buf,&peer_addr);
        cout<<"client say:["<<buf.c_str()<<"]"<<endl;
        printf("server say:");
        fflush(stdout);
        cin>>buf;
        us.Send(buf,&peer_addr);
    }
    us.Close();
    return 0;
}
