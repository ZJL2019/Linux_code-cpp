/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：main.cpp
*   创 建 者：Jaler
*   创建日期：2020年05月23日
*   描    述：epoll测试程序
*
================================================================*/

#include "tcp_svr.hpp"
#include "epoll_svr.hpp"


int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("Start this process use in ./tcpsvr [ip] [port]\n");
        return 0;
    }
    std::string ip=argv[1];
    uint16_t port=atoi(argv[2]);
    TcpServer listen_tcpsvr;
    CHECK_RET(listen_tcpsvr.CreateSock());
    CHECK_RET(listen_tcpsvr.Bind(ip,port));
    CHECK_RET(listen_tcpsvr.Listen(5));

    EpollSvr es;
    es.AddFd(listen_tcpsvr.GetFd());
    while(1)
    {
        std::vector<TcpServer> output;
        if(!es.EpollWait(&output))
        {
            continue;
        }
        
        for(size_t i = 0;i < output.size();i++)
        {
            if(output[i].GetFd()==listen_tcpsvr.GetFd())
            {
                TcpServer newts;
                struct sockaddr_in peeraddr;
                listen_tcpsvr.Accept(newts,&peeraddr);
                printf("Have a new connection %s:%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
                es.AddFd(newts.GetFd());
            }
            else
            {
                std::string buf;
                int ret=output[i].Recv(buf);
                if(ret < 0)
                {
                    es.DeleteFd(output[i].GetFd());
                    output[i].Close();
                    continue;
                }
                printf("recv data is %s\n",buf.c_str());
            }
        }
    }
    listen_tcpsvr.Close();
    return 0;
}
