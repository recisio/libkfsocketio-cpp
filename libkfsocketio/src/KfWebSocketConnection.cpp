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

KfWebSocketConnection::KfWebSocketConnection(const KfWebSocketConImplWrapper& wrapper) :
    m_connection(new KfWebSocketConImplWrapper())
{
    m_connection->connection = wrapper.connection;
}

KfWebSocketConnection::KfWebSocketConnection(const KfWebSocketConnection& copy) :
    m_connection(new KfWebSocketConImplWrapper())
{
    m_connection->connection = copy.m_connection->connection;
}

KfWebSocketConnection::~KfWebSocketConnection()
{
    delete m_connection;
}

bool KfWebSocketConnection::operator==(const KfWebSocketConnection& con)  const
{
    return con.m_connection->connection == m_connection->connection;
}

void KfWebSocketConnection::setOpenHandshakeTimeout(const long& timeout)
{
    m_connection->connection->set_open_handshake_timeout(timeout);
}

void KfWebSocketConnection::setCloseHandshakeTimeout(const long& timeout)
{
    m_connection->connection->set_close_handshake_timeout(timeout);
}

void KfWebSocketConnection::setProxyTimeout(const long& timeout)
{
    m_connection->connection->set_proxy_timeout(timeout);
}

void KfWebSocketConnection::setProxy(const std::string& proxy)
{
    m_connection->connection->set_proxy(proxy);
}

void KfWebSocketConnection::setProxyBasicAuth(const std::string& username, const std::string& passwd)
{
    m_connection->connection->set_proxy_basic_auth(username, passwd);
}

std::string KfWebSocketConnection::getProxy() const
{
    return m_connection->connection->get_proxy();
}

void KfWebSocketConnection::setMaxHttpBodySize(const size_t& size)
{
    m_connection->connection->set_max_http_body_size(size);
}

void KfWebSocketConnection::setHttpBody(const std::string& body)
{
    m_connection->connection->set_body(body);
}

void KfWebSocketConnection::setHttpStatus(const HttpStatusCode& status, const std::string& message)
{
    m_connection->connection->set_status((websocketpp::http::status_code::value) status, message);
}

void KfWebSocketConnection::appendHttpHeader(const std::string& key, const std::string& value)
{
    m_connection->connection->append_header(key, value);
}

void KfWebSocketConnection::deferHttpResponse()
{
    m_connection->connection->defer_http_response();
}

void KfWebSocketConnection::sendHttpResponse()
{
    m_connection->connection->send_http_response();
}

std::string KfWebSocketConnection::getHttpOrigin() const
{
    return m_connection->connection->get_origin();
}

std::string KfWebSocketConnection::getHttpRequestBody() const
{
    return m_connection->connection->get_request_body();
}

KfWebSocketConnection::HttpStatusCode KfWebSocketConnection::getHttpResponseCode() const
{
    return (HttpStatusCode) m_connection->connection->get_response_code();
}

std::string KfWebSocketConnection::getHttpResponseMessage() const
{
    return m_connection->connection->get_response_msg();
}

std::string KfWebSocketConnection::getHttpRequestHeader(const std::string& key) const
{
    return m_connection->connection->get_request_header(key);
}

std::string KfWebSocketConnection::getHttpResponseHeader(const std::string& key) const
{
    return m_connection->connection->get_response_header(key);
}

void KfWebSocketConnection::removeHttpHeader(const std::string& key)
{
    m_connection->connection->remove_header(key);
}

void KfWebSocketConnection::replaceHttpHeader(const std::string& key, const std::string& value)
{
    m_connection->connection->replace_header(key, value);
}

void KfWebSocketConnection::setPongTimeout(const long& timeout)
{
    m_connection->connection->set_pong_timeout(timeout);
}

void KfWebSocketConnection::ping(const std::string& payload)
{
    m_connection->connection->ping(payload);
}

void KfWebSocketConnection::pong(const std::string& payload)
{
    m_connection->connection->pong(payload);
}

void KfWebSocketConnection::setMaxMessageSize(const size_t& size)
{
    m_connection->connection->set_max_message_size(size);
}

void KfWebSocketConnection::addSubProtocol(const std::string& protocol)
{
    m_connection->connection->add_subprotocol(protocol);
}

size_t KfWebSocketConnection::getBufferedAmount() const
{
    return m_connection->connection->get_buffered_amount();
}

void KfWebSocketConnection::readFrame()
{
    m_connection->connection->read_frame();
}

void KfWebSocketConnection::writeFrame()
{
    m_connection->connection->write_frame();
}

void KfWebSocketConnection::send(const std::string& payload, const OpCode& opcode)
{
    m_connection->connection->send(payload, (websocketpp::frame::opcode::value) opcode);
}

void KfWebSocketConnection::close(const CloseStatus& status, const std::string& reason)
{
    m_connection->connection->close((websocketpp::close::status::value) status, reason);
}

uint16_t KfWebSocketConnection::getPort() const
{
    return m_connection->connection->get_port();
}

int KfWebSocketConnection::getErrorCode() const
{
    return m_connection->connection->get_ec().value();
}

std::string KfWebSocketConnection::getErrorMessage() const
{
    return m_connection->connection->get_ec().message();
}

std::string KfWebSocketConnection::getHost() const
{
    return m_connection->connection->get_host();
}

std::string KfWebSocketConnection::getRemoteEndpoint() const
{
    return m_connection->connection->get_remote_endpoint();
}

std::vector<std::string> KfWebSocketConnection::getRequestedSubProtocols() const
{
    return m_connection->connection->get_requested_subprotocols();
}

std::string KfWebSocketConnection::getSubProtocol() const
{
    return m_connection->connection->get_subprotocol();
}

std::string KfWebSocketConnection::getUri() const
{
    auto uri = m_connection->connection->get_uri();
    if (nullptr == uri) {
        return "";
    }
    return uri->str();
}

KfWebSocketConnection::ConnectionState KfWebSocketConnection::getState() const
{
    if (nullptr == m_connection->connection) {
        return STATE_CLOSED;
    }
    return (ConnectionState) m_connection->connection->get_state();
}

