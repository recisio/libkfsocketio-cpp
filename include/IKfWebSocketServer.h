#ifndef _IKFWEBSOCKETSERVER_H
#define _IKFWEBSOCKETSERVER_H

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

#include <functional>
#include <string>

#include "IKfWebSocketConnection.h"
#include "IKfWebSocketMessage.h"

class IKfWebSocketServer {

public:
    typedef std::function<void(KfWebSocketConnectionPtr)> ConnectionListener;
    typedef std::function<bool(KfWebSocketConnectionPtr)> ValidateListener;
    typedef std::function<void(KfWebSocketConnectionPtr, KfWebSocketMessagePtr)> MessageListener;
    typedef std::function<bool(KfWebSocketConnectionPtr, std::string)> PingListener;
    typedef std::function<void(KfWebSocketConnectionPtr, std::string)> PongListener;

public:
    virtual void enableWebSocketOutputLog() = 0;
    virtual void disableWebSocketOutputLog() = 0;

    /// Blocking mode
    virtual void run(const uint16_t& port) = 0;

    /// Non-blocking mode
    virtual void start(const uint16_t& port) = 0;
    virtual size_t poll() = 0;
    virtual size_t pollOne() = 0;

    /// Stop either one of blocking or non-blocking connections
    virtual void stop() = 0;

    virtual bool isListening() const = 0;
    virtual bool isStopped() const = 0;
    virtual bool isSecure() const = 0;

    /// Calbacks setup

    virtual void unbindListeners() = 0;
    virtual void setOpenListener(ConnectionListener listener) = 0;
    virtual void setCloseListener(ConnectionListener listener) = 0;
    virtual void setFailListener(ConnectionListener listener) = 0;
    virtual void setHttpListener(ConnectionListener listener) = 0;
    virtual void setInterruptListener(ConnectionListener listener) = 0;
    virtual void setSocketInitListener(ConnectionListener listener) = 0;
    virtual void setTcpInitListener(ConnectionListener listener) = 0;
    virtual void setTcpPostInitListener(ConnectionListener listener) = 0;
    virtual void setTcpPreInitListener(ConnectionListener listener) = 0;
    virtual void setValidateListener(ValidateListener listener) = 0;
    virtual void setMessageListener(MessageListener listener) = 0;
    virtual void setPingListener(PingListener listener) = 0;
    virtual void setPongListener(PongListener listener) = 0;
    virtual void setPongTimeoutListener(PongListener listener) = 0;

};

#endif // _IKFWEBSOCKETSERVER_H
