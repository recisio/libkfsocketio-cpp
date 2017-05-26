#pragma once

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

#include "sio_client.h"
#include <functional>

#ifdef KFSIO_THREAD_SAFE
#include <mutex>
#endif // KFSIO_THREAD_SAFE

class KfSioListener {

public:
    enum CloseReason {
        CLOSE_REASON_NORMAL = 0,
        CLOSE_REASON_DROP = 1
    };

    typedef std::function<void(void)> ConnectionListener;
    typedef std::function<void(unsigned int const& reason)> CloseListener;
    typedef std::function<void(unsigned int, unsigned int)> ReconnectListener;
    typedef std::function<void(std::string const& nsp)> SocketListener;

public:
    KfSioListener(sio::client* client);
    virtual ~KfSioListener();

    void clearListeners();

    void setClientOpenListener(const ConnectionListener& listener);
    void setClientCloseListener(const CloseListener& listener);
    void setClientFailListener(const ConnectionListener& listener);
    void setClientReconnectingListener(const ConnectionListener& listener);
    void setClientReconnectListener(const ReconnectListener& listener);
    void setSocketOpenListener(const SocketListener& listener);
    void setSocketCloseListener(const SocketListener& listener);

private:
    void bindClient();
    void unbindClient();

    void onClientClose(sio::client::close_reason const& reason);
    void onClientFail();
    void onClientOpen();
    void onClientReconnecting();
    void onClientReconnect(unsigned int nAttempt, unsigned int delay);
    void onSocketClose(std::string const& nsp);
    void onSocketOpen(std::string const& nsp);

private:
#ifdef KFSIO_THREAD_SAFE
    std::mutex m_mutex;
#endif // KFSIO_THREAD_SAFE
    sio::client* m_client;

    ConnectionListener m_clientOpenListener;
    ConnectionListener m_clientFailListener;
    ConnectionListener m_clientReconnectingListener;
    CloseListener m_clientCloseListener;
    ReconnectListener m_clientReconnectListener;
    SocketListener m_socketOpenListener;
    SocketListener m_socketCloseListener;

};
