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

#ifdef LIBKFSOCKETIO_EXPORTS
#define LIBKFSOCKETIO_WEBSOCKETMESSAGE_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_WEBSOCKETMESSAGE_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#include <string>

#include "KfWebSocketConnection.h"

struct KfWebSocketMessageImplWrapper;

class LIBKFSOCKETIO_WEBSOCKETMESSAGE_DLL KfWebSocketMessage {

public:
    KfWebSocketMessage(const KfWebSocketMessageImplWrapper& message);
    KfWebSocketMessage(const KfWebSocketMessage& copy);
    ~KfWebSocketMessage();

    void setCompressed(const bool& isCompressed);
    void setFin(const bool& isFin);
    void setHeader(const std::string& header);
    void setOpcode(const KfWebSocketConnection::OpCode& opcode);
    void setPayload(const std::string& payload);
    void appendPayload(const std::string& payload);

    bool isCompressed() const;
    bool isFin() const;
    bool isPrepared() const;
    std::string getExtensionData() const;
    std::string getHeader() const;
    std::string getPayload() const;
    std::string getRawPayload() const;
    KfWebSocketConnection::OpCode getOpcode() const;

private:
    KfWebSocketMessageImplWrapper* m_message;

};

#endif // _KFWEBSOCKETMESSAGE_H
