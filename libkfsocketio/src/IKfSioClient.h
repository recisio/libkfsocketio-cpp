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

#include "IKfSioMessage.h"

typedef struct {
    const char* key;
    const char* value;
} KfSioClientQueryParam;

class IKfSioClient {

public:

    typedef std::function<void(void)> ConnectionListener;
    typedef std::function<void(unsigned int const& reason)> CloseListener;
    typedef std::function<void(unsigned int nAttempts, unsigned int delay)> ReconnectListener;
    typedef std::function<void(const char* nsp)> SocketListener;
    typedef std::function<void(const char* name, KfSioMessagePtr message, bool needAck, KfSioMessageList ackMessage)> EventListener;
    typedef std::function<void(KfSioMessagePtr message)> ErrorListener;
    typedef std::function<void(KfSioMessageList)> AckListener;

public:
    virtual ~IKfSioClient() {}

    // Client calls
    virtual void KF_CALLCONV connect(const char* uri) = 0;
    virtual void KF_CALLCONV connect(const char* uri, const KfSioClientQueryParam* query, const unsigned int& queryCount) = 0;
    virtual void KF_CALLCONV connect(
        const char* uri, 
        const KfSioClientQueryParam* query, 
        const unsigned int& queryCount, 
        const KfSioClientQueryParam* http_extra_headers, 
        const unsigned int& extraHeaderCount) = 0;
    virtual void KF_CALLCONV close() = 0;
    virtual void KF_CALLCONV syncClose() = 0;

    virtual bool KF_CALLCONV isOpen() const = 0;
    virtual const char* KF_CALLCONV getSessionId() const = 0;

    virtual void KF_CALLCONV setClientOpenListener(const ConnectionListener& listener) = 0;
    virtual void KF_CALLCONV setClientCloseListener(const CloseListener& listener) = 0;
    virtual void KF_CALLCONV setClientFailListener(const ConnectionListener& listener) = 0;
    virtual void KF_CALLCONV setClientReconnectingListener(const ConnectionListener& listener) = 0;
    virtual void KF_CALLCONV setClientReconnectListener(const ReconnectListener& listener) = 0;
    virtual void KF_CALLCONV setSocketOpenListener(const SocketListener& listener) = 0;
    virtual void KF_CALLCONV setSocketCloseListener(const SocketListener& listener) = 0;
    virtual void KF_CALLCONV clearListeners() = 0;

    virtual void KF_CALLCONV setReconnectAttempts(int attempts) = 0;
    virtual void KF_CALLCONV setReconnectDelay(unsigned int millis) = 0;
    virtual void KF_CALLCONV setReconnectDelayMax(unsigned int millis) = 0;

    // Socket calls
    virtual void KF_CALLCONV on(const char* eventName, EventListener eventListener, const char* socketNs = "") = 0;
    virtual void KF_CALLCONV off(const char* eventName, const char* socketNs = "") = 0;
    virtual void KF_CALLCONV offAll(const char* socketNs = "") = 0;
    virtual void KF_CALLCONV close(const char* socketNs = "") = 0;
    virtual void KF_CALLCONV onError(ErrorListener listener, const char* socketNs = "") = 0;
    virtual void KF_CALLCONV offError(const char* socketNs = "") = 0;

    virtual void KF_CALLCONV emit(
        const char* name,
        KfSioMessageList msglist = nullptr,
        const AckListener& ack = nullptr,
        const char* socketNs = "") = 0;

    virtual void KF_CALLCONV emit(
        const char* name,
        const char* message,
        const AckListener& ack = nullptr,
        const char* socketNs = "") = 0;

};

#endif // _IKFSIOCLIENT_H
