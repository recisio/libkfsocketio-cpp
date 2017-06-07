#include "KfSioClient.h"

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

#include "KfSioListener.h"

#define _KFSIO_CLIENT_LOCK m_mutex.lock()
#define _KFSIO_CLIENT_UNLOCK m_mutex.unlock()

KfSioClient::KfSioClient() :
    m_mutex(),
    m_client(),
    m_listener(new KfSioListener(&m_client))
{
}

KfSioClient::~KfSioClient()
{
    delete m_listener;
}

void KF_CALLCONV KfSioClient::setClientOpenListener(const ConnectionListener& listener)
{
    m_listener->setClientOpenListener(listener);
}

void KF_CALLCONV KfSioClient::setClientCloseListener(const CloseListener& listener)
{
    m_listener->setClientCloseListener(listener);
}

void KF_CALLCONV KfSioClient::setClientFailListener(const ConnectionListener& listener)
{
    m_listener->setClientFailListener(listener);
}

void KF_CALLCONV KfSioClient::setClientReconnectingListener(const ConnectionListener& listener)
{
    m_listener->setClientReconnectingListener(listener);
}

void KF_CALLCONV KfSioClient::setClientReconnectListener(const ReconnectListener& listener)
{
    m_listener->setClientReconnectListener(listener);
}

void KF_CALLCONV KfSioClient::setSocketOpenListener(const SocketListener& listener)
{
    m_listener->setSocketOpenListener(listener);
}

void KF_CALLCONV KfSioClient::setSocketCloseListener(const SocketListener& listener)
{
    m_listener->setSocketCloseListener(listener);
}

void KF_CALLCONV KfSioClient::clearListeners()
{
    m_listener->clearListeners();
}

void KF_CALLCONV KfSioClient::connect(const char* uri)
{
    m_client.connect(uri);
}

void KF_CALLCONV KfSioClient::connect(const char* uri, const KfSioClientQueryParam* query, const unsigned int& queryCount)
{
    std::map<std::string, std::string> stlQuery;
    for (int i = 0; i < queryCount; ++i) {
        stlQuery[query[i].key] = query[i].value;
    }

    m_client.connect(uri, stlQuery);
}

void KF_CALLCONV KfSioClient::connect(
    const char* uri,
    const KfSioClientQueryParam* query,
    const unsigned int& queryCount,
    const KfSioClientQueryParam* http_extra_headers,
    const unsigned int& extraHeaderCount)
{
    std::map<std::string, std::string> stlQuery;
    for (int i = 0; i < queryCount; ++i) {
        stlQuery[query[i].key] = query[i].value;
    }

    std::map<std::string, std::string> stlExtraHeaders;
    for (int i = 0; i < extraHeaderCount; ++i) {
        stlExtraHeaders[http_extra_headers[i].key] = http_extra_headers[i].value;
    }

    m_client.connect(uri, stlQuery, stlExtraHeaders);
}

void KF_CALLCONV KfSioClient::close()
{
    m_client.close();
}

void KF_CALLCONV KfSioClient::syncClose()
{
    m_client.sync_close();
}

void KF_CALLCONV KfSioClient::setReconnectAttempts(int attempts)
{
    m_client.set_reconnect_attempts(attempts);
}

void KF_CALLCONV KfSioClient::setReconnectDelay(unsigned int millis)
{
    m_client.set_reconnect_delay(millis);
}

void KF_CALLCONV KfSioClient::setReconnectDelayMax(unsigned int millis)
{
    m_client.set_reconnect_delay_max(millis);
}

bool KF_CALLCONV KfSioClient::isOpen() const
{
    return m_client.opened();
}

const char* KF_CALLCONV KfSioClient::getSessionId() const
{
    return m_client.get_sessionid().c_str();
}

