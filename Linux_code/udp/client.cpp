//实现UDP版本的客户端
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// ./client 127.0.0.1
int main(int argc, char* argv[])
{
    //1、先创建一个socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 1;
    }

    // 客户端一般不需要 bind
    // bind意味着和某个具体的端口号关联在一起
    // 如果没有bind，操作系统会随机分配一个端口号
    // 如果是服务器程序不去bind，就会导致每次启动服务的端口号找不到
    // 客户端就没法连接了
    // 如果是客户端 bind的话，可能出现问题
    // 通常情况下：一个端口号只能被一个进程bind
    // 如果客户端 bind一个端口号，其他客户端也可能bind同一个端口号，就会出错
    // 客户端最好还是让操作系统自己随机分配
    
    //准备好服务器的 sockaddr_in 结构
    
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(9090);

    //3、 客户端直接发送数据即可
    while(1)
    {
        char buf[1024] = {0};
        printf("请输入：");
        fflush(stdout);
        scanf("%s",buf);
        sendto(sock, buf ,strlen(buf),0,(sockaddr*)&server_addr, sizeof(server_addr));
        // 从服务器接收一下返回结果
        char buf_output[1024] = {0};
        recvfrom(sock, buf_output,sizeof(buf_output)-1, 0,NULL,NULL);
        //后两个参数填NULL表示不关注对端的地址
        
        printf("server resp: %s\n",buf_output);
    }
    return 0;
}
