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

#include "IKfWebSocketMessage.h"

#include "websocketpp/connection.hpp"
#include "websocketpp/config/asio.hpp"

typedef websocketpp::connection<websocketpp::config::asio>::message_ptr WSMessagePtr;

class KfWebSocketMessage : public IKfWebSocketMessage {

public:
    KfWebSocketMessage(const WSMessagePtr& message);
    KfWebSocketMessage(const KfWebSocketMessage& copy);

    virtual void setCompressed(const bool& isCompressed);
    virtual void setFin(const bool& isFin);
    virtual void setHeader(const std::string& header);
    virtual void setOpcode(const IKfWebSocketConnection::OpCode& opcode);
    virtual void setPayload(const std::string& payload);
    virtual void appendPayload(const std::string& payload);

    virtual bool isCompressed() const;
    virtual bool isFin() const;
    virtual bool isPrepared() const;
    virtual std::string getExtensionData() const;
    virtual std::string getHeader() const;
    virtual std::string getPayload() const;
    virtual std::string getRawPayload() const;
    virtual IKfWebSocketConnection::OpCode getOpcode() const;

private:
    WSMessagePtr m_message;

};

#endif // _KFWEBSOCKETMESSAGE_H
