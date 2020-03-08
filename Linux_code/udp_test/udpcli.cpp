#include "udpsvr.hpp"

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        cout<<"./cli [ip]";
        return 0;
    }
    std::string ip=argv[1];
    uint16_t port=9090;

    UdpSvr us;
    if(!us.CreateSock())
    {
        return 0;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(port);
    dest_addr.sin_addr.s_addr=inet_addr(ip.c_str());

    while(1)
    {
        std::string buf;
        cout<<"client say:";
        fflush(stdout);
        cin>>buf;
        us.Send(buf,&dest_addr);
        us.Recv(buf,&dest_addr);

        cout<<"server say:["<<buf.c_str()<<"]"<<endl;
    }
    us.Close();
    return 0;
}
