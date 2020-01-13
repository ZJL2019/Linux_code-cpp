#include "udp_server.hpp"


int main()
{
    UdpServer server;
    // lambda 表达式 本质上是一个 匿名函数
    // []() -> int {}
    server.Start("0.0.0.0", 9090 ,[](const std::string& req,std::string* resp)
            {
                *resp = req;
            });
    return 0;
}
