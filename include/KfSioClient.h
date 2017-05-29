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
#include <mutex>

#include "KfSioMessage.h"

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

class LIBKFSOCKETIO_SIOCLIENT_DLL KfSioClient {

public:
    typedef std::function<void(void)> ConnectionListener;
    typedef std::function<void(unsigned int const& reason)> CloseListener;
    typedef std::function<void(unsigned int nAttempts, unsigned int delay)> ReconnectListener;
    typedef std::function<void(std::string const& nsp)> SocketListener;
    typedef std::function<void(const std::string& name, const KfSioMessage& message, bool needAck, KfSioMessageList& ackMessage)> EventListener;
    typedef std::function<void(const KfSioMessage& message)> ErrorListener;
    typedef std::function<void(const KfSioMessageList&)> AckListener;

public:
    KfSioClient();
    ~KfSioClient();

    // Client calls
    void connect(const std::string& uri);
    void connect(const std::string& uri, const std::map<std::string, std::string>& query);
    void connect(const std::string& uri, const std::map<std::string, std::string>& query, const std::map<std::string, std::string>& http_extra_headers);
    void close();
    void syncClose();

    bool isOpen() const;
    std::string const& getSessionId() const;

    void setClientOpenListener(const ConnectionListener& listener);
    void setClientCloseListener(const CloseListener& listener);
    void setClientFailListener(const ConnectionListener& listener);
    void setClientReconnectingListener(const ConnectionListener& listener);
    void setClientReconnectListener(const ReconnectListener& listener);
    void setSocketOpenListener(const SocketListener& listener);
    void setSocketCloseListener(const SocketListener& listener);
    void clearListeners();

    void setReconnectAttempts(int attempts);
    void setReconnectDelay(unsigned int millis);
    void setReconnectDelayMax(unsigned int millis);

    // Socket calls
    void on(std::string const& eventName, EventListener eventListener, const std::string& socketNs = "");
    void off(std::string const& eventName, const std::string& socketNs = "");
    void offAll(const std::string& socketNs = "");
    void close(const std::string& socketNs = "");
    void onError(ErrorListener listener, const std::string& socketNs = "");
    void offError(const std::string& socketNs = "");

    void emit(
        const std::string& name,
        const KfSioMessageList& msglist = KfSioMessageList(),
        const AckListener& ack = nullptr,
        const std::string& socketNs = "");


private:
    std::mutex m_mutex;
    sio::client* m_client;
    KfSioListener* m_listener;

};

#endif // _KFSIOCLIENT_H
