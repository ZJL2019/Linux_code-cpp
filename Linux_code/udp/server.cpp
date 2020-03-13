//实现UDP版本的服务器
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
//1、先创建一个socket
//AF_INET是一个宏，表示Ipv4
//SOCK_DGRAM 表示使用UDP协议

int main()
{
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("sock");
        return 1;
    }
    // 把当前的socket绑定上一个ip + 端口号
    
    //2. 把当前的sockaddr和sock绑定
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    //ip地址也是一个整数，也需要转为网络字节序
    //inet_addr 函数自动转化了
    addr.sin_addr.s_addr =inet_addr("0.0.0.0");
    //端口号必须要转为网络字节序
    addr.sin_port = htons(9090);
    int ret = bind(sock, (sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return 1;
    }
    printf("server start ok!\n");

    while(true)
    {
        //a)读取客户端请求
        sockaddr_in peer;
        socklen_t len = sizeof(peer);//输入输出参数
        //面向数据报的接口函数
        char buf[1024] = {0};
        ssize_t n = recvfrom(sock, buf,sizeof(buf)-1, 0,(sockaddr*)&peer,&len);
        if(n < 0)
        {
            perror("recvfrom");
            continue;//考虑到容错,不能因为一次请求失败,就不再请求
        }
        buf[n] = '\0';
        //b)根据请求计算响应
        // 此处写的是一个回显服务器
        //c)把响应写回客户端
        sendto(sock,buf,strlen(buf),0,(sockaddr*)&peer,len);
        if(n < 0)
        {
            perror("sendto");
            continue;
        }
        printf("[%s:%d]buf: %s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
    }
    close(sock);

    return 0;
}
