#include "tcp_thread_server.hpp"

void HttpProcess(const std::string& req,std::string* resp)
{
    (void)req;
    std::string first_line = "HTTP/1.1 302 Found\n";
    std::string header = "Location: http://www.sogou.com\n"
        "Content-Type: text/html\n"
        "Content-Length: 10\n";
        std::string body = "aaaaaaaaaa";
    *resp = first_line+header+"\n"+body;
}


int main()
{
    TcpThreadServer server;
    server.Start("0.0.0.0",9090,HttpProcess);
    return 0;
}
