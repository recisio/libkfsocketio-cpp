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
    connection = m_server->get_con_from_hdl(con); \
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
    KfWebSocketConnectionSPtr conSPtr = findConnection(con); \
    if (nullptr != conSPtr) { \
        cb(conSPtr.get()); \
    } \
} \
_KFSIO_WSSERVER_UNLOCK 

KfWebSocketServer::KfWebSocketServer() :
    m_mutex(),
    m_server(new websocketpp::server<websocketpp::config::asio>()),
    m_connections(),
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
    m_server->init_asio();
}

KfWebSocketServer::~KfWebSocketServer()
{
    unbindListeners();
    stop();
    delete m_server;
}

void KF_CALLCONV KfWebSocketServer::enableWebSocketOutputLog()
{
    m_server->set_access_channels(websocketpp::log::alevel::all);
}

void KF_CALLCONV KfWebSocketServer::disableWebSocketOutputLog()
{
    m_server->clear_access_channels(websocketpp::log::alevel::all);
}

KfWebSocketConnectionSPtr KF_CALLCONV KfWebSocketServer::findConnection(websocketpp::server<websocketpp::config::asio>::connection_ptr con)
{
    for (KfWebSocketConnectionSPtr connection : m_connections) {
        if (nullptr != connection && (*connection) == con) {
            return connection;
        }
    }

    return nullptr;
}

void KF_CALLCONV KfWebSocketServer::run(const uint16_t& port)
{
    start(port);
    m_server->run();
}

void KF_CALLCONV KfWebSocketServer::start(const uint16_t& port)
{
    _KFSIO_WSSERVER_LOCK;
    m_server->listen(port);
    m_server->start_accept();
    _KFSIO_WSSERVER_UNLOCK;
}

size_t KF_CALLCONV KfWebSocketServer::poll()
{
    return m_server->poll();
}

size_t KF_CALLCONV KfWebSocketServer::pollOne()
{
    return m_server->poll_one();
}

void KF_CALLCONV KfWebSocketServer::stop()
{
    _KFSIO_WSSERVER_LOCK;
    m_server->stop_listening();
    m_server->stop();
    m_connections.clear();
    _KFSIO_WSSERVER_UNLOCK;
}

bool KF_CALLCONV KfWebSocketServer::isListening() const
{
    return m_server->is_listening();
}

bool KF_CALLCONV KfWebSocketServer::isStopped() const
{
    return m_server->stopped();
}

bool KF_CALLCONV KfWebSocketServer::isSecure() const
{
    return m_server->is_secure();
}

