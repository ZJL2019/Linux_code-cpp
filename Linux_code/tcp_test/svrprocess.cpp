#include "tcp_svr.hpp"
#include <signal.h>
#include <sys/wait.h>

void sigcb(int signo)
{
    (void) signo;
    while(1)
    {
        waitpid(-1,NULL,WNOHANG);
    }
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
       printf("./svrprocess [ip]\n");
       return 0;
    }
    signal(SIGCHLD,sigcb);
    std::string ip = argv[1];
    uint16_t port=9090;

    TcpServer ts;
    CHECK_RET(ts.CreateSock());
    CHECK_RET(ts.Bind(ip,port));
    CHECK_RET(ts.Listen(5));
    while(1)
    {
        TcpServer peerts;
        struct sockaddr_in peeraddr;
        if(!ts.Accept(peerts,&peeraddr))
        {
            continue;
        }
        printf("Have a new connect %s:%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
        int pid=fork();
        if(pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if(pid==0)
        {
            while(1)
            {
                std::string buf;
                if(!peerts.Recv(buf))
                {
                    break;
                }
                printf("cli say:%s\n",buf.c_str());
                printf("svr say:");
                fflush(stdout);
                buf.clear();
                std::cin>>buf;
                peerts.Send(buf);
            }
            peerts.Close();
            exit(1);
        }
        peerts.Close();
    }
    ts.Close();
    return 0;
}
