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

class KfWebSocketConnection;

typedef std::shared_ptr<websocketpp::connection<websocketpp::config::asio>> WSConPtr;
typedef std::shared_ptr<KfWebSocketConnection> KfWebSocketConnectionSPtr;

class KfWebSocketConnection : public IKfWebSocketConnection {

public:
    KfWebSocketConnection(const WSConPtr& wrapper);
    KfWebSocketConnection(const KfWebSocketConnection& copy);

    virtual bool KF_CALLCONV operator==(const IKfWebSocketConnection& con) const;
    bool KF_CALLCONV operator==(const WSConPtr& con) const;

    // General timeouts

    virtual void KF_CALLCONV setOpenHandshakeTimeout(const long& timeout);
    virtual void KF_CALLCONV setCloseHandshakeTimeout(const long& timeout);

    // Proxy 

    virtual void KF_CALLCONV setProxyTimeout(const long& timeout);
    virtual void KF_CALLCONV setProxy(const char* proxy);
    virtual void KF_CALLCONV setProxyBasicAuth(const char* username, const char* passwd);
     
    virtual const char* KF_CALLCONV getProxy() const;

    // Http

    virtual void KF_CALLCONV setMaxHttpBodySize(const size_t& size);
    virtual void KF_CALLCONV setHttpBody(const char* body);
    virtual void KF_CALLCONV setHttpStatus(const HttpStatusCode& status, const char* message);
    virtual void KF_CALLCONV appendHttpHeader(const char* key, const char* value);

    virtual void KF_CALLCONV deferHttpResponse();
    virtual void KF_CALLCONV sendHttpResponse();

    virtual HttpStatusCode KF_CALLCONV getHttpResponseCode() const;
    virtual const char* KF_CALLCONV getHttpOrigin() const;
    virtual const char* KF_CALLCONV getHttpRequestBody() const;
    virtual const char* KF_CALLCONV getHttpResponseMessage() const;
    virtual const char* KF_CALLCONV getHttpRequestHeader(const char* key) const;
    virtual const char* KF_CALLCONV getHttpResponseHeader(const char* key) const;

    virtual void KF_CALLCONV removeHttpHeader(const char* key);
    virtual void KF_CALLCONV replaceHttpHeader(const char* key, const char* value);

    // Ping/Pong

    virtual void KF_CALLCONV setPongTimeout(const long& timeout);
    virtual void KF_CALLCONV ping(const char* payload);
    virtual void KF_CALLCONV pong(const char* payload);

    // Misc. 

    virtual void KF_CALLCONV setMaxMessageSize(const size_t& size);
    virtual void KF_CALLCONV addSubProtocol(const char* protocol);

    virtual size_t KF_CALLCONV getBufferedAmount() const;

    virtual void KF_CALLCONV readFrame();
    virtual void KF_CALLCONV writeFrame();
    virtual void KF_CALLCONV send(const char* payload, const OpCode& opcode);
    virtual void KF_CALLCONV close(const CloseStatus& status = CLOSESTATUS_NORMAL, const char* reason = "");

    virtual uint16_t KF_CALLCONV getPort() const;
    virtual int KF_CALLCONV getErrorCode() const;
    virtual const char* KF_CALLCONV getErrorMessage() const;
    virtual const char* KF_CALLCONV getHost() const;
    virtual const char* KF_CALLCONV getRemoteEndpoint() const;
    virtual const char* KF_CALLCONV getSubProtocol() const;
    virtual const char* KF_CALLCONV getUri() const;

    virtual ConnectionState KF_CALLCONV getState() const;

private:
    WSConPtr m_connection;

};

#endif // _KFWEBSOCKETCONNECTION_H