void KF_CALLCONV KfSioClient::on(const char* eventName, EventListener eventListener, const char* socketNs)
{
    sio::socket::event_listener_aux fnc = [eventListener](const std::string& name, sio::message::ptr const& message, bool needAck, sio::message::list& ackMessage) {
        int msgSize = (int) ackMessage.size();

        KfSioMessageList ackList = nullptr;
        if (msgSize > 0) {
            KfSioMessageListItem* previous = nullptr;
            KfSioMessageListItem* current = nullptr;
            for (int i = 0; i < msgSize; ++i) {

                current = new KfSioMessageListItem();
                if (i == 0) {
                    ackList = current;
                }

                current->item = new KfSioMessage(ackMessage.at(i).get());

                if (nullptr != previous) {
                    previous->next = current;
                }

                previous = current;
            }
        }

        KfSioMessagePtr kfmessage = new KfSioMessage(message.get());
        eventListener(name.c_str(), kfmessage, needAck, ackList);

        while (nullptr != ackList) {
            KfSioMessageListItem* listItem = ackList;
            ackList = ackList->next;

            KfSioMessage* item = dynamic_cast<KfSioMessage*>(listItem->item);
            if (nullptr != item) {
                ackMessage.push(item->m_message);
            }

            delete item;
            delete listItem;
        }

        delete kfmessage;
    };

    _KFSIO_CLIENT_LOCK;
    m_client.socket(socketNs)->on(eventName, fnc);
    _KFSIO_CLIENT_UNLOCK;
}

void KF_CALLCONV KfSioClient::off(const char* eventName, const char* socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client.socket(socketNs)->off(eventName);
    _KFSIO_CLIENT_UNLOCK;
}

void KF_CALLCONV KfSioClient::offAll(const char* socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client.socket(socketNs)->off_all();
    _KFSIO_CLIENT_UNLOCK;
}

void KF_CALLCONV KfSioClient::closeSocket(const char* socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client.socket(socketNs)->close();
    _KFSIO_CLIENT_UNLOCK;
}

void KF_CALLCONV KfSioClient::onError(ErrorListener listener, const char* socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client.socket(socketNs)->on_error([listener](const std::shared_ptr<sio::message>& message) {
        KfSioMessagePtr kfmsg = new KfSioMessage(message.get());
        listener(kfmsg);
        delete kfmsg;
    });
    _KFSIO_CLIENT_UNLOCK;
}

void KF_CALLCONV KfSioClient::offError(const char* socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client.socket(socketNs)->off_error();
    _KFSIO_CLIENT_UNLOCK;
}

void KF_CALLCONV KfSioClient::emit(const char* name, const char* message, const AckListener& ack, const char* socketNs)
{
    KfSioMessageList msgList = new KfSioMessageListItem();
    msgList->item = new KfSioMessage(message);
    emit(name, msgList, ack, socketNs);

    delete msgList->item;
    delete msgList;
}

void KF_CALLCONV KfSioClient::emit(const char* name, KfSioMessageList msglist, const AckListener& ack, const char* socketNs)
{
    sio::message::list sioMsgList = nullptr;
    if (nullptr != msglist) {
        while (nullptr != msglist) {
            KfSioMessageListItem* item = msglist;
            msglist = item->next;

            KfSioMessage* cMsg = dynamic_cast<KfSioMessage*>(item->item);
            if (nullptr == cMsg) {
                continue;
            }

            sioMsgList.push(cMsg->m_message);
        }
    }

    std::function<void(sio::message::list const&)> ackFun = nullptr;
    if (nullptr != ack) {
        ackFun = [ack](sio::message::list const& ackMsgList) {

            KfSioMessageList ackList = nullptr;
            int msgSize = (int) ackMsgList.size();

            if (msgSize > 0) {
                ackList = new KfSioMessageListItem();
                KfSioMessageListItem* previous = nullptr;
                KfSioMessageListItem* current = ackList;

                for (int i = 0; i < msgSize; ++i) {
                    current->item = new KfSioMessage(ackMsgList.at(i).get());
                    if (nullptr != previous) {
                        previous->next = current;
                    }
                    previous = current;
                }
            }

            ack(ackList);

            while (nullptr != ackList) {
                KfSioMessageListItem* current = ackList;
                ackList = current->next;

                delete current->item;
                delete current;
            }
        };
    }

    _KFSIO_CLIENT_LOCK;
    m_client.socket(socketNs)->emit(
        name,
        sioMsgList,
        ackFun
    );
    _KFSIO_CLIENT_UNLOCK;
}
