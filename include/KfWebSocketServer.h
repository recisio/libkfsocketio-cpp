#ifndef _KFWEBSOCKETSERVER_H
#define _KFWEBSOCKETSERVER_H

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
#define LIBKFSOCKETIO_WEBSOCKETSERVER_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_WEBSOCKETSERVER_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

// Disable nothrow spec warning if needed
#ifdef NO_VS4290_WARNING
#pragma warning(disable : 4290)  
#endif

#include <functional>
#include <string>

#include "KfWebSocketConnection.h"

class KfWebSocketServerHandler;

class LIBKFSOCKETIO_WEBSOCKETSERVER_DLL KfWebSocketServer {

public:
    typedef std::function<void(const KfWebSocketConnection&)> ConnectionListener;
    typedef std::function<bool(const KfWebSocketConnection&)> ValidateListener;
    typedef std::function<void(const KfWebSocketConnection&)> MessageListener; /// @todo MessageWrapper
    typedef std::function<bool(const KfWebSocketConnection&, std::string)> PingListener;
    typedef std::function<void(const KfWebSocketConnection&, std::string)> PongListener;

public:
    KfWebSocketServer();
    virtual ~KfWebSocketServer();

    /// Blocking mode
    void run(const uint16_t& port) throw(std::exception);

    /// Non-blocking mode
    void start(const uint16_t& port) throw(std::exception);
    size_t poll();
    size_t pollOne();

    /// Stop either one of blocking or non-blocking connections
    void stop();

    bool isListening() const;
    bool isStopped() const;
    bool isSecure() const;

    /// Calbacks setup

    void unbindListeners();
    void setOpenListener(ConnectionListener listener);
    void setCloseListener(ConnectionListener listener);
    void setFailListener(ConnectionListener listener);
    void setHttpListener(ConnectionListener listener);
    void setInterruptListener(ConnectionListener listener);
    void setSocketInitListener(ConnectionListener listener);
    void setTcpInitListener(ConnectionListener listener);
    void setTcpPostInitListener(ConnectionListener listener);
    void setTcpPreInitListener(ConnectionListener listener);
    void setValidateListener(ValidateListener listener);
    void setMessageListener(MessageListener listener);
    void setPingListener(PingListener listener);
    void setPongListener(PongListener listener);
    void setPongTimeoutListener(PongListener listener);

private:
    KfWebSocketServerHandler* m_handler;

};

#endif // _KFWEBSOCKETSERVER_H
