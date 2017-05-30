#ifndef _KFWEBSOCKETCONNECTION_H
#define _KFWEBSOCKETCONNECTION_H

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

#include <string>
#include <vector>
#include <memory>

#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"
#include "IKfWebSocketConnection.h"

typedef std::shared_ptr<websocketpp::connection<websocketpp::config::asio>> WSConPtr;


class KfWebSocketConnection : public IKfWebSocketConnection {

public:
    KfWebSocketConnection(const WSConPtr& wrapper);
    KfWebSocketConnection(const KfWebSocketConnection& copy);

    virtual bool operator==(const IKfWebSocketConnection& con) const;

    // General timeouts

    virtual void setOpenHandshakeTimeout(const long& timeout);
    virtual void setCloseHandshakeTimeout(const long& timeout);

    // Proxy 

    virtual void setProxyTimeout(const long& timeout);
    virtual void setProxy(const std::string& proxy);
    virtual void setProxyBasicAuth(const std::string& username, const std::string& passwd);
     
    virtual std::string getProxy() const;

    // Http

    virtual void setMaxHttpBodySize(const size_t& size);
    virtual void setHttpBody(const std::string& body);
    virtual void setHttpStatus(const HttpStatusCode& status, const std::string& message);
    virtual void appendHttpHeader(const std::string& key, const std::string& value);

    virtual void deferHttpResponse();
    virtual void sendHttpResponse();

    virtual HttpStatusCode getHttpResponseCode() const;
    virtual std::string getHttpOrigin() const;
    virtual std::string getHttpRequestBody() const;
    virtual std::string getHttpResponseMessage() const;
    virtual std::string getHttpRequestHeader(const std::string& key) const;
    virtual std::string getHttpResponseHeader(const std::string& key) const;

    virtual void removeHttpHeader(const std::string& key);
    virtual void replaceHttpHeader(const std::string& key, const std::string& value);

    // Ping/Pong

    virtual void setPongTimeout(const long& timeout);
    virtual void ping(const std::string& payload);
    virtual void pong(const std::string& payload);

    // Misc. 

    virtual void setMaxMessageSize(const size_t& size);
    virtual void addSubProtocol(const std::string& protocol);

    virtual size_t getBufferedAmount() const;

    virtual void readFrame();
    virtual void writeFrame();
    virtual void send(const std::string& payload, const OpCode& opcode);
    virtual void close(const CloseStatus& status = CLOSESTATUS_NORMAL, const std::string& reason = "");

    virtual uint16_t getPort() const;
    virtual int getErrorCode() const;
    virtual std::string getErrorMessage() const;
    virtual std::string getHost() const;
    virtual std::string getRemoteEndpoint() const;
    virtual std::vector<std::string> getRequestedSubProtocols() const;
    virtual std::string getSubProtocol() const;
    virtual std::string getUri() const;

    virtual ConnectionState getState() const;

private:
    WSConPtr m_connection;

};

#endif // _KFWEBSOCKETCONNECTION_H
