#include "KfWebSocketServer.h"

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

#include "KfWebSocketConnection.h"
#include "KfWebSocketMessage.h"

#include "websocketpp/server.hpp"
#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

#define _KFSIO_WSSERVER_LOCK m_mutex.lock()
#define _KFSIO_WSSERVER_UNLOCK m_mutex.unlock()

#define _KFWEBSOCKET_CAST_CONNECTION_CB(con) \
websocketpp::server<websocketpp::config::asio>::connection_ptr connection; \
try { \
    connection = m_server.get_con_from_hdl(con); \
} catch (...) { 

#define _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con) \
_KFWEBSOCKET_CAST_CONNECTION_CB(con)\
    return; \
} 

#define _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con) \
_KFWEBSOCKET_CAST_CONNECTION_CB(con)\
    return false; \
} 

#define _KFWEBSOCKET_SIMPLE_CONCB(cb, con) \
_KFSIO_WSSERVER_LOCK; \
if (nullptr != cb) { \
    cb(std::make_shared<KfWebSocketConnection>(con)); \
} \
_KFSIO_WSSERVER_UNLOCK 

KfWebSocketServer::KfWebSocketServer() :
    m_mutex(),
    m_server(),
    m_openListener(nullptr),
    m_closeListener(nullptr),
    m_failListener(nullptr),
    m_httpListener(nullptr),
    m_interruptListener(nullptr),
    m_socketInitListener(nullptr),
    m_tcpInitListener(nullptr),
    m_tcpPostInitListener(nullptr),
    m_tcpPreInitListener(nullptr),
    m_validateListener(nullptr),
    m_messageListener(nullptr),
    m_pingListener(nullptr),
    m_pongListener(nullptr),
    m_pongTimeoutListener(nullptr)
{
    disableWebSocketOutputLog();
    m_server.init_asio();
}

KfWebSocketServer::~KfWebSocketServer()
{
    unbindListeners();
    stop();
}

void KfWebSocketServer::enableWebSocketOutputLog()
{
    m_server.set_access_channels(websocketpp::log::alevel::all);
}

void KfWebSocketServer::disableWebSocketOutputLog()
{
    m_server.clear_access_channels(websocketpp::log::alevel::all);
}

void KfWebSocketServer::run(const uint16_t& port)
{
    start(port);
    m_server.run();
}

void KfWebSocketServer::start(const uint16_t& port)
{
    _KFSIO_WSSERVER_LOCK;
    m_server.listen(port);
    m_server.start_accept();
    _KFSIO_WSSERVER_UNLOCK;
}

size_t KfWebSocketServer::poll()
{
    return m_server.poll();
}

size_t KfWebSocketServer::pollOne()
{
    return m_server.poll_one();
}

void KfWebSocketServer::stop()
{
    _KFSIO_WSSERVER_LOCK;
    m_server.stop_listening();
    m_server.stop();
    _KFSIO_WSSERVER_UNLOCK;
}

bool KfWebSocketServer::isListening() const
{
    return m_server.is_listening();
}

bool KfWebSocketServer::isStopped() const
{
    return m_server.stopped();
}

bool KfWebSocketServer::isSecure() const
{
    return m_server.is_secure();
}

