#ifndef _KFSIOCLIENT_H
#define _KFSIOCLIENT_H

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
#include <map>

#include "KfSioSocket.h"

#ifdef LIBKFSOCKETIO_EXPORTS
#define LIBKFSOCKETIO_SIOCLIENT_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_SIOCLIENT_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#define SIO_LISTENER_CLOSE_REASON_NORMAL 0
#define SIO_LISTENER_CLOSE_REASON_DROP 1

namespace sio {
class client;
}

class KfSioListener;

class KfSioClient {
    friend class KfSioSocket;

public:
    typedef std::function<void(void)> ConnectionListener;
    typedef std::function<void(unsigned int const& reason)> CloseListener;
    typedef std::function<void(unsigned int nAttempts, unsigned int delay)> ReconnectListener;
    typedef std::function<void(std::string const& nsp)> SocketListener;

public:
    LIBKFSOCKETIO_SIOCLIENT_DLL KfSioClient();
    LIBKFSOCKETIO_SIOCLIENT_DLL ~KfSioClient();

    // Client calls

    LIBKFSOCKETIO_SIOCLIENT_DLL void connect(const std::string& uri);
    LIBKFSOCKETIO_SIOCLIENT_DLL void connect(const std::string& uri, const std::map<std::string, std::string>& query);
    LIBKFSOCKETIO_SIOCLIENT_DLL void connect(const std::string& uri, const std::map<std::string, std::string>& query, const std::map<std::string, std::string>& http_extra_headers);
    LIBKFSOCKETIO_SIOCLIENT_DLL void close();
    LIBKFSOCKETIO_SIOCLIENT_DLL void syncClose();

    LIBKFSOCKETIO_SIOCLIENT_DLL bool isOpen() const;
    LIBKFSOCKETIO_SIOCLIENT_DLL std::string const& getSessionId() const;

    LIBKFSOCKETIO_SIOCLIENT_DLL void setClientOpenListener(const ConnectionListener& listener);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setClientCloseListener(const CloseListener& listener);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setClientFailListener(const ConnectionListener& listener);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setClientReconnectingListener(const ConnectionListener& listener);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setClientReconnectListener(const ReconnectListener& listener);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setSocketOpenListener(const SocketListener& listener);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setSocketCloseListener(const SocketListener& listener);
    LIBKFSOCKETIO_SIOCLIENT_DLL void clearListeners();

    LIBKFSOCKETIO_SIOCLIENT_DLL void setReconnectAttempts(int attempts);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setReconnectDelay(unsigned int millis);
    LIBKFSOCKETIO_SIOCLIENT_DLL void setReconnectDelayMax(unsigned int millis);


private:
    sio::client* m_client;
    KfSioListener* m_listener;
    KfSioSocket* m_socket;

};

#endif // _KFSIOCLIENT_H
