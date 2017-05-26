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
#ifdef KFSIO_THREAD_SAFE
#include <mutex>
#endif // KFSIO_THREAD_SAFE

#include "websocketpp/server.hpp"
#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

#include "KfWebSocketServer.h"
#include "KfWebSocketConnection.h"


class KfWebSocketServerHandler {
    friend class KfWebSocketServer;

public:
    typedef std::function<void(const KfWebSocketConnection&)> ConnectionListener;
    typedef std::function<bool(const KfWebSocketConnection&)> ValidateListener;
    typedef std::function<void(const KfWebSocketConnection&)> MessageListener; /// @todo MessageWrapper
    typedef std::function<bool(const KfWebSocketConnection&, std::string)> PingListener;
    typedef std::function<void(const KfWebSocketConnection&, std::string)> PongListener;


public:
    KfWebSocketServerHandler();

    void unbindListeners();

    void setOpenListener(ConnectionListener listener);
    void setCloseListener(ConnectionListener listener);
    void setFailListener(ConnectionListener listener);
    void setHttpListener(ConnectionListener listener);
    void setInterruptListener(ConnectionListener listener);
    void setSocketInitListener(ConnectionListener listener);
    void setTcpInitListener(ConnectionListener listener);
    void setTcpPostInitListener(ConnectionListener listener);
    void setTcpPreInitListener(ConnectionListener listener);
    void setValidateListener(ValidateListener listener);
    void setMessageListener(MessageListener listener);
    void setPingListener(PingListener listener);
    void setPongListener(PongListener listener);
    void setPongTimeoutListener(PongListener listener);

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
    void onServerSocketInit(websocketpp::connection_hdl con, boost::asio::ip::tcp::socket& sock);
    void onServerTcpInit(websocketpp::connection_hdl con);
    void onServerTcpPostInit(websocketpp::connection_hdl con);
    void onServerTcpPreInit(websocketpp::connection_hdl con);
    bool onServerValidate(websocketpp::connection_hdl con);

private:
#ifdef KFSIO_THREAD_SAFE
    std::mutex m_mutex;
#endif // KFSIO_THREAD_SAFE
    websocketpp::server<websocketpp::config::asio> m_server;

    ConnectionListener m_openListener;
    ConnectionListener m_closeListener;
    ConnectionListener m_failListener;
    ConnectionListener m_httpListener;
    ConnectionListener m_interruptListener;
    ConnectionListener m_socketInitListener;
    ConnectionListener m_tcpInitListener;
    ConnectionListener m_tcpPostInitListener;
    ConnectionListener m_tcpPreInitListener;
    ValidateListener m_validateListener;
    MessageListener m_messageListener;
    PingListener m_pingListener;
    PongListener m_pongListener;
    PongListener m_pongTimeoutListener;

};
