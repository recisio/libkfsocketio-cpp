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

KfWebSocketConnection::KfWebSocketConnection(const WSConPtr& wrapper) :
    m_connection(wrapper)
{
}

KfWebSocketConnection::KfWebSocketConnection(const KfWebSocketConnection& copy) :
    m_connection(copy.m_connection)
{
}

bool KF_CALLCONV KfWebSocketConnection::operator==(const IKfWebSocketConnection& con)  const
{
    return ((const KfWebSocketConnection&) con).m_connection == m_connection;
}

bool KF_CALLCONV KfWebSocketConnection::operator==(const WSConPtr& con) const
{
    return m_connection == con;
}

void KF_CALLCONV KfWebSocketConnection::setOpenHandshakeTimeout(const long& timeout)
{
    m_connection->set_open_handshake_timeout(timeout);
}

void KF_CALLCONV KfWebSocketConnection::setCloseHandshakeTimeout(const long& timeout)
{
    m_connection->set_close_handshake_timeout(timeout);
}

void KF_CALLCONV KfWebSocketConnection::setProxyTimeout(const long& timeout)
{
    m_connection->set_proxy_timeout(timeout);
}

void KF_CALLCONV KfWebSocketConnection::setProxy(const char* proxy)
{
    m_connection->set_proxy(proxy);
}

void KF_CALLCONV KfWebSocketConnection::setProxyBasicAuth(const char* username, const char* passwd)
{
    m_connection->set_proxy_basic_auth(username, passwd);
}

const char* KF_CALLCONV KfWebSocketConnection::getProxy() const
{
    return m_connection->get_proxy().c_str();
}

void KF_CALLCONV KfWebSocketConnection::setMaxHttpBodySize(const size_t& size)
{
    m_connection->set_max_http_body_size(size);
}

void KF_CALLCONV KfWebSocketConnection::setHttpBody(const char* body)
{
    m_connection->set_body(body);
}

void KF_CALLCONV KfWebSocketConnection::setHttpStatus(const HttpStatusCode& status, const char* message)
{
    m_connection->set_status((websocketpp::http::status_code::value) status, message);
}

void KF_CALLCONV KfWebSocketConnection::appendHttpHeader(const char* key, const char* value)
{
    m_connection->append_header(key, value);
}

void KF_CALLCONV KfWebSocketConnection::deferHttpResponse()
{
    m_connection->defer_http_response();
}

void KF_CALLCONV KfWebSocketConnection::sendHttpResponse()
{
    m_connection->send_http_response();
}

const char* KF_CALLCONV KfWebSocketConnection::getHttpOrigin() const
{
    return m_connection->get_origin().c_str();
}

const char* KF_CALLCONV KfWebSocketConnection::getHttpRequestBody() const
{
    return m_connection->get_request_body().c_str();
}

KfWebSocketConnection::HttpStatusCode KF_CALLCONV KfWebSocketConnection::getHttpResponseCode() const
{
    return (HttpStatusCode) m_connection->get_response_code();
}

const char* KF_CALLCONV KfWebSocketConnection::getHttpResponseMessage() const
{
    return m_connection->get_response_msg().c_str();
}

const char* KF_CALLCONV KfWebSocketConnection::getHttpRequestHeader(const char* key) const
{
    return m_connection->get_request_header(key).c_str();
}

const char* KF_CALLCONV KfWebSocketConnection::getHttpResponseHeader(const char* key) const
{
    return m_connection->get_response_header(key).c_str();
}

void KF_CALLCONV KfWebSocketConnection::removeHttpHeader(const char* key)
{
    m_connection->remove_header(key);
}

void KF_CALLCONV KfWebSocketConnection::replaceHttpHeader(const char* key, const char* value)
{
    m_connection->replace_header(key, value);
}

void KF_CALLCONV KfWebSocketConnection::setPongTimeout(const long& timeout)
{
    m_connection->set_pong_timeout(timeout);
}

void KF_CALLCONV KfWebSocketConnection::ping(const char* payload)
{
    m_connection->ping(payload);
}

void KF_CALLCONV KfWebSocketConnection::pong(const char* payload)
{
    m_connection->pong(payload);
}

void KF_CALLCONV KfWebSocketConnection::setMaxMessageSize(const size_t& size)
{
    m_connection->set_max_message_size(size);
}

void KF_CALLCONV KfWebSocketConnection::addSubProtocol(const char* protocol)
{
    m_connection->add_subprotocol(protocol);
}

size_t KF_CALLCONV KfWebSocketConnection::getBufferedAmount() const
{
    return m_connection->get_buffered_amount();
}

void KF_CALLCONV KfWebSocketConnection::readFrame()
{
    m_connection->read_frame();
}

void KF_CALLCONV KfWebSocketConnection::writeFrame()
{
    m_connection->write_frame();
}

void KF_CALLCONV KfWebSocketConnection::send(const char* payload, const OpCode& opcode)
{
    m_connection->send(std::string(payload), (websocketpp::frame::opcode::value) opcode);
}

void KF_CALLCONV KfWebSocketConnection::close(const CloseStatus& status, const char* reason)
{
    m_connection->close((websocketpp::close::status::value) status, reason);
}

uint16_t KF_CALLCONV KfWebSocketConnection::getPort() const
{
    return m_connection->get_port();
}

int KF_CALLCONV KfWebSocketConnection::getErrorCode() const
{
    return m_connection->get_ec().value();
}

const char* KF_CALLCONV KfWebSocketConnection::getErrorMessage() const
{
    return m_connection->get_ec().message().c_str();
}

const char* KF_CALLCONV KfWebSocketConnection::getHost() const
{
    return m_connection->get_host().c_str();
}

const char* KF_CALLCONV KfWebSocketConnection::getRemoteEndpoint() const
{
    return m_connection->get_remote_endpoint().c_str();
}

const char* KF_CALLCONV KfWebSocketConnection::getSubProtocol() const
{
    return m_connection->get_subprotocol().c_str();
}

const char* KF_CALLCONV KfWebSocketConnection::getUri() const
{
    auto uri = m_connection->get_uri();
    if (nullptr == uri) {
        return "";
    }
    return uri->str().c_str();
}

KfWebSocketConnection::ConnectionState KF_CALLCONV KfWebSocketConnection::getState() const
{
    if (nullptr == m_connection) {
        return STATE_CLOSED;
    }
    return (ConnectionState) m_connection->get_state();
}

