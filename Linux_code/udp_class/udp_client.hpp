#pragma once
#include "udp_socket.hpp"

class UdpClient
{
public:
    UdpClient(const std::string& ip, uint16_t port)
        :_server_ip(ip)
         ,_server_port(port)
    {
        _sock.Socket();
    }

    ~UdpClient()
    {
        _sock.Close();
    }

    bool RecvFrom(std::string* msg)
    {
        return _sock.RecvFroms(msg);
    }

    bool SendTo(const std::string& msg)
    {
        return _sock.SendTo(msg, _server_ip, _server_port);
    }


private:
    UdpSocket _sock;
    std::string _server_ip;
    uint16_t _server_port;
};
