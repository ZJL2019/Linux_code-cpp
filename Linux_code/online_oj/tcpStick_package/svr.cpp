#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
#include "tcp_svr.hpp"

int Sum(std::string Data)
{   
    std::vector<std::string> output;
    std::string split_char= "+";
    boost::split(output,Data,boost::is_any_of(split_char),boost::token_compress_off);
    int sum_number=0;
    for(size_t i=0;i < output.size();i++)
    {
        sum_number+=atoi(output[i].c_str());
    }
    return sum_number;
}

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
        sleep(15);
        Data data;
        if(!peets.Recv(data))
        {
            break;
        }
        printf("cli say %d+%d\n",data.a,data.b);
       
        std::string buf;
        buf=std::to_string(data.a+data.b);
        peets.Send(buf);
    }
    ts.Close();
    return 0;
}
