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
#include "IKfSioClient.h"

#define SIO_LISTENER_CLOSE_REASON_NORMAL 0
#define SIO_LISTENER_CLOSE_REASON_DROP 1

namespace sio {
class client;
}

class KfSioListener;

class KfSioClient : public IKfSioClient {

public:
    KfSioClient();
    virtual ~KfSioClient();

    // Client calls
    virtual void connect(const std::string& uri);
    virtual void connect(const std::string& uri, const std::map<std::string, std::string>& query);
    virtual void connect(const std::string& uri, const std::map<std::string, std::string>& query, const std::map<std::string, std::string>& http_extra_headers);
    virtual void close();
    virtual void syncClose();

    virtual bool isOpen() const;
    virtual std::string const& getSessionId() const;

    virtual void setClientOpenListener(const ConnectionListener& listener);
    virtual void setClientCloseListener(const CloseListener& listener);
    virtual void setClientFailListener(const ConnectionListener& listener);
    virtual void setClientReconnectingListener(const ConnectionListener& listener);
    virtual void setClientReconnectListener(const ReconnectListener& listener);
    virtual void setSocketOpenListener(const SocketListener& listener);
    virtual void setSocketCloseListener(const SocketListener& listener);
    virtual void clearListeners();

    virtual void setReconnectAttempts(int attempts);
    virtual void setReconnectDelay(unsigned int millis);
    virtual void setReconnectDelayMax(unsigned int millis);

    // Socket calls
    virtual void on(std::string const& eventName, EventListener eventListener, const std::string& socketNs = "");
    virtual void off(std::string const& eventName, const std::string& socketNs = "");
    virtual void offAll(const std::string& socketNs = "");
    virtual void close(const std::string& socketNs = "");
    virtual void onError(ErrorListener listener, const std::string& socketNs = "");
    virtual void offError(const std::string& socketNs = "");

    virtual void emit(
        const std::string& name,
        const KfSioMessageList& msglist = KfSioMessageList(),
        const AckListener& ack = nullptr,
        const std::string& socketNs = "");

    virtual void emit(
        const std::string& name,
        const std::string& message,
        const AckListener& ack = nullptr,
        const std::string& socketNs = "");


private:
    std::mutex m_mutex;
    sio::client* m_client;
    KfSioListener* m_listener;

};

#endif // _KFSIOCLIENT_H