void KfWebSocketServer::unbindListeners()
{
    m_server.set_close_handler(nullptr);
    m_server.set_fail_handler(nullptr);
    m_server.set_http_handler(nullptr);
    m_server.set_interrupt_handler(nullptr);
    m_server.set_message_handler(nullptr);
    m_server.set_ping_handler(nullptr);
    m_server.set_pong_handler(nullptr);
    m_server.set_pong_timeout_handler(nullptr);
    m_server.set_socket_init_handler(nullptr);
    m_server.set_tcp_init_handler(nullptr);
    m_server.set_tcp_post_init_handler(nullptr);
    m_server.set_tcp_pre_init_handler(nullptr);
    m_server.set_validate_handler(nullptr);

    _KFSIO_WSSERVER_LOCK;
    m_openListener = nullptr;
    m_closeListener = nullptr;
    m_failListener = nullptr;
    m_httpListener = nullptr;
    m_interruptListener = nullptr;
    m_socketInitListener = nullptr;
    m_tcpInitListener = nullptr;
    m_tcpPostInitListener = nullptr;
    m_tcpPreInitListener = nullptr;
    m_validateListener = nullptr;
    m_messageListener = nullptr;
    m_pingListener = nullptr;
    m_pongListener = nullptr;
    m_pongTimeoutListener = nullptr;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setOpenListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_openListener = listener;
    if (nullptr != m_openListener) {
        m_server.set_open_handler(std::bind(&KfWebSocketServer::onServerOpen, this, std::placeholders::_1));
    } else {
        m_server.set_open_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setCloseListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_closeListener = listener;
    if (nullptr != m_closeListener) {
        m_server.set_close_handler(std::bind(&KfWebSocketServer::onServerClose, this, std::placeholders::_1));
    } else {
        m_server.set_close_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setFailListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_failListener = listener;
    if (nullptr != m_failListener) {
        m_server.set_fail_handler(std::bind(&KfWebSocketServer::onServerFail, this, std::placeholders::_1));
    } else {
        m_server.set_fail_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setHttpListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_httpListener = listener;
    if (nullptr != m_httpListener) {
        m_server.set_http_handler(std::bind(&KfWebSocketServer::onServerHttp, this, std::placeholders::_1));
    } else {
        m_server.set_http_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setInterruptListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_interruptListener = listener;
    if (nullptr != m_interruptListener) {
        m_server.set_interrupt_handler(std::bind(&KfWebSocketServer::onServerInterrupt, this, std::placeholders::_1));
    } else {
        m_server.set_interrupt_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setSocketInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_socketInitListener = listener;
    if (nullptr != m_socketInitListener) {
        m_server.set_socket_init_handler(std::bind(&KfWebSocketServer::onServerSocketInit, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server.set_socket_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setTcpInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpInitListener = listener;
    if (nullptr != m_tcpInitListener) {
        m_server.set_tcp_init_handler(std::bind(&KfWebSocketServer::onServerTcpInit, this, std::placeholders::_1));
    } else {
        m_server.set_tcp_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setTcpPostInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpPostInitListener = listener;
    if (nullptr != m_tcpPostInitListener) {
        m_server.set_tcp_post_init_handler(std::bind(&KfWebSocketServer::onServerTcpPostInit, this, std::placeholders::_1));
    } else {
        m_server.set_tcp_post_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setTcpPreInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpPreInitListener = listener;
    if (nullptr != m_tcpPreInitListener) {
        m_server.set_tcp_pre_init_handler(std::bind(&KfWebSocketServer::onServerTcpPreInit, this, std::placeholders::_1));
    } else {
        m_server.set_tcp_pre_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setValidateListener(ValidateListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_validateListener = listener;
    if (nullptr != m_validateListener) {
        m_server.set_validate_handler(std::bind(&KfWebSocketServer::onServerValidate, this, std::placeholders::_1));
    } else {
        m_server.set_validate_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setMessageListener(MessageListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_messageListener = listener;
    if (nullptr != m_messageListener) {
        m_server.set_message_handler(std::bind(&KfWebSocketServer::onServerMessage, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server.set_message_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setPingListener(PingListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pingListener = listener;
    if (nullptr != m_pingListener) {
        m_server.set_ping_handler(std::bind(&KfWebSocketServer::onServerPing, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server.set_ping_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setPongListener(PongListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pongListener = listener;
    if (nullptr != m_pongListener) {
        m_server.set_pong_handler(std::bind(&KfWebSocketServer::onServerPong, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server.set_pong_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setPongTimeoutListener(PongListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pongTimeoutListener = listener;
    if (nullptr != m_pongTimeoutListener) {
        m_server.set_pong_timeout_handler(std::bind(&KfWebSocketServer::onServerPongTimeout, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server.set_pong_timeout_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::onServerOpen(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_openListener, connection);
}

void KfWebSocketServer::onServerClose(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_closeListener, connection);
}

void KfWebSocketServer::onServerFail(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_failListener, connection);
}

void KfWebSocketServer::onServerHttp(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_httpListener, connection);
}

void KfWebSocketServer::onServerInterrupt(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_interruptListener, connection);
}

void KfWebSocketServer::onServerMessage(websocketpp::connection_hdl con, websocketpp::connection<websocketpp::config::asio>::message_ptr msgPtr)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_messageListener) {
        m_messageListener(std::make_shared<KfWebSocketConnection>(connection), std::make_shared<KfWebSocketMessage>(msgPtr));
    }
    _KFSIO_WSSERVER_UNLOCK;
}

bool KfWebSocketServer::onServerPing(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con);
    bool ret = true;
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_pingListener) {
        ret = m_pingListener(std::make_shared<KfWebSocketConnection>(connection), msg);
    }
    _KFSIO_WSSERVER_UNLOCK;
    return ret;
}

void KfWebSocketServer::onServerPong(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_pongListener) {
        m_pongListener(std::make_shared<KfWebSocketConnection>(connection), msg);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::onServerPongTimeout(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_pongTimeoutListener) {
        m_pongTimeoutListener(std::make_shared<KfWebSocketConnection>(connection), msg);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::onServerSocketInit(websocketpp::connection_hdl con, boost::asio::ip::tcp::socket&)
{
    /// @todo Check if passing the socket is useful
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_socketInitListener, connection);
}

void KfWebSocketServer::onServerTcpInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpInitListener, connection);
}

void KfWebSocketServer::onServerTcpPostInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpPostInitListener, connection);
}

void KfWebSocketServer::onServerTcpPreInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpPreInitListener, connection);
}

bool KfWebSocketServer::onServerValidate(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con);
    bool ret = true;
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_validateListener) {
        ret = m_validateListener(std::make_shared<KfWebSocketConnection>(connection));
    }
    _KFSIO_WSSERVER_UNLOCK;
    return ret;
}

