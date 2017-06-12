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
#include "sio_client.h"

#define SIO_LISTENER_CLOSE_REASON_NORMAL 0
#define SIO_LISTENER_CLOSE_REASON_DROP 1

typedef struct {
    const char* key;
    const char* value;
} KfSioClientQueryParam;

class KfSioClient {

public:
    typedef std::function<void(const char* name, KfSioMessagePtr message, bool needAck, KfSioMessageList ackMessage)> EventListener;
    typedef std::function<void(KfSioMessagePtr message)> ErrorListener;
    typedef std::function<void(KfSioMessageList)> AckListener;

public:
    KfSioClient();

    // Client calls
    virtual void KF_CALLCONV connect(const char* uri);
    virtual void KF_CALLCONV connect(const char* uri, const KfSioClientQueryParam* query, const unsigned int& queryCount);
    virtual void KF_CALLCONV connect(
        const char* uri,
        const KfSioClientQueryParam* query,
        const unsigned int& queryCount,
        const KfSioClientQueryParam* http_extra_headers,
        const unsigned int& extraHeaderCount);
    virtual void KF_CALLCONV close();
    virtual void KF_CALLCONV syncClose();

    virtual bool KF_CALLCONV isOpen() const;
    virtual const char* KF_CALLCONV getSessionId() const;

    virtual void KF_CALLCONV setClientOpenListener(const sio::client::con_listener& listener);
    virtual void KF_CALLCONV setClientCloseListener(const sio::client::close_listener& listener);
    virtual void KF_CALLCONV setClientFailListener(const sio::client::con_listener& listener);
    virtual void KF_CALLCONV setClientReconnectingListener(const sio::client::con_listener& listener);
    virtual void KF_CALLCONV setClientReconnectListener(const sio::client::reconnect_listener& listener);
    virtual void KF_CALLCONV setSocketOpenListener(const sio::client::socket_listener& listener);
    virtual void KF_CALLCONV setSocketCloseListener(const sio::client::socket_listener& listener);
    virtual void KF_CALLCONV clearListeners();

    virtual void KF_CALLCONV setReconnectAttempts(int attempts);
    virtual void KF_CALLCONV setReconnectDelay(unsigned int millis);
    virtual void KF_CALLCONV setReconnectDelayMax(unsigned int millis);

    // Socket calls
    virtual void KF_CALLCONV on(const char* eventName, EventListener eventListener, const char* socketNs = "");
    virtual void KF_CALLCONV off(const char* eventName, const char* socketNs = "");
    virtual void KF_CALLCONV offAll(const char* socketNs = "");
    virtual void KF_CALLCONV closeSocket(const char* socketNs = "");
    virtual void KF_CALLCONV onError(ErrorListener listener, const char* socketNs = "");
    virtual void KF_CALLCONV offError(const char* socketNs = "");

    virtual void KF_CALLCONV emit(
        const char* name,
        sio::message::list sioMsgList = nullptr,
        const AckListener& ack = nullptr,
        const char* socketNs = "");

    virtual void KF_CALLCONV emit(
        const char* name,
        const char* message,
        const AckListener& ack = nullptr,
        const char* socketNs = "");

    virtual void KF_CALLCONV emitJson(
        const char* name,
        const char* message,
        const AckListener& ack = nullptr,
        const char* socketNs = "");

private:
    sio::object_message::ptr KF_CALLCONV createSioObjectMessage(const char* json);

private:
    std::recursive_mutex m_mutex;
    sio::client m_client;

};

#endif // _KFSIOCLIENT_H
