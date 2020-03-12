#include "tcp_svr.hpp"

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("./cli [ip]\n");
        return 0;
    }
    std::string ip=argv[1];
    uint16_t port = 9090;
    TcpServer ts;
    
    CHECK_RET(ts.CreateSock());
    CHECK_RET(ts.Connect(ip,port));

    while(1)
    {
        printf("cli say:");
        fflush(stdout);
        std::string buf;
        std::cin>>buf;
        ts.Send(buf);

        buf.clear();
        ts.Recv(buf);
        printf("svr say:%s\n",buf.c_str());
    }
    ts.Close();
    return 0;
}
