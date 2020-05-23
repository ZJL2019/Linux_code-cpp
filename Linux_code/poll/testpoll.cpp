/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：testpoll.cpp
*   创 建 者：Jaler
*   创建日期：2020年05月23日
*   描    述：poll的简单测试程序
*
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <poll.h>

int main()
{
    struct pollfd fd_arr[10];
    fd_arr[0].fd=0;
    fd_arr[0].events=POLLIN;

    while(1)
    {
        int ret=poll(fd_arr,1,2000);
        if(ret < 0)
        {
            perror("poll");
            return 0;
        }
        else if(ret==0)
        {
            printf("timeout!\n");
            continue;
        }
        for(size_t i = 0;i < sizeof(fd_arr)/sizeof(fd_arr[0]);i++)
        {
            if(fd_arr[i].revents==POLLIN)
            {
                char buf[1024]={0};
                read(fd_arr[i].fd,buf,sizeof(buf)-1);
                printf("buf=%s\n",buf);
            }
        }
    }
    return 0;
}
