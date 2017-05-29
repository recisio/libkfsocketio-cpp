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

#ifdef LIBKFSOCKETIO_EXPORTS
#define LIBKFSOCKETIO_WEBSOCKETCONNECTION_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_WEBSOCKETCONNECTION_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#include <string>
#include <vector>

struct KfWebSocketConImplWrapper;

class LIBKFSOCKETIO_WEBSOCKETCONNECTION_DLL KfWebSocketConnection {

public:
    typedef enum {
        OPCODE_CONTINUATION = 0x0,
        OPCODE_TEXT = 0x1,
        OPCODE_BINARY = 0x2,
        OPCODE_RSV3 = 0x3,
        OPCODE_RSV4 = 0x4,
        OPCODE_RSV5 = 0x5,
        OPCODE_RSV6 = 0x6,
        OPCODE_RSV7 = 0x7,
        OPCODE_CLOSE = 0x8,
        OPCODE_PING = 0x9,
        OPCODE_PONG = 0xA,
        OPCODE_CONTROL_RSVB = 0xB,
        OPCODE_CONTROL_RSVC = 0xC,
        OPCODE_CONTROL_RSVD = 0xD,
        OPCODE_CONTROL_RSVE = 0xE,
        OPCODE_CONTROL_RSVF = 0xF
    } OpCode;

    typedef enum {
        CLOSESTATUS_BLANK = 0,
        CLOSESTATUS_OMIT_HANDSHAKE = 1,
        CLOSESTATUS_FORCE_TCP_DROP = 2,
        CLOSESTATUS_NORMAL = 1000,
        CLOSESTATUS_GOING_AWAY = 1001,
        CLOSESTATUS_PROTOCOL_ERROR = 1002,
        CLOSESTATUS_UNSUPPORTED_DATA = 1003,
        CLOSESTATUS_NO_STATUS = 1005,
        CLOSESTATUS_ABNORMAL_CLOSE = 1006,
        CLOSESTATUS_INVALID_PAYLOAD = 1007,
        CLOSESTATUS_POLICY_VIOLATION = 1008,
        CLOSESTATUS_MESSAGE_TOO_BIG = 1009,
        CLOSESTATUS_EXTENSION_REQUIRED = 1010,
        CLOSESTATUS_INTERNAL_ENDPOINT_ERROR = 1011,
        CLOSESTATUS_SERVICE_RESTART = 1012,
        CLOSESTATUS_TRY_AGAIN_LATER = 1013,
        CLOSESTATUS_TLS_HANDSHAKE = 1015,
        CLOSESTATUS_SUBPROTOCOL_ERROR = 3000,
        CLOSESTATUS_INVALID_SUBPROTOCOL_DATA = 3001,
        CLOSESTATUS_INVALID_LOW = 999,
        CLOSESTATUS_INVALID_HIGH = 5000
    } CloseStatus;

