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

#include "IKfWebSocketConnection.h"

class IKfWebSocketMessage;

typedef IKfWebSocketMessage* KfWebSocketMessagePtr;

class IKfWebSocketMessage {

public:
    virtual void KF_CALLCONV setCompressed(const bool& isCompressed) = 0;
    virtual void KF_CALLCONV setFin(const bool& isFin) = 0;
    virtual void KF_CALLCONV setHeader(const char* header) = 0;
    virtual void KF_CALLCONV setOpcode(const IKfWebSocketConnection::OpCode& opcode) = 0;
    virtual void KF_CALLCONV setPayload(const char* payload) = 0;
    virtual void KF_CALLCONV appendPayload(const char* payload) = 0;

    virtual bool KF_CALLCONV isCompressed() const = 0;
    virtual bool KF_CALLCONV isFin() const = 0;
    virtual bool KF_CALLCONV isPrepared() const = 0;
    virtual const char* KF_CALLCONV getExtensionData() const = 0;
    virtual const char* KF_CALLCONV getHeader() const = 0;
    virtual const char* KF_CALLCONV getPayload() const = 0;
    virtual const char* KF_CALLCONV getRawPayload() const = 0;
    virtual IKfWebSocketConnection::OpCode KF_CALLCONV getOpcode() const = 0;

};

#endif // !_IKFWEBSOCKETMESSAGE_H
