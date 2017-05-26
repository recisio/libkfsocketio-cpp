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

#include <functional>
#include <string>

#include "KfWebSocketConnection.h"

class KfWebSocketServerHandler;

class KfWebSocketServer {

public:
    typedef std::function<void(const KfWebSocketConnection&)> ConnectionListener;
    typedef std::function<bool(const KfWebSocketConnection&)> ValidateListener;
    typedef std::function<void(const KfWebSocketConnection&)> MessageListener; /// @todo MessageWrapper
    typedef std::function<bool(const KfWebSocketConnection&, std::string)> PingListener;
    typedef std::function<void(const KfWebSocketConnection&, std::string)> PongListener;

public:
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL KfWebSocketServer();
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL virtual ~KfWebSocketServer();

    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void unbindListeners();

    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setOpenListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setCloseListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setFailListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setHttpListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setInterruptListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setSocketInitListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setTcpInitListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setTcpPostInitListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setTcpPreInitListener(ConnectionListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setValidateListener(ValidateListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setMessageListener(MessageListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setPingListener(PingListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setPongListener(PongListener listener);
    LIBKFSOCKETIO_WEBSOCKETSERVER_DLL void setPongTimeoutListener(PongListener listener);

private:
    KfWebSocketServerHandler* m_handler;

};

#endif // _KFWEBSOCKETSERVER_H
