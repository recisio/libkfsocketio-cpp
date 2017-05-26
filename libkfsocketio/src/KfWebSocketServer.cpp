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

#include "KfWebSocketServerHandler.h"

#include "websocketpp/server.hpp"
#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

KfWebSocketServer::KfWebSocketServer() :
    m_handler(new KfWebSocketServerHandler())
{

}

KfWebSocketServer::~KfWebSocketServer()
{
    delete m_handler;
}

void KfWebSocketServer::run(const uint16_t& port) throw(std::exception)
{
    m_handler->m_server.listen(port);
    m_handler->m_server.start_accept();
    m_handler->m_server.run();
}

void KfWebSocketServer::start(const uint16_t& port) throw(std::exception)
{
    m_handler->m_server.listen(port);
    m_handler->m_server.start_accept();
}

size_t KfWebSocketServer::poll()
{
    return m_handler->m_server.poll();
}

size_t KfWebSocketServer::pollOne()
{
    return m_handler->m_server.poll_one();
}

void KfWebSocketServer::stop()
{
    m_handler->m_server.stop_listening();
    m_handler->m_server.stop();
}

bool KfWebSocketServer::isListening() const
{
    return m_handler->m_server.is_listening();
}

bool KfWebSocketServer::isStopped() const
{
    return m_handler->m_server.stopped();
}

bool KfWebSocketServer::isSecure() const
{
    return m_handler->m_server.is_secure();
}

void KfWebSocketServer::unbindListeners()
{
    m_handler->unbindListeners();
}

void KfWebSocketServer::setOpenListener(ConnectionListener listener)
{
    m_handler->setOpenListener(listener);
}

void KfWebSocketServer::setCloseListener(ConnectionListener listener)
{
    m_handler->setCloseListener(listener);
}

void KfWebSocketServer::setFailListener(ConnectionListener listener)
{
    m_handler->setFailListener(listener);
}

void KfWebSocketServer::setHttpListener(ConnectionListener listener)
{
    m_handler->setHttpListener(listener);
}

void KfWebSocketServer::setInterruptListener(ConnectionListener listener)
{
    m_handler->setInterruptListener(listener);
}

void KfWebSocketServer::setSocketInitListener(ConnectionListener listener)
{
    m_handler->setSocketInitListener(listener);
}

void KfWebSocketServer::setTcpInitListener(ConnectionListener listener)
{
    m_handler->setTcpInitListener(listener);
}

void KfWebSocketServer::setTcpPostInitListener(ConnectionListener listener)
{
    m_handler->setTcpPostInitListener(listener);
}

void KfWebSocketServer::setTcpPreInitListener(ConnectionListener listener)
{
    m_handler->setTcpPreInitListener(listener);
}

void KfWebSocketServer::setValidateListener(ValidateListener listener)
{
    m_handler->setValidateListener(listener);
}

void KfWebSocketServer::setMessageListener(MessageListener listener)
{
    m_handler->setMessageListener(listener);
}

void KfWebSocketServer::setPingListener(PingListener listener)
{
    m_handler->setPingListener(listener);
}

void KfWebSocketServer::setPongListener(PongListener listener)
{
    m_handler->setPongListener(listener);
}

void KfWebSocketServer::setPongTimeoutListener(PongListener listener)
{
    m_handler->setPongTimeoutListener(listener);
}
