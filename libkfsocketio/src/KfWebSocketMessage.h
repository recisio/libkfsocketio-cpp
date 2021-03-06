#ifndef _KFWEBSOCKETMESSAGE_H
#define _KFWEBSOCKETMESSAGE_H

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

#include "KfWebSocketConnection.h"
#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

class KfWebSocketMessage;

typedef websocketpp::connection<websocketpp::config::asio>::message_ptr WSMessagePtr;
typedef KfWebSocketMessage* KfWebSocketMessagePtr;

class KfWebSocketMessage {

public:
    KfWebSocketMessage(const WSMessagePtr& message);
    KfWebSocketMessage(const KfWebSocketMessage& copy);

    virtual void KF_CALLCONV setCompressed(const bool& isCompressed);
    virtual void KF_CALLCONV setFin(const bool& isFin);
    virtual void KF_CALLCONV setHeader(const char* header);
    virtual void KF_CALLCONV setOpcode(const KfWebSocketConnection::OpCode& opcode);
    virtual void KF_CALLCONV setPayload(const char* payload);
    virtual void KF_CALLCONV appendPayload(const char* payload);

    virtual bool KF_CALLCONV isCompressed() const;
    virtual bool KF_CALLCONV isFin() const;
    virtual bool KF_CALLCONV isPrepared() const;
    virtual std::string KF_CALLCONV getExtensionData() const;
    virtual std::string KF_CALLCONV getHeader() const;
    virtual std::string KF_CALLCONV getPayload() const;
    virtual std::string KF_CALLCONV getRawPayload() const;
    virtual KfWebSocketConnection::OpCode KF_CALLCONV getOpcode() const;

private:
    WSMessagePtr m_message;

};

#endif // _KFWEBSOCKETMESSAGE_H
