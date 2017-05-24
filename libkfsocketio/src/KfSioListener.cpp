#include "KfSioListener.h"

#ifdef KFSIO_THREAD_SAFE
#define _KFSIO_LISTENER_LOCK m_mutex.lock()
#define _KFSIO_LISTENER_UNLOCK m_mutex.unlock()
#else 
#define _KFSIO_LISTENER_LOCK
#define _KFSIO_LISTENER_UNLOCK
#endif // KFSIO_THREAD_SAFE

KfSioListener::KfSioListener(sio::client* client) :
#ifdef KFSIO_THREAD_SAFE
    m_mutex(),
#endif // KFSIO_THREAD_SAFE
    m_client(client),
    m_clientOpenListener(nullptr),
    m_clientFailListener(nullptr),
    m_clientReconnectingListener(nullptr),
    m_clientCloseListener(nullptr),
    m_clientReconnectListener(nullptr),
    m_socketOpenListener(nullptr),
    m_socketCloseListener(nullptr)
{
    bindClient();
}

KfSioListener::~KfSioListener()
{
    unbindClient();
}

void KfSioListener::bindClient()
{
    m_client->set_close_listener(std::bind(&KfSioListener::onClientClose, this, std::placeholders::_1));
    m_client->set_fail_listener(std::bind(&KfSioListener::onClientFail, this));
    m_client->set_open_listener(std::bind(&KfSioListener::onClientOpen, this));
    m_client->set_reconnecting_listener(std::bind(&KfSioListener::onClientReconnecting, this));
    m_client->set_reconnect_listener(std::bind(&KfSioListener::onClientReconnect, this, std::placeholders::_1, std::placeholders::_2));
    m_client->set_socket_close_listener(std::bind(&KfSioListener::onSocketClose, this, std::placeholders::_1));
    m_client->set_socket_open_listener(std::bind(&KfSioListener::onSocketOpen, this, std::placeholders::_1));
}

void KfSioListener::unbindClient()
{
    m_client->clear_con_listeners();
    m_client->clear_socket_listeners();
}

void KfSioListener::clearListeners()
{
    _KFSIO_LISTENER_LOCK;
    m_clientOpenListener = nullptr;
    m_clientFailListener = nullptr;
    m_clientReconnectingListener = nullptr;
    m_clientCloseListener = nullptr;
    m_clientReconnectListener = nullptr;
    m_socketOpenListener = nullptr;
    m_socketCloseListener = nullptr;
    _KFSIO_LISTENER_UNLOCK;
}


void KfSioListener::setClientOpenListener(const ConnectionListener& listener)
{
    _KFSIO_LISTENER_LOCK;
    m_clientOpenListener = listener;
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::setClientCloseListener(const CloseListener& listener)
{
    _KFSIO_LISTENER_LOCK;
    m_clientCloseListener = listener;
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::setClientFailListener(const ConnectionListener& listener)
{
    _KFSIO_LISTENER_LOCK;
    m_clientFailListener = listener;
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::setClientReconnectingListener(const ConnectionListener& listener)
{
    _KFSIO_LISTENER_LOCK;
    m_clientReconnectingListener = listener;
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::setClientReconnectListener(const ReconnectListener& listener)
{
    _KFSIO_LISTENER_LOCK;
    m_clientReconnectListener = listener;
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::setSocketOpenListener(const SocketListener& listener)
{
    _KFSIO_LISTENER_LOCK;
    m_socketOpenListener = listener;
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::setSocketCloseListener(const SocketListener& listener)
{
    _KFSIO_LISTENER_LOCK;
    m_socketCloseListener = listener;
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::onClientClose(sio::client::close_reason const& reason)
{
    _KFSIO_LISTENER_LOCK;
    if (nullptr != m_clientCloseListener) {
        CloseReason reason = CLOSE_REASON_NORMAL;
        if (reason != sio::client::close_reason_normal) {
            reason = CLOSE_REASON_DROP;
        }
        m_clientCloseListener((unsigned int) reason);
    }
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::onClientFail()
{
    _KFSIO_LISTENER_LOCK;
    if (nullptr != m_clientFailListener) {
        m_clientFailListener();
    }
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::onClientOpen()
{
    _KFSIO_LISTENER_LOCK;
    if (nullptr != m_clientOpenListener) {
        m_clientOpenListener();
    }
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::onClientReconnecting()
{
    _KFSIO_LISTENER_LOCK;
    if (nullptr != m_clientReconnectingListener) {
        m_clientReconnectingListener();
    }
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::onClientReconnect(unsigned int nAttempt, unsigned int delay)
{
    _KFSIO_LISTENER_LOCK;
    if (nullptr != m_clientReconnectListener) {
        m_clientReconnectListener(nAttempt, delay);
    }
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::onSocketClose(std::string const& nsp)
{
    _KFSIO_LISTENER_LOCK;
    if (nullptr != m_socketCloseListener) {
        m_socketCloseListener(nsp);
    }
    _KFSIO_LISTENER_UNLOCK;
}

void KfSioListener::onSocketOpen(std::string const& nsp)
{
    _KFSIO_LISTENER_LOCK;
    if (nullptr != m_socketOpenListener) {
        m_socketOpenListener(nsp);
    }
    _KFSIO_LISTENER_UNLOCK;
}