void KF_CALLCONV KfWebSocketServer::unbindListeners()
{
    m_server->set_close_handler(nullptr);
    m_server->set_fail_handler(nullptr);
    m_server->set_http_handler(nullptr);
    m_server->set_interrupt_handler(nullptr);
    m_server->set_message_handler(nullptr);
    m_server->set_ping_handler(nullptr);
    m_server->set_pong_handler(nullptr);
    m_server->set_pong_timeout_handler(nullptr);
    m_server->set_socket_init_handler(nullptr);
    m_server->set_tcp_init_handler(nullptr);
    m_server->set_tcp_post_init_handler(nullptr);
    m_server->set_tcp_pre_init_handler(nullptr);
    m_server->set_validate_handler(nullptr);

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

void KF_CALLCONV KfWebSocketServer::setOpenListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_openListener = listener;
    if (nullptr != m_openListener) {
        m_server->set_open_handler(std::bind(&KfWebSocketServer::onServerOpen, this, std::placeholders::_1));
    } else {
        m_server->set_open_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServer::setCloseListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_closeListener = listener;
    if (nullptr != m_closeListener) {
        m_server->set_close_handler(std::bind(&KfWebSocketServer::onServerClose, this, std::placeholders::_1));
    } else {
        m_server->set_close_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setFailListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_failListener = listener;
    if (nullptr != m_failListener) {
        m_server->set_fail_handler(std::bind(&KfWebSocketServer::onServerFail, this, std::placeholders::_1));
    } else {
        m_server->set_fail_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setHttpListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_httpListener = listener;
    if (nullptr != m_httpListener) {
        m_server->set_http_handler(std::bind(&KfWebSocketServer::onServerHttp, this, std::placeholders::_1));
    } else {
        m_server->set_http_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setInterruptListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_interruptListener = listener;
    if (nullptr != m_interruptListener) {
        m_server->set_interrupt_handler(std::bind(&KfWebSocketServer::onServerInterrupt, this, std::placeholders::_1));
    } else {
        m_server->set_interrupt_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setSocketInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_socketInitListener = listener;
    if (nullptr != m_socketInitListener) {
        m_server->set_socket_init_handler(std::bind(&KfWebSocketServer::onServerSocketInit, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_socket_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setTcpInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpInitListener = listener;
    if (nullptr != m_tcpInitListener) {
        m_server->set_tcp_init_handler(std::bind(&KfWebSocketServer::onServerTcpInit, this, std::placeholders::_1));
    } else {
        m_server->set_tcp_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setTcpPostInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpPostInitListener = listener;
    if (nullptr != m_tcpPostInitListener) {
        m_server->set_tcp_post_init_handler(std::bind(&KfWebSocketServer::onServerTcpPostInit, this, std::placeholders::_1));
    } else {
        m_server->set_tcp_post_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setTcpPreInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpPreInitListener = listener;
    if (nullptr != m_tcpPreInitListener) {
        m_server->set_tcp_pre_init_handler(std::bind(&KfWebSocketServer::onServerTcpPreInit, this, std::placeholders::_1));
    } else {
        m_server->set_tcp_pre_init_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setValidateListener(ValidateListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_validateListener = listener;
    if (nullptr != m_validateListener) {
        m_server->set_validate_handler(std::bind(&KfWebSocketServer::onServerValidate, this, std::placeholders::_1));
    } else {
        m_server->set_validate_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setMessageListener(MessageListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_messageListener = listener;
    if (nullptr != m_messageListener) {
        m_server->set_message_handler(std::bind(&KfWebSocketServer::onServerMessage, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_message_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setPingListener(PingListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pingListener = listener;
    if (nullptr != m_pingListener) {
        m_server->set_ping_handler(std::bind(&KfWebSocketServer::onServerPing, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_ping_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setPongListener(PongListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pongListener = listener;
    if (nullptr != m_pongListener) {
        m_server->set_pong_handler(std::bind(&KfWebSocketServer::onServerPong, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_pong_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::setPongTimeoutListener(PongListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pongTimeoutListener = listener;
    if (nullptr != m_pongTimeoutListener) {
        m_server->set_pong_timeout_handler(std::bind(&KfWebSocketServer::onServerPongTimeout, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_pong_timeout_handler(nullptr);
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::onServerOpen(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);

    _KFSIO_WSSERVER_LOCK;
    KfWebSocketConnectionSPtr ptr = findConnection(connection);
    if (nullptr == ptr) {
        ptr = std::make_shared<KfWebSocketConnection>(connection);
        m_connections.push_back(ptr);
    }
    if (nullptr != m_openListener) {
        m_openListener(ptr.get());
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::onServerClose(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;

    KfWebSocketConnectionSPtr ptr = nullptr;
    std::vector<KfWebSocketConnectionSPtr>::iterator found = m_connections.begin();
    std::vector<KfWebSocketConnectionSPtr>::iterator conEnd = m_connections.end();
    for (; found != conEnd; ++found) {
        ptr = *found;
        if ((*ptr) == connection) {
            break;
        }
    }

    if (found == conEnd) {
        _KFSIO_WSSERVER_UNLOCK;
        return;
    }

    if (nullptr != ptr && nullptr != m_closeListener) {
        m_closeListener(ptr.get());
    }

    m_connections.erase(found);
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::onServerFail(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_failListener, connection);
}

void KF_CALLCONV KfWebSocketServer::onServerHttp(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_httpListener, connection);
}

void KF_CALLCONV KfWebSocketServer::onServerInterrupt(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_interruptListener, connection);
}

void KF_CALLCONV KfWebSocketServer::onServerMessage(websocketpp::connection_hdl con, websocketpp::connection<websocketpp::config::asio>::message_ptr msgPtr)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_messageListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            KfWebSocketMessagePtr message = new KfWebSocketMessage(msgPtr);
            m_messageListener(ptr.get(), message);
            delete message;
        }
    }
    _KFSIO_WSSERVER_UNLOCK;
}

bool KF_CALLCONV KfWebSocketServer::onServerPing(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con);
    bool ret = true;
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_pingListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            ret = m_pingListener(ptr.get(), msg.c_str());
        }
    }
    _KFSIO_WSSERVER_UNLOCK;
    return ret;
}

void KF_CALLCONV KfWebSocketServer::onServerPong(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_pongListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            m_pongListener(ptr.get(), msg.c_str());
        }
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::onServerPongTimeout(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_pongTimeoutListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            m_pongTimeoutListener(ptr.get(), msg.c_str());
        }
    }
    _KFSIO_WSSERVER_UNLOCK;
}

void KF_CALLCONV KfWebSocketServer::onServerSocketInit(websocketpp::connection_hdl con, boost::asio::ip::tcp::socket&)
{
    /// @todo Check if passing the socket is useful
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_socketInitListener, connection);
}

void KF_CALLCONV KfWebSocketServer::onServerTcpInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpInitListener, connection);
}

void KF_CALLCONV KfWebSocketServer::onServerTcpPostInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpPostInitListener, connection);
}

void KF_CALLCONV KfWebSocketServer::onServerTcpPreInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpPreInitListener, connection);
}

bool KF_CALLCONV KfWebSocketServer::onServerValidate(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con);
    bool ret = true;
    _KFSIO_WSSERVER_LOCK;
    if (nullptr != m_validateListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            ret = m_validateListener(ptr.get());
        }
    }
    _KFSIO_WSSERVER_UNLOCK;
    return ret;
}

