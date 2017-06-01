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

#ifdef KFSIO_USE_STDFUNCB
#include <functional>
#endif // KFSIO_USE_STDFUN

#include <cstdint>

#include "IKfWebSocketConnection.h"
#include "IKfWebSocketMessage.h"

class IKfWebSocketServer {

public:
#ifdef KFSIO_USE_STDFUNCB
    typedef std::function<void(KfWebSocketConnectionPtr)> ConnectionListener;
    typedef std::function<bool(KfWebSocketConnectionPtr)> ValidateListener;
    typedef std::function<void(KfWebSocketConnectionPtr, KfWebSocketMessagePtr)> MessageListener;
    typedef std::function<bool(KfWebSocketConnectionPtr, const char*)> PingListener;
    typedef std::function<void(KfWebSocketConnectionPtr, const char*)> PongListener;
#else
    typedef void (KF_CALLCONV *ConnectionListener)(KfWebSocketConnectionPtr);
    typedef bool (KF_CALLCONV *ValidateListener)(KfWebSocketConnectionPtr);
    typedef void (KF_CALLCONV *MessageListener)(KfWebSocketConnectionPtr, KfWebSocketMessagePtr);
    typedef bool (KF_CALLCONV *PingListener)(KfWebSocketConnectionPtr, const char*);
    typedef void (KF_CALLCONV *PongListener)(KfWebSocketConnectionPtr, const char*);
#endif // KFSIO_USE_STDFUN

public:
    virtual ~IKfWebSocketServer() {}
    virtual void KF_CALLCONV enableWebSocketOutputLog() = 0;
    virtual void KF_CALLCONV disableWebSocketOutputLog() = 0;

    /// Blocking mode
    virtual void KF_CALLCONV run(const uint16_t& port) = 0;

    /// Non-blocking mode
    virtual void KF_CALLCONV start(const uint16_t& port) = 0;
    virtual size_t KF_CALLCONV poll() = 0;
    virtual size_t KF_CALLCONV pollOne() = 0;

    /// Stop either one of blocking or non-blocking connections
    virtual void KF_CALLCONV stop() = 0;

    virtual bool KF_CALLCONV isListening() const = 0;
    virtual bool KF_CALLCONV isStopped() const = 0;
    virtual bool KF_CALLCONV isSecure() const = 0;

    /// Calbacks setup

    virtual void KF_CALLCONV unbindListeners() = 0;
    virtual void KF_CALLCONV setOpenListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setCloseListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setFailListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setHttpListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setInterruptListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setSocketInitListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setTcpInitListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setTcpPostInitListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setTcpPreInitListener(ConnectionListener listener) = 0;
    virtual void KF_CALLCONV setValidateListener(ValidateListener listener) = 0;
    virtual void KF_CALLCONV setMessageListener(MessageListener listener) = 0;
    virtual void KF_CALLCONV setPingListener(PingListener listener) = 0;
    virtual void KF_CALLCONV setPongListener(PongListener listener) = 0;
    virtual void KF_CALLCONV setPongTimeoutListener(PongListener listener) = 0;

};

#endif // _IKFWEBSOCKETSERVER_H
