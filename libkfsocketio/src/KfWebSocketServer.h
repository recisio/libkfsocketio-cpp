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
#include <cstdint>

#include "websocketpp/server.hpp"
#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

#include "KfWebSocketConnection.h"
#include "KfWebSocketMessage.h"

class KfWebSocketServer {

public:
    typedef std::function<void(KfWebSocketConnectionPtr)> ConnectionListener;
    typedef std::function<bool(KfWebSocketConnectionPtr)> ValidateListener;
    typedef std::function<void(KfWebSocketConnectionPtr, KfWebSocketMessagePtr)> MessageListener;
    typedef std::function<bool(KfWebSocketConnectionPtr, const char*)> PingListener;
    typedef std::function<void(KfWebSocketConnectionPtr, const char*)> PongListener;

public:
    virtual ~KfWebSocketServer();

    virtual void KF_CALLCONV enableWebSocketOutputLog();
    virtual void KF_CALLCONV disableWebSocketOutputLog();

    /// Blocking mode
    virtual void KF_CALLCONV run(const uint16_t& port);

    /// Non-blocking mode
    virtual void KF_CALLCONV start(const uint16_t& port);
    virtual std::size_t KF_CALLCONV poll();
    virtual std::size_t KF_CALLCONV pollOne();

    /// Stop either one of blocking or non-blocking connections
    virtual void KF_CALLCONV stop();

    virtual bool KF_CALLCONV isListening() const;
    virtual bool KF_CALLCONV isStopped() const;
    virtual bool KF_CALLCONV isSecure() const;

    /// Calbacks setup

    virtual void KF_CALLCONV unbindListeners();
    virtual void KF_CALLCONV setOpenListener(ConnectionListener listener);
    virtual void KF_CALLCONV setCloseListener(ConnectionListener listener);
    virtual void KF_CALLCONV setFailListener(ConnectionListener listener);
    virtual void KF_CALLCONV setHttpListener(ConnectionListener listener);
    virtual void KF_CALLCONV setMessageListener(MessageListener listener);
    virtual void KF_CALLCONV setPingListener(PingListener listener);
    virtual void KF_CALLCONV setPongListener(PongListener listener);
    virtual void KF_CALLCONV setPongTimeoutListener(PongListener listener);

public:
    KfWebSocketServer();

private:
    void KF_CALLCONV onServerOpen(websocketpp::connection_hdl con);
    void KF_CALLCONV onServerClose(websocketpp::connection_hdl con);
    void KF_CALLCONV onServerFail(websocketpp::connection_hdl con);
    void KF_CALLCONV onServerHttp(websocketpp::connection_hdl con);
    void KF_CALLCONV onServerMessage(websocketpp::connection_hdl con, websocketpp::connection<websocketpp::config::asio>::message_ptr msgPtr);
    bool KF_CALLCONV onServerPing(websocketpp::connection_hdl con, std::string msg);
    void KF_CALLCONV onServerPong(websocketpp::connection_hdl con, std::string msg);
    void KF_CALLCONV onServerPongTimeout(websocketpp::connection_hdl con, std::string msg);

    KfWebSocketConnectionSPtr KF_CALLCONV findConnection(websocketpp::server<websocketpp::config::asio>::connection_ptr con);

private:
    std::recursive_mutex m_mutex;
    websocketpp::server<websocketpp::config::asio>* m_server;
    std::vector<KfWebSocketConnectionSPtr> m_connections;

    ConnectionListener m_openListener;
    ConnectionListener m_closeListener;
    ConnectionListener m_failListener;
    ConnectionListener m_httpListener;
    MessageListener m_messageListener;
    PingListener m_pingListener;
    PongListener m_pongListener;
    PongListener m_pongTimeoutListener;

};

#endif // _KFWEBSOCKETSERVER_H
