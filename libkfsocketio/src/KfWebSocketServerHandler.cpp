#include "KfWebSocketServerHandler.h"

/*
MIT License
Copyright (c) 2017 Recisio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <functional>

KfWebSocketServerHandler::KfWebSocketServerHandler() :
    m_server()
{
    m_server.init_asio();
    bindHandlers();
}

void KfWebSocketServerHandler::bindHandlers()
{
    m_server.set_open_handler(std::bind(&KfWebSocketServerHandler::onServerOpen, this, std::placeholders::_1));
    m_server.set_close_handler(std::bind(&KfWebSocketServerHandler::onServerClose, this, std::placeholders::_1));
    m_server.set_fail_handler(std::bind(&KfWebSocketServerHandler::onServerFail, this, std::placeholders::_1));
    m_server.set_http_handler(std::bind(&KfWebSocketServerHandler::onServerHttp, this, std::placeholders::_1));
    m_server.set_interrupt_handler(std::bind(&KfWebSocketServerHandler::onServerInterrupt, this, std::placeholders::_1));
    m_server.set_message_handler(std::bind(&KfWebSocketServerHandler::onServerMessage, this, std::placeholders::_1, std::placeholders::_2));
    m_server.set_ping_handler(std::bind(&KfWebSocketServerHandler::onServerPing, this, std::placeholders::_1, std::placeholders::_2));
    m_server.set_pong_handler(std::bind(&KfWebSocketServerHandler::onServerPong, this, std::placeholders::_1, std::placeholders::_2));
    m_server.set_pong_timeout_handler(std::bind(&KfWebSocketServerHandler::onServerPongTimeout, this, std::placeholders::_1, std::placeholders::_2));
    m_server.set_socket_init_handler(std::bind(&KfWebSocketServerHandler::onServerSocketInit, this, std::placeholders::_1, std::placeholders::_2));
    m_server.set_tcp_init_handler(std::bind(&KfWebSocketServerHandler::onServerTcpInit, this, std::placeholders::_1));
    m_server.set_tcp_post_init_handler(std::bind(&KfWebSocketServerHandler::onServerTcpPostInit, this, std::placeholders::_1));
    m_server.set_tcp_pre_init_handler(std::bind(&KfWebSocketServerHandler::onServerTcpPreInit, this, std::placeholders::_1));
    m_server.set_validate_handler(std::bind(&KfWebSocketServerHandler::onServerValidate, this, std::placeholders::_1));
}

void KfWebSocketServerHandler::onServerOpen(websocketpp::connection_hdl con)
{
    auto connection = m_server.get_con_from_hdl(con);
}

void KfWebSocketServerHandler::onServerClose(websocketpp::connection_hdl con)
{

}

void KfWebSocketServerHandler::onServerFail(websocketpp::connection_hdl con)
{

}

void KfWebSocketServerHandler::onServerHttp(websocketpp::connection_hdl con)
{

}

void KfWebSocketServerHandler::onServerInterrupt(websocketpp::connection_hdl con)
{

}

void KfWebSocketServerHandler::onServerMessage(websocketpp::connection_hdl con, websocketpp::connection<websocketpp::config::asio>::message_ptr msgPtr)
{

}

bool KfWebSocketServerHandler::onServerPing(websocketpp::connection_hdl con, std::string msg)
{
    return true;
}

void KfWebSocketServerHandler::onServerPong(websocketpp::connection_hdl con, std::string msg)
{

}

void KfWebSocketServerHandler::onServerPongTimeout(websocketpp::connection_hdl con, std::string msg)
{

}

void KfWebSocketServerHandler::onServerSocketInit(websocketpp::connection_hdl, boost::asio::ip::tcp::socket&)
{

}

void KfWebSocketServerHandler::onServerTcpInit(websocketpp::connection_hdl)
{

}

void KfWebSocketServerHandler::onServerTcpPostInit(websocketpp::connection_hdl)
{

}

void KfWebSocketServerHandler::onServerTcpPreInit(websocketpp::connection_hdl)
{

}

bool KfWebSocketServerHandler::onServerValidate(websocketpp::connection_hdl con)
{
    return true;
}
