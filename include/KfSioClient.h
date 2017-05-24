#ifndef _KFSIOCLIENT_H
#define _KFSIOCLIENT_H

#include <functional>
#include <string>
#include <map>

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

    LIBKFSOCKETIO_SIOCLIENT_DLL bool isOpened() const;
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

    // Socket calls

private:
    sio::client* m_client;
    KfSioListener* m_listener;

};

#endif // _KFSIOCLIENT_H
