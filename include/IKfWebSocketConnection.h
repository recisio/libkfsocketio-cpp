#ifndef _IKFWEBSOCKETCONNECTION_H
#define _IKFWEBSOCKETCONNECTION_H

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

class IKfWebSocketConnection {

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
        KFHTTP_STATUS_UNINITIALIZED = 0,

        KFHTTP_STATUS_CONTINUE_CODE = 100,
        KFHTTP_STATUS_SWITCHING_PROTOCOL = 101,

        KFHTTP_STATUS_OK = 200,
        KFHTTP_STATUS_CREATED = 201,
        KFHTTP_STATUS_ACCEPTED = 202,
        KFHTTP_STATUS_NON_AUTHORITATIVE_INFO = 203,
        KFHTTP_STATUS_NO_CONTENT = 204,
        KFHTTP_STATUS_RESET_CONTENT = 205,
        KFHTTP_STATUS_PARTIAL_CONTENT = 206,

        KFHTTP_STATUS_MULTIPLE_CHOICES = 300,
        KFHTTP_STATUS_MOVED_PERMANENTLY = 301,
        KFHTTP_STATUS_FOUND = 302,
        KFHTTP_STATUS_SEE_OTHER = 303,
        KFHTTP_STATUS_NOT_MODIFIED = 304,
        KFHTTP_STATUS_USE_PROXY = 305,
        KFHTTP_STATUS_TEMPORARY_REDIRECT = 307,

        KFHTTP_STATUS_BAD_REQUEST = 400,
        KFHTTP_STATUS_UNAUTHORIZED = 401,
        KFHTTP_STATUS_PAYMENT_REQUIRED = 402,
        KFHTTP_STATUS_FORBIDDEN = 403,
        KFHTTP_STATUS_NOT_FOUND = 404,
        KFHTTP_STATUS_METHOD_NOT_ALLOWED = 405,
        KFHTTP_STATUS_NOT_ACCEPTABLE = 406,
        KFHTTP_STATUS_PROXY_AUTH_REQUIRED = 407,
        KFHTTP_STATUS_REQUEST_TIMEOUT = 408,
        KFHTTP_STATUS_CONFLICT = 409,
        KFHTTP_STATUS_GONE = 410,
        KFHTTP_STATUS_LENGTH_REQUIRED = 411,
        KFHTTP_STATUS_PRECOND_FAILED = 412,
        KFHTTP_STATUS_REQ_ENTITY_TOO_LARGE = 413,
        KFHTTP_STATUS_REQ_URI_TOO_LONG = 414,
        KFHTTP_STATUS_UNSUPPORTED_MEDIA_TYPE = 415,
        KFHTTP_STATUS_REQ_RANGE_NOT_SATISFIABLE = 416,
        KFHTTP_STATUS_EXPECTATION_FAILED = 417,
        KFHTTP_STATUS_IM_A_TEAPOT = 418,
        KFHTTP_STATUS_UPGRADE_REQUIRED = 426,
        KFHTTP_STATUS_PRECOND_REQUIRED = 428,
        KFHTTP_STATUS_TOO_MANY_REQUESTS = 429,
        KFHTTP_STATUS_REQ_HEADER_FIELDS_TOO_LARGE = 431,

        KFHTTP_STATUS_INTERNAL_SRV_ERROR = 500,
        KFHTTP_STATUS_NOT_IMPLEMENTED = 501,
        KFHTTP_STATUS_BAD_GATEWAY = 502,
        KFHTTP_STATUS_SERVICE_UNAVAILABLE = 503,
        KFHTTP_STATUS_GATEWAY_TIMEOUT = 504,
        KFHTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED = 505,
        KFHTTP_STATUS_NOT_EXTENDED = 510,
        KFHTTP_STATUS_NETWORK_AUTH_REQUIRED = 511
    } HttpStatusCode;

    typedef enum {
        STATE_CONNECTING = 0,
        STATE_OPEN = 1,
        STATE_CLOSING = 2,
        STATE_CLOSED = 3
    } ConnectionState;

public:
    virtual bool operator==(const IKfWebSocketConnection& con) const = 0;

    // General timeouts
    virtual void setOpenHandshakeTimeout(const long& timeout) = 0;
    virtual void setCloseHandshakeTimeout(const long& timeout) = 0;

    // Proxy 

    virtual void setProxyTimeout(const long& timeout) = 0;
    virtual void setProxy(const std::string& proxy) = 0;
    virtual void setProxyBasicAuth(const std::string& username, const std::string& passwd) = 0;
    virtual std::string getProxy() const = 0;

    // Http

    virtual void setMaxHttpBodySize(const size_t& size) = 0;
    virtual void setHttpBody(const std::string& body) = 0;
    virtual void setHttpStatus(const HttpStatusCode& status, const std::string& message) = 0;
    virtual void appendHttpHeader(const std::string& key, const std::string& value) = 0;
     
    virtual void deferHttpResponse() = 0;
    virtual void sendHttpResponse() = 0;

    virtual HttpStatusCode getHttpResponseCode() const = 0;
    virtual std::string getHttpOrigin() const = 0;
    virtual std::string getHttpRequestBody() const = 0;
    virtual std::string getHttpResponseMessage() const = 0;
    virtual std::string getHttpRequestHeader(const std::string& key) const = 0;
    virtual std::string getHttpResponseHeader(const std::string& key) const = 0;

    virtual void removeHttpHeader(const std::string& key) = 0;
    virtual void replaceHttpHeader(const std::string& key, const std::string& value) = 0;

    // Ping/Pong

    virtual void setPongTimeout(const long& timeout) = 0;
    virtual void ping(const std::string& payload) = 0;
    virtual void pong(const std::string& payload) = 0;

    // Misc. 

    virtual void setMaxMessageSize(const size_t& size) = 0;
    virtual void addSubProtocol(const std::string& protocol) = 0;

    virtual size_t getBufferedAmount() const = 0;

    virtual void readFrame() = 0;
    virtual void writeFrame() = 0;
    virtual void send(const std::string& payload, const OpCode& opcode) = 0;
    virtual void close(const CloseStatus& status = CLOSESTATUS_NORMAL, const std::string& reason = "") = 0;

    virtual uint16_t getPort() const = 0;
    virtual int getErrorCode() const = 0;
    virtual std::string getErrorMessage() const = 0;
    virtual std::string getHost() const = 0;
    virtual std::string getRemoteEndpoint() const = 0;
    virtual std::vector<std::string> getRequestedSubProtocols() const = 0;
    virtual std::string getSubProtocol() const = 0;
    virtual std::string getUri() const = 0;

    virtual ConnectionState getState() const = 0;

};

#endif // _IKFWEBSOCKETCONNECTION_H
