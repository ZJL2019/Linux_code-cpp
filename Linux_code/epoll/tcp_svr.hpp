#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define CHECK_RET(exp) if(!(exp)) {return 0;}

class TcpServer
{
    public:
        TcpServer()
        {
            Sock_=-1;
        }

        ~TcpServer()
        {}

        bool CreateSock()
        {
            Sock_ = socket(AF_INET,SOCK_STREAM,0);
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
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret = bind(Sock_,(struct sockaddr*)&addr,sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        bool Listen(int BackLog)
        {
            int ret = listen(Sock_,BackLog);
            if(ret < 0)
            {
                perror("listen");
                return false;
            }
            return true;
        }

        bool Accept(TcpServer& ts,struct sockaddr_in* addr=NULL)
        {
            struct sockaddr_in peeraddr;
            socklen_t len = sizeof(struct sockaddr_in);
            int newfd = accept(Sock_,(struct sockaddr*)&peeraddr,&len);
            if(newfd < 0)
            {
                perror("accept");
                return false;
            }
            ts.Sock_ = newfd;
            if(addr!=NULL)
            {
                memcpy(addr,&peeraddr,len);
            }
            return true;
        }
        
        bool Connect(std::string& ip,uint16_t port)
        {
            struct sockaddr_in destaddr;
            destaddr.sin_port = htons(port);
            destaddr.sin_family = AF_INET;
            destaddr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret = connect(Sock_,(struct sockaddr*)&destaddr,sizeof(destaddr));
            if(ret < 0)
            {
                perror("connect");
                return false;
            }
            return true;
        }

        bool Send(std::string& buf)
        {
            int sendsize = send(Sock_,buf.c_str(),buf.size(),0);
            if(sendsize < 0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        bool Recv(std::string& buffer)
        {
            char buf[1024]={0};
            int recvsize=recv(Sock_,buf,sizeof(buf)-1,0);
            if(recvsize < 0)
            {
                perror("recv");
                return false;
            }
            else if(recvsize==0)
            {
                printf("Recv Closed!\n");
                return false;
            }
            buffer.assign(buf,recvsize);
            return true;
        }

        void Close()
        {
            close(Sock_);
            Sock_=-1;
        }
        
        void SetFd(int fd)
        {
            Sock_=fd;
        }

        int GetFd()
        {
            return Sock_;
        }
    private:
        int Sock_;
};
