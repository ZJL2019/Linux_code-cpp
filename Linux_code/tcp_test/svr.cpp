#include "tcp_svr.hpp"

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("./svr [ip]\n");
        return 0;
    }
    std::string ip=argv[1];
    uint16_t port=9090;
    TcpServer ts;
    CHECK_RET(ts.CreateSock());
    CHECK_RET(ts.Bind(ip,port));
    CHECK_RET(ts.Listen(5));
    
    TcpServer peets;
    CHECK_RET(ts.Accept(peets));
    while(1)
    {
        std::string buf;
        peets.Recv(buf);
        printf("cli say %s\n",buf.c_str());

        printf("svr say:");
        fflush(stdout);
        buf.clear();
        std::cin>>buf;
        peets.Send(buf);
    }
    ts.Close();
    return 0;
}
