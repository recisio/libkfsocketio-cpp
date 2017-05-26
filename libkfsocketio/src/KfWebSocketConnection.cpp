#include "KfWebSocketConnection.h"

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

#include "KfWebSocketConImplWrapper.h"


KfWebSocketConnection::KfWebSocketConnection() :
    m_connection(new KfWebSocketConImplWrapper())
{
}

KfWebSocketConnection::KfWebSocketConnection(const KfWebSocketConnection& copy) :
    m_connection(new KfWebSocketConImplWrapper())
{
    m_connection->connection = copy.m_connection->connection;
}

KfWebSocketConnection::KfWebSocketConnection(const KfWebSocketConImplWrapper& wrapper) :
    m_connection(new KfWebSocketConImplWrapper())
{
    m_connection->connection = wrapper.connection;
}

KfWebSocketConnection::~KfWebSocketConnection()
{
    delete m_connection;
}

void KfWebSocketConnection::setOpenHandshakeTimeout(const long& timeout)
{

}

void KfWebSocketConnection::setCloseHandshakeTimeout(const long& timeout)
{

}

void KfWebSocketConnection::setProxyTimeout(const long& timeout)
{

}

void KfWebSocketConnection::setProxy(const std::string& proxy)
{

}

void KfWebSocketConnection::setProxyBasicAuth(const std::string& username, const std::string& passwd)
{

}

std::string KfWebSocketConnection::getProxy() const
{
    return "";
}

void KfWebSocketConnection::setMaxHttpBodySize(const size_t& size)
{

}

void KfWebSocketConnection::setHttpBody(const std::string& body)
{

}

void KfWebSocketConnection::setHttpStatus(const HttpStatusCode& status, const std::string& message)
{

}

void KfWebSocketConnection::appendHttpHeader(const std::string& key, const std::string& value)
{

}

void KfWebSocketConnection::deferHttpResponse()
{

}

void KfWebSocketConnection::sendHttpResponse()
{

}

std::string KfWebSocketConnection::getHttpOrigin() const
{
    return "";
}

std::string KfWebSocketConnection::getHttpRequestBody() const
{
    return "";
}

unsigned int KfWebSocketConnection::getHttpResponseCode() const
{
    return 0;
}

std::string KfWebSocketConnection::getHttpResponseMessage() const
{
    return "";
}

std::string KfWebSocketConnection::getHttpRequestHeader(const std::string& key) const
{
    return "";
}

std::string KfWebSocketConnection::getHttpResponseHeader(const std::string& key) const
{
    return "";
}

void KfWebSocketConnection::removeHttpHeader(const std::string& key)
{

}

void KfWebSocketConnection::replaceHttpHeader(const std::string& key, const std::string& value)
{

}

void KfWebSocketConnection::setPongTimeout(const long& timeout)
{

}

void KfWebSocketConnection::ping(const std::string& payload)
{

}

void KfWebSocketConnection::pong(const std::string& payload)
{

}

void KfWebSocketConnection::setMaxMessageSize(const size_t& size)
{

}

void KfWebSocketConnection::addSubProtocol(const std::string& protocol)
{

}

size_t KfWebSocketConnection::getBufferedAmount() const
{
    return (size_t) 0;
}

void KfWebSocketConnection::readFrame()
{

}

void KfWebSocketConnection::writeFrame()
{

}

void KfWebSocketConnection::send(const std::string& payload, const OpCode& opcode)
{

}

void KfWebSocketConnection::close(const CloseStatus& status, const std::string& reason)
{

}

uint16_t KfWebSocketConnection::getPort() const
{
    return 0;
}

int KfWebSocketConnection::getErrorCode() const
{
    return 0;
}

std::string KfWebSocketConnection::getErrorMessage() const
{
    return "";
}

std::string KfWebSocketConnection::getHost() const
{
    return "";
}

std::string KfWebSocketConnection::getRemoteEndpoint() const
{
    return "";
}

std::vector<std::string> KfWebSocketConnection::getRequestedSubProtocols() const
{
    return std::vector<std::string>();
}

std::string KfWebSocketConnection::getSubProtocol() const
{
    return "";
}

std::string KfWebSocketConnection::getUri() const
{
    return "";
}

std::string KfWebSocketConnection::getMessage() const
{
    return "";
}

