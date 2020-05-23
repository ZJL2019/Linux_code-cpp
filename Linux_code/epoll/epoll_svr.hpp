/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：epoll_svr.hpp
*   创 建 者：Jaler
*   创建日期：2020年05月23日
*   描    述：epoll模型的服务器
*
================================================================*/

#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <vector>

#include "tcp_svr.hpp"

class EpollSvr
{
    public:
        EpollSvr()
        {
            epoll_fd_=epoll_create(10);
        }

        bool AddFd(int fd)
        {
            struct epoll_event ev;
            ev.events=EPOLLIN;
            ev.data.fd=fd;
            int ret=epoll_ctl(epoll_fd_,EPOLL_CTL_ADD,fd,&ev);
            if(ret < 0)
            {
                perror("epoll_ctl:ADD");
                return false;
            }
            return true;
        }
    
        bool DeleteFd(int fd)
        {
            int ret=epoll_ctl(epoll_fd_,EPOLL_CTL_DEL,fd,NULL);
            if(ret < 0)
            {
                perror("epoll_ctl:DEL");
                return false;
            }
            return true;
        }

        bool EpollWait(std::vector<TcpServer>* output)
        {
            struct epoll_event events[1000];
            int nfds=epoll_wait(epoll_fd_,events,sizeof(events)/sizeof(events[0]),-1);
            if(nfds < 0)
            {
                perror("epoll_wait");
                return false;
            }
            for(int i=0;i < nfds;i++)
            {
                TcpServer ts;
                ts.SetFd(events[i].data.fd);
                output->push_back(ts);
            }
            return true;
        }
    private:
        int epoll_fd_;
};
