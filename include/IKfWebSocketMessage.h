#ifndef _IKFWEBSOCKETMESSAGE_H
#define _IKFWEBSOCKETMESSAGE_H

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
#include <memory>

#include "IKfWebSocketConnection.h"

class IKfWebSocketMessage;

typedef std::shared_ptr<IKfWebSocketMessage> KfWebSocketMessagePtr;

class IKfWebSocketMessage {

public:
    virtual void setCompressed(const bool& isCompressed) = 0;
    virtual void setFin(const bool& isFin) = 0;
    virtual void setHeader(const std::string& header) = 0;
    virtual void setOpcode(const IKfWebSocketConnection::OpCode& opcode) = 0;
    virtual void setPayload(const std::string& payload) = 0;
    virtual void appendPayload(const std::string& payload) = 0;

    virtual bool isCompressed() const = 0;
    virtual bool isFin() const = 0;
    virtual bool isPrepared() const = 0;
    virtual std::string getExtensionData() const = 0;
    virtual std::string getHeader() const = 0;
    virtual std::string getPayload() const = 0;
    virtual std::string getRawPayload() const = 0;
    virtual IKfWebSocketConnection::OpCode getOpcode() const = 0;

};

#endif // !_IKFWEBSOCKETMESSAGE_H
