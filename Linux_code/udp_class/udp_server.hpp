#pragma once
#include "udp_socket.hpp"
#include <functional>
#include <assert.h>
//通用的 Udp 服务器
// 1、读取请求
// 2、根据请求计算响应
// 3、把响应写回到客户端

//其中1 3 是固定套路，不管是什么常见，代码都一样
//2是和业务相关，所以把2对应的代码提取成一个回调函数

//typedef void (*Handler)(const std::string& req, std::string* resp);
//C++11
typedef std::function<void (const std::string&, std::string*)> Handler;

class UdpServer
{
public:
    UdpServer()
    {
       assert(_sock.Socket());
    }
    ~UdpServer()
    {
        _sock.Close();
    }

    bool Start(const std::string& ip, uint16_t port,Handler handler)
    {
        //1、创建socket(已经完成)
        //2、绑定端口号
        bool ret = _sock.Bind(ip,port);
        if(!ret)
        {
            return false;
        }
        //3.进入一个死循环
        while(true)
        {
            //a)读取请求
            std::string req;
            std::string peer_ip;
            uint16_t peer_port;
            _sock.RecvFroms(&req, &peer_ip, &peer_port);
            //b)根据请求计算响应
            std::string resp;
            handler(req, &resp);
            //c)把响应返回客户端
            _sock.SendTo(resp, peer_ip, peer_port);
        }
    }
private:      
    UdpSocket _sock;
};




