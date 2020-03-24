#include "tcp_svr.hpp"
#include <sstream>
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("./svr [ip]\n");
        return 0;
    }
    std::string ip=argv[1];
    uint16_t port=19999;
    TcpServer ts;
    CHECK_RET(ts.CreateSock());
    CHECK_RET(ts.Bind(ip,port));
    CHECK_RET(ts.Listen(5));
    
    while(1)
    {

        TcpServer peets;
        CHECK_RET(ts.Accept(peets));
        std::string buf;
        if(!peets.Recv(buf))
        {
            break;
        }
        printf("chorme send data: %s\n",buf.c_str());

        //std::string body="<html><body><h1>Hello World</h1><body></html>";
        //char arraybuf[10240]={0};
        //sprintf(arraybuf,"%s %s %s\r\nContent-Length:%lu\r\nContent-Type:%s\r\n\r\n",
        //                               "HTTP/1.1","200","OK",body.size(),"text/html");

        //std::string body="<html><body><h1>Hello World</h1><body></html>";
        //std::stringstream ss;
        //ss<<"HTTP/1.1 200 OK\r\n";
        //ss<<"Content-Length:"<<body.size()<<"\r\n";
        //ss<<"Content-Type:text/html\r\n";
        //ss<<"\r\n";
        //std::string header=ss.str();
        

        std::string body="<html><body><h1>Hello World</h1><body></html>";
        std::stringstream ss;
        ss<<"HTTP/1.1 302 Found\r\n";
        ss<<"Content-Length:"<<body.size()<<"\r\n";
        ss<<"Content-Type:text/html\r\n";
        ss<<"Location:https://www.baidu.com\r\n";
        ss<<"\r\n";
       

        std::string header=ss.str();
        peets.Send(header);
        peets.Send(body);
        peets.Close();

    }
    ts.Close();
    return 0;
}
