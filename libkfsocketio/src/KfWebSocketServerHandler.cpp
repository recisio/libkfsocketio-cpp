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

#include "KfWebSocketConImplWrapper.h"

#ifdef KFSIO_THREAD_SAFE
#define _KFSIO_WSSERVER_LOCK m_mutex.lock()
#define _KFSIO_WSSERVER_UNLOCK m_mutex.unlock()
#else 
#define _KFSIO_WSSERVER_LOCK
#define _KFSIO_WSSERVER_UNLOCK
#endif // KFSIO_THREAD_SAFE

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
    KfWebSocketConnection kfCon(KfWebSocketConImplWrapper({con})); \
    cb(kfCon); \
} \
_KFSIO_WSSERVER_UNLOCK 

KfWebSocketServerHandler::KfWebSocketServerHandler() :
#ifdef KFSIO_THREAD_SAFE
    m_mutex(),
#endif // KFSIO_THREAD_SAFE
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
    m_validateListener(nullptr)
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

void KfWebSocketServerHandler::unbindListeners()
{
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
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setOpenListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_openListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setCloseListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_closeListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setFailListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_failListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setHttpListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_httpListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setInterruptListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_interruptListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setSocketInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_socketInitListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setTcpInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpInitListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setTcpPostInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpPostInitListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setTcpPreInitListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_tcpPreInitListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setValidateListener(ConnectionListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_validateListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setMessageListener(MessageListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_messageListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setPingListener(PingListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pingListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setPongListener(PongListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pongListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::setPongTimeoutListener(PongListener listener)
{
    _KFSIO_WSSERVER_LOCK;
    m_pongTimeoutListener = listener;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::onServerOpen(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_openListener, connection);
}

void KfWebSocketServerHandler::onServerClose(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_closeListener, connection);
}

void KfWebSocketServerHandler::onServerFail(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_failListener, connection);
}

void KfWebSocketServerHandler::onServerHttp(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_httpListener, connection);
}

void KfWebSocketServerHandler::onServerInterrupt(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_interruptListener, connection);
}

void KfWebSocketServerHandler::onServerMessage(websocketpp::connection_hdl con, websocketpp::connection<websocketpp::config::asio>::message_ptr msgPtr)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    _KFSIO_WSSERVER_UNLOCK;
}

bool KfWebSocketServerHandler::onServerPing(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con);
    _KFSIO_WSSERVER_LOCK;
    _KFSIO_WSSERVER_UNLOCK;
    return true;
}

void KfWebSocketServerHandler::onServerPong(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::onServerPongTimeout(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::onServerSocketInit(websocketpp::connection_hdl con, boost::asio::ip::tcp::socket& sock)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFSIO_WSSERVER_LOCK;
    _KFSIO_WSSERVER_UNLOCK;
}

void KfWebSocketServerHandler::onServerTcpInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpInitListener, connection);
}

void KfWebSocketServerHandler::onServerTcpPostInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpPostInitListener, connection);
}

void KfWebSocketServerHandler::onServerTcpPreInit(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    _KFWEBSOCKET_SIMPLE_CONCB(m_tcpPreInitListener, connection);
}

bool KfWebSocketServerHandler::onServerValidate(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con);
    _KFSIO_WSSERVER_LOCK;
    _KFSIO_WSSERVER_UNLOCK;
    return true;
}
