#ifndef _IKFSIOCLIENT_H
#define _IKFSIOCLIENT_H

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

#include "IKfSioMessage.h"

class IKfSioClient {

public:
    typedef std::function<void(void)> ConnectionListener;
    typedef std::function<void(unsigned int const& reason)> CloseListener;
    typedef std::function<void(unsigned int nAttempts, unsigned int delay)> ReconnectListener;
    typedef std::function<void(std::string const& nsp)> SocketListener;
    typedef std::function<void(const std::string& name, const KfSioMessagePtr& message, bool needAck, KfSioMessageList& ackMessage)> EventListener;
    typedef std::function<void(const KfSioMessagePtr& message)> ErrorListener;
    typedef std::function<void(const KfSioMessageList&)> AckListener;

public:

    // Client calls
    virtual void connect(const std::string& uri) = 0;
    virtual void connect(const std::string& uri, const std::map<std::string, std::string>& query) = 0;
    virtual void connect(const std::string& uri, const std::map<std::string, std::string>& query, const std::map<std::string, std::string>& http_extra_headers) = 0;
    virtual void close() = 0;
    virtual void syncClose() = 0;

    virtual bool isOpen() const = 0;
    virtual std::string const& getSessionId() const = 0;

    virtual void setClientOpenListener(const ConnectionListener& listener) = 0;
    virtual void setClientCloseListener(const CloseListener& listener) = 0;
    virtual void setClientFailListener(const ConnectionListener& listener) = 0;
    virtual void setClientReconnectingListener(const ConnectionListener& listener) = 0;
    virtual void setClientReconnectListener(const ReconnectListener& listener) = 0;
    virtual void setSocketOpenListener(const SocketListener& listener) = 0;
    virtual void setSocketCloseListener(const SocketListener& listener) = 0;
    virtual void clearListeners() = 0;

    virtual void setReconnectAttempts(int attempts) = 0;
    virtual void setReconnectDelay(unsigned int millis) = 0;
    virtual void setReconnectDelayMax(unsigned int millis) = 0;

    // Socket calls
    virtual void on(std::string const& eventName, EventListener eventListener, const std::string& socketNs = "") = 0;
    virtual void off(std::string const& eventName, const std::string& socketNs = "") = 0;
    virtual void offAll(const std::string& socketNs = "") = 0;
    virtual void close(const std::string& socketNs = "") = 0;
    virtual void onError(ErrorListener listener, const std::string& socketNs = "") = 0;
    virtual void offError(const std::string& socketNs = "") = 0;

    virtual void emit(
        const std::string& name,
        const KfSioMessageList& msglist = KfSioMessageList(),
        const AckListener& ack = nullptr,
        const std::string& socketNs = "") = 0;

    virtual void emit(
        const std::string& name,
        const std::string& message,
        const AckListener& ack = nullptr,
        const std::string& socketNs = "") = 0;

};

#endif // _IKFSIOCLIENT_H
