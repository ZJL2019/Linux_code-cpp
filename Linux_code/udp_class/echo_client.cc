#include "udp_client.hpp"

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("Usage ./echo_client [ip]\n");
        return 1;
    }
    UdpClient client(argv[1],9090);
    while(true)
    {
        printf("请输入信息：");
        fflush(stdout);
        char req[1024]={0};
        scanf("%s",req);
        client.SendTo(req);
        std::string resp;
        client.RecvFrom(&resp);
        printf("resp: %s\n",resp.c_str());
    }
    return 0;
    
}
