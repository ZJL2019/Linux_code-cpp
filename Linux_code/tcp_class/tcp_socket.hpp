#pragma once

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>


class TcpSocket
{
public:
    TcpSocket()
        :_fd(-1)
    {

    }

    bool Socket()
    {
        _fd=socket(AF_INET,SOCK_STREAM,0);
        if(_fd < 0)
        {
            return false;
        }
        return true;
    }

    bool Bind(const std::string& ip,uint16_t port)
    {
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port=htons(port);
        int ret=bind(_fd, (sockaddr*)&addr, sizeof(addr));
        if(ret < 0)
        {
            perror("bind");
            return false;
        }
        return true;
    }

    bool Listen()
    {
        //进入监听状态
        int ret=listen(_fd,10);
        if(ret < 0)
        {
            perror("listen");
            return false;
        }
        return true;
    }

    bool Accept(TcpSocket* peer,std::string* ip=NULL,uint16_t* port=NULL)
    {
        //从连接队列中取一个到用户代码中
        //如果队列中没有连接，就会阻塞(默认行为)
        sockaddr_in peer_addr;
        socklen_t len=sizeof(peer_addr);
        //返回值也是一个socket
        int client_sock = accept(_fd,(sockaddr*)&peer_addr,&len);
        if(client_sock < 0)
        {
            perror("accept");
            return false;
        }
        peer->_fd=client_sock;
        if(ip!=NULL)
        {
            *ip=inet_ntoa(peer_addr.sin_addr);
        }
        if(port!=NULL)
        {
            *port=ntohs(peer_addr.sin_port);
        }
        return true;
    }

    int Recv(std::string* msg)
    {
        msg->clear();
        char buf[1024*10]={0};
        ssize_t n=recv(_fd,buf,sizeof(buf)-1,0);
        //recv的返回值：如果读取成功，返回结果为读到的字节数
        //如果读取失败，返回结果为 -1
        //如果对端关闭了，socket返回结果为0
        if(n < 0)
        {
            perror("recv");
            return -1;
        }
        else if(n==0)
        {
            return 0;
        }
        msg->assign(buf);
        return 1;
    }
    
    bool Send(const std::string& msg)
    {
        ssize_t n =send(_fd,msg.c_str(),msg.size(),0);
        if(n < 0)
        {
            perror("send");
            return false;
        }
        return true;
    }

    bool Connect(const std::string& ip,uint16_t port)
    {
        sockaddr_in addr;
        addr.sin_family =AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port =htons(port);
        int ret=connect(_fd,(sockaddr*)&addr,sizeof(addr));
        if(ret < 0)
        {
            perror("connect");
            return false;
        }
        return true;
    }

    bool Clsoe()
    {
        if(_fd!=-1)
        {
            close(_fd);
        }
        return true;
    }

private:
    int _fd;
};
