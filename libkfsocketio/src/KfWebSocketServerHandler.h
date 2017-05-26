#pragma once

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

#include <string>

#include "websocketpp/server.hpp"
#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

#include "KfWebSocketServer.h"

class KfWebSocketServerHandler {
    friend class KfWebSocketServer;

public:
    KfWebSocketServerHandler();

private:
    void bindHandlers();

    void onServerOpen(websocketpp::connection_hdl con);
    void onServerClose(websocketpp::connection_hdl con);
    void onServerFail(websocketpp::connection_hdl con);
    void onServerHttp(websocketpp::connection_hdl con);
    void onServerInterrupt(websocketpp::connection_hdl con);
    void onServerMessage(websocketpp::connection_hdl con, websocketpp::connection<websocketpp::config::asio>::message_ptr msgPtr);
    bool onServerPing(websocketpp::connection_hdl con, std::string msg);
    void onServerPong(websocketpp::connection_hdl con, std::string msg);
    void onServerPongTimeout(websocketpp::connection_hdl con, std::string msg);
    void onServerSocketInit(websocketpp::connection_hdl, boost::asio::ip::tcp::socket&);
    void onServerTcpInit(websocketpp::connection_hdl);
    void onServerTcpPostInit(websocketpp::connection_hdl);
    void onServerTcpPreInit(websocketpp::connection_hdl);
    bool onServerValidate(websocketpp::connection_hdl con);

private:
    websocketpp::server<websocketpp::config::asio> m_server;

};