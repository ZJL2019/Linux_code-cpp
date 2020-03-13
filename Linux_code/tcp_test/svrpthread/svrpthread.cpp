#include "tcp_svr.hpp"

void* ThreadStart(void* arg)
{
    pthread_detach(pthread_self());
    TcpServer* ts=(TcpServer*)arg;
    while(1)
    {
        std::string buf;
        if(!ts->Recv(buf))
        {
            break;
        }
        printf("cli say:%s\n",buf.c_str());
        printf("svr say:");
        fflush(stdout);
        std::cin>>buf;
        ts->Send(buf);
    }
    delete ts;
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("./svrpthread [ip]\n");
        return 0;
    }
    std::string ip=argv[1];
    uint16_t port=9090;

    TcpServer ts;
    CHECK_RET(ts.CreateSock());
    CHECK_RET(ts.Bind(ip,port));
    CHECK_RET(ts.Listen(5));
    while(1)
    {
        TcpServer* peerts=new TcpServer();
        struct sockaddr_in peeraddr;
        CHECK_RET(ts.Accept(peerts,&peeraddr));
        pthread_t tid;
        int ret=pthread_create(&tid,NULL,ThreadStart,(void*)peerts);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }
    ts.Close();
    return 0;
}
