#pragma once

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