    typedef enum {
        HTTP_STATUS_UNINITIALIZED = 0,

        HTTP_STATUS_CONTINUE_CODE = 100,
        HTTP_STATUS_SWITCHING_PROTOCOL = 101,

        HTTP_STATUS_OK = 200,
        HTTP_STATUS_CREATED = 201,
        HTTP_STATUS_ACCEPTED = 202,
        HTTP_STATUS_NON_AUTHORITATIVE_INFO = 203,
        HTTP_STATUS_NO_CONTENT = 204,
        HTTP_STATUS_RESET_CONTENT = 205,
        HTTP_STATUS_PARTIAL_CONTENT = 206,

        HTTP_STATUS_MULTIPLE_CHOICES = 300,
        HTTP_STATUS_MOVED_PERMANENTLY = 301,
        HTTP_STATUS_FOUND = 302,
        HTTP_STATUS_SEE_OTHER = 303,
        HTTP_STATUS_NOT_MODIFIED = 304,
        HTTP_STATUS_USE_PROXY = 305,
        HTTP_STATUS_TEMPORARY_REDIRECT = 307,

        HTTP_STATUS_BAD_REQUEST = 400,
        HTTP_STATUS_UNAUTHORIZED = 401,
        HTTP_STATUS_PAYMENT_REQUIRED = 402,
        HTTP_STATUS_FORBIDDEN = 403,
        HTTP_STATUS_NOT_FOUND = 404,
        HTTP_STATUS_METHOD_NOT_ALLOWED = 405,
        HTTP_STATUS_NOT_ACCEPTABLE = 406,
        HTTP_STATUS_PROXY_AUTH_REQUIRED = 407,
        HTTP_STATUS_REQUEST_TIMEOUT = 408,
        HTTP_STATUS_CONFLICT = 409,
        HTTP_STATUS_GONE = 410,
        HTTP_STATUS_LENGTH_REQUIRED = 411,
        HTTP_STATUS_PRECOND_FAILED = 412,
        HTTP_STATUS_REQ_ENTITY_TOO_LARGE = 413,
        HTTP_STATUS_REQ_URI_TOO_LONG = 414,
        HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE = 415,
        HTTP_STATUS_REQ_RANGE_NOT_SATISFIABLE = 416,
        HTTP_STATUS_EXPECTATION_FAILED = 417,
        HTTP_STATUS_IM_A_TEAPOT = 418,
        HTTP_STATUS_UPGRADE_REQUIRED = 426,
        HTTP_STATUS_PRECOND_REQUIRED = 428,
        HTTP_STATUS_TOO_MANY_REQUESTS = 429,
        HTTP_STATUS_REQ_HEADER_FIELDS_TOO_LARGE = 431,

        HTTP_STATUS_INTERNAL_SRV_ERROR = 500,
        HTTP_STATUS_NOT_IMPLEMENTED = 501,
        HTTP_STATUS_BAD_GATEWAY = 502,
        HTTP_STATUS_SERVICE_UNAVAILABLE = 503,
        HTTP_STATUS_GATEWAY_TIMEOUT = 504,
        HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED = 505,
        HTTP_STATUS_NOT_EXTENDED = 510,
        HTTP_STATUS_NETWORK_AUTH_REQUIRED = 511
    } HttpStatusCode;

    typedef enum {
        STATE_CONNECTING = 0,
        STATE_OPEN = 1,
        STATE_CLOSING = 2,
        STATE_CLOSED = 3
    } ConnectionState;

public:
    KfWebSocketConnection(const KfWebSocketConImplWrapper& wrapper);
    KfWebSocketConnection(const KfWebSocketConnection& copy);
    virtual ~KfWebSocketConnection();

    bool operator==(const KfWebSocketConnection& con);

    // General timeouts

    void setOpenHandshakeTimeout(const long& timeout);
    void setCloseHandshakeTimeout(const long& timeout);

    // Proxy 

    void setProxyTimeout(const long& timeout);
    void setProxy(const std::string& proxy);
    void setProxyBasicAuth(const std::string& username, const std::string& passwd);

    std::string getProxy() const;

    // Http

    void setMaxHttpBodySize(const size_t& size);
    void setHttpBody(const std::string& body);
    void setHttpStatus(const HttpStatusCode& status, const std::string& message);
    void appendHttpHeader(const std::string& key, const std::string& value);

    void deferHttpResponse();
    void sendHttpResponse();

    HttpStatusCode getHttpResponseCode() const;
    std::string getHttpOrigin() const;
    std::string getHttpRequestBody() const;
    std::string getHttpResponseMessage() const;
    std::string getHttpRequestHeader(const std::string& key) const;
    std::string getHttpResponseHeader(const std::string& key) const;

    void removeHttpHeader(const std::string& key);
    void replaceHttpHeader(const std::string& key, const std::string& value);

    // Ping/Pong

    void setPongTimeout(const long& timeout);
    void ping(const std::string& payload);
    void pong(const std::string& payload);

    // Misc. 

    void setMaxMessageSize(const size_t& size);
    void addSubProtocol(const std::string& protocol);

    size_t getBufferedAmount() const;

    void readFrame();
    void writeFrame();
    void send(const std::string& payload, const OpCode& opcode);
    void close(const CloseStatus& status = CLOSESTATUS_NORMAL, const std::string& reason = "");

    uint16_t getPort() const;
    int getErrorCode() const;
    std::string getErrorMessage() const;
    std::string getHost() const;
    std::string getRemoteEndpoint() const;
    std::vector<std::string> getRequestedSubProtocols() const;
    std::string getSubProtocol() const;
    std::string getUri() const;

    ConnectionState getState() const;

private:
    KfWebSocketConImplWrapper* m_connection;

};

#endif // _KFWEBSOCKETCONNECTION_H
