#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
using namespace std;
class UdpSvr
{
    public:
        UdpSvr()
        {
            Sock_=-1;
        }

        ~UdpSvr()
        {}

        bool CreateSock()
        {
            Sock_=socket(AF_INET,SOCK_DGRAM,17);
            if(Sock_ < 0)
            {
                perror("socket");
                return false;
            }
            return true;
        }

        bool Bind(std::string& ip,uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(port);
            addr.sin_addr.s_addr=inet_addr(ip.c_str());

            int ret=bind(Sock_,(struct sockaddr*)&addr,sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        bool Send(std::string& buf,struct sockaddr_in* destaddr)
        {
            int sendsize=sendto(Sock_,buf.c_str(),buf.size(),0,(struct sockaddr*)destaddr,sizeof(sockaddr_in));
            if(sendsize < 0)
            {
                perror("sendto");
                return false;
            }
        return 0;
        }

        bool Recv(std::string& buf,struct sockaddr_in* srcaddr)
        {
            char tmp[1024]={0};
            socklen_t socklen=sizeof(struct sockaddr_in);
            int recvsize=recvfrom(Sock_,tmp,sizeof(tmp)-1,0,(struct sockaddr*)srcaddr,&socklen);
            if(recvsize < 0)
            {
               perror("recvfrom");
               return false;
            }
            buf.assign(tmp,recvsize);
            return true;
        }

        void Close()
        {
            close(Sock_);
            Sock_=-1;
        }

    private:
    int Sock_;
};
