#ifndef _KFWEBSOCKETSERVER_H
#define _KFWEBSOCKETSERVER_H

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
#include <string>
#include <mutex>

#include "websocketpp/server.hpp"
#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

#include "IKfWebSocketServer.h"

class KfWebSocketServer : public IKfWebSocketServer {

public:
    KfWebSocketServer();
    ~KfWebSocketServer();

    virtual void enableWebSocketOutputLog();
    virtual void disableWebSocketOutputLog();

    /// Blocking mode
    virtual void run(const uint16_t& port);

    /// Non-blocking mode
    virtual void start(const uint16_t& port);
    virtual size_t poll();
    virtual size_t pollOne();

    /// Stop either one of blocking or non-blocking connections
    virtual void stop();

    virtual bool isListening() const;
    virtual bool isStopped() const;
    virtual bool isSecure() const;

    /// Calbacks setup

    virtual void unbindListeners();
    virtual void setOpenListener(ConnectionListener listener);
    virtual void setCloseListener(ConnectionListener listener);
    virtual void setFailListener(ConnectionListener listener);
    virtual void setHttpListener(ConnectionListener listener);
    virtual void setInterruptListener(ConnectionListener listener);
    virtual void setSocketInitListener(ConnectionListener listener);
    virtual void setTcpInitListener(ConnectionListener listener);
    virtual void setTcpPostInitListener(ConnectionListener listener);
    virtual void setTcpPreInitListener(ConnectionListener listener);
    virtual void setValidateListener(ValidateListener listener);
    virtual void setMessageListener(MessageListener listener);
    virtual void setPingListener(PingListener listener);
    virtual void setPongListener(PongListener listener);
    virtual void setPongTimeoutListener(PongListener listener);

private:
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
    std::mutex m_mutex;
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

#endif // _KFWEBSOCKETSERVER_H
