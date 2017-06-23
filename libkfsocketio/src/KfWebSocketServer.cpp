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
m_mutex.lock(); \
if (nullptr != cb) { \
    KfWebSocketConnectionSPtr conSPtr = findConnection(con); \
    if (nullptr != conSPtr) { \
        cb(conSPtr.get()); \
    } \
} \
m_mutex.unlock(); 

KfWebSocketServer::KfWebSocketServer() :
    m_mutex(),
    m_server(new websocketpp::server<websocketpp::config::asio>()),
    m_connections(),
    m_openListener(nullptr),
    m_closeListener(nullptr),
    m_failListener(nullptr),
    m_httpListener(nullptr),
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
    m_mutex.lock();
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
    m_mutex.lock();
    m_server->listen(port);
    m_server->start_accept();
    m_mutex.unlock();
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
    m_mutex.lock();
    m_server->stop();
    m_server->stop_listening();
    m_connections.clear();
    m_mutex.unlock();
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
    m_server->set_message_handler(nullptr);
    m_server->set_ping_handler(nullptr);
    m_server->set_pong_handler(nullptr);
    m_server->set_pong_timeout_handler(nullptr);

    m_mutex.lock();
    m_openListener = nullptr;
    m_closeListener = nullptr;
    m_failListener = nullptr;
    m_httpListener = nullptr;
    m_messageListener = nullptr;
    m_pingListener = nullptr;
    m_pongListener = nullptr;
    m_pongTimeoutListener = nullptr;
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::setOpenListener(ConnectionListener listener)
{
    m_mutex.lock();
    m_openListener = listener;
    if (nullptr != m_openListener) {
        m_server->set_open_handler(std::bind(&KfWebSocketServer::onServerOpen, this, std::placeholders::_1));
    } else {
        m_server->set_open_handler(nullptr);
    }
    m_mutex.unlock();
}

void KfWebSocketServer::setCloseListener(ConnectionListener listener)
{
    m_mutex.lock();
    m_closeListener = listener;
    if (nullptr != m_closeListener) {
        m_server->set_close_handler(std::bind(&KfWebSocketServer::onServerClose, this, std::placeholders::_1));
    } else {
        m_server->set_close_handler(nullptr);
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::setFailListener(ConnectionListener listener)
{
    m_mutex.lock();
    m_failListener = listener;
    if (nullptr != m_failListener) {
        m_server->set_fail_handler(std::bind(&KfWebSocketServer::onServerFail, this, std::placeholders::_1));
    } else {
        m_server->set_fail_handler(nullptr);
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::setHttpListener(ConnectionListener listener)
{
    m_mutex.lock();
    m_httpListener = listener;
    if (nullptr != m_httpListener) {
        m_server->set_http_handler(std::bind(&KfWebSocketServer::onServerHttp, this, std::placeholders::_1));
    } else {
        m_server->set_http_handler(nullptr);
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::setMessageListener(MessageListener listener)
{
    m_mutex.lock();
    m_messageListener = listener;
    if (nullptr != m_messageListener) {
        m_server->set_message_handler(std::bind(&KfWebSocketServer::onServerMessage, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_message_handler(nullptr);
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::setPingListener(PingListener listener)
{
    m_mutex.lock();
    m_pingListener = listener;
    if (nullptr != m_pingListener) {
        m_server->set_ping_handler(std::bind(&KfWebSocketServer::onServerPing, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_ping_handler(nullptr);
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::setPongListener(PongListener listener)
{
    m_mutex.lock();
    m_pongListener = listener;
    if (nullptr != m_pongListener) {
        m_server->set_pong_handler(std::bind(&KfWebSocketServer::onServerPong, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_pong_handler(nullptr);
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::setPongTimeoutListener(PongListener listener)
{
    m_mutex.lock();
    m_pongTimeoutListener = listener;
    if (nullptr != m_pongTimeoutListener) {
        m_server->set_pong_timeout_handler(std::bind(&KfWebSocketServer::onServerPongTimeout, this, std::placeholders::_1, std::placeholders::_2));
    } else {
        m_server->set_pong_timeout_handler(nullptr);
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::onServerOpen(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);

    m_mutex.lock();
    KfWebSocketConnectionSPtr ptr = findConnection(connection);
    if (nullptr == ptr) {
        ptr = std::make_shared<KfWebSocketConnection>(connection);
        m_connections.push_back(ptr);
    }
    if (nullptr != m_openListener) {
        m_openListener(ptr.get());
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::onServerClose(websocketpp::connection_hdl con)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    m_mutex.lock();

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
        m_mutex.unlock();
        return;
    }

    if (nullptr != ptr && nullptr != m_closeListener) {
        m_closeListener(ptr.get());
    }

    m_connections.erase(found);
    m_mutex.unlock();
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


void KF_CALLCONV KfWebSocketServer::onServerMessage(websocketpp::connection_hdl con, websocketpp::connection<websocketpp::config::asio>::message_ptr msgPtr)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    m_mutex.lock();
    if (nullptr != m_messageListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            KfWebSocketMessagePtr message = new KfWebSocketMessage(msgPtr);
            m_messageListener(ptr.get(), message);
            delete message;
        }
    }
    m_mutex.unlock();
}

bool KF_CALLCONV KfWebSocketServer::onServerPing(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETBOOL(con);
    bool ret = true;
    m_mutex.lock();
    if (nullptr != m_pingListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            ret = m_pingListener(ptr.get(), msg.c_str());
        }
    }
    m_mutex.unlock();
    return ret;
}

void KF_CALLCONV KfWebSocketServer::onServerPong(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    m_mutex.lock();
    if (nullptr != m_pongListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            m_pongListener(ptr.get(), msg.c_str());
        }
    }
    m_mutex.unlock();
}

void KF_CALLCONV KfWebSocketServer::onServerPongTimeout(websocketpp::connection_hdl con, std::string msg)
{
    _KFWEBSOCKET_CAST_CONNECTION_CBRETVOID(con);
    m_mutex.lock();
    if (nullptr != m_pongTimeoutListener) {
        KfWebSocketConnectionSPtr ptr = findConnection(connection);
        if (nullptr != ptr) {
            m_pongTimeoutListener(ptr.get(), msg.c_str());
        }
    }
    m_mutex.unlock();
}
