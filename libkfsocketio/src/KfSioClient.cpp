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
#include "sio_client.h"

#define _KFSIO_CLIENT_LOCK m_mutex.lock()
#define _KFSIO_CLIENT_UNLOCK m_mutex.unlock()

KfSioClient::KfSioClient() :
    m_mutex(),
    m_client(new sio::client()),
    m_listener(nullptr)
{
    m_listener = new KfSioListener(m_client);
}

KfSioClient::~KfSioClient()
{
    delete m_listener;
    delete m_client;
}

void KfSioClient::setClientOpenListener(const ConnectionListener& listener)
{
    m_listener->setClientOpenListener(listener);
}

void KfSioClient::setClientCloseListener(const CloseListener& listener)
{
    m_listener->setClientCloseListener(listener);
}

void KfSioClient::setClientFailListener(const ConnectionListener& listener)
{
    m_listener->setClientFailListener(listener);
}

void KfSioClient::setClientReconnectingListener(const ConnectionListener& listener)
{
    m_listener->setClientReconnectingListener(listener);
}

void KfSioClient::setClientReconnectListener(const ReconnectListener& listener)
{
    m_listener->setClientReconnectListener(listener);
}

void KfSioClient::setSocketOpenListener(const SocketListener& listener)
{
    m_listener->setSocketOpenListener(listener);
}

void KfSioClient::setSocketCloseListener(const SocketListener& listener)
{
    m_listener->setSocketCloseListener(listener);
}

void KfSioClient::clearListeners()
{
    m_listener->clearListeners();
}

void KfSioClient::connect(const std::string& uri)
{
    m_client->connect(uri);
}

void KfSioClient::connect(const std::string& uri, const std::map<std::string, std::string>& query)
{
    m_client->connect(uri, query);
}

void KfSioClient::connect(const std::string& uri, const std::map<std::string, std::string>& query, const std::map<std::string, std::string>& http_extra_headers)
{
    m_client->connect(uri, query, http_extra_headers);
}

void KfSioClient::close()
{
    m_client->close();
}

void KfSioClient::syncClose()
{
    m_client->sync_close();
}

void KfSioClient::setReconnectAttempts(int attempts)
{
    m_client->set_reconnect_attempts(attempts);
}

void KfSioClient::setReconnectDelay(unsigned int millis)
{
    m_client->set_reconnect_delay(millis);
}

void KfSioClient::setReconnectDelayMax(unsigned int millis)
{
    m_client->set_reconnect_delay_max(millis);
}

bool KfSioClient::isOpen() const
{
    return m_client->opened();
}

std::string const& KfSioClient::getSessionId() const
{
    return m_client->get_sessionid();
}

void KfSioClient::on(std::string const& eventName, EventListener eventListener, const std::string& socketNs)
{
    sio::socket::event_listener_aux fnc = [eventListener](const std::string& name, sio::message::ptr const& message, bool needAck, sio::message::list& ackMessage) {

        KfSioMessageList ackList;
        int msgSize = (int) ackMessage.size();
        for (int i = 0; i < msgSize; ++i) {
            ackList.push_back(std::make_shared<KfSioMessage>(ackMessage.at(i).get()));
        }

        KfSioMessagePtr kfmessage = std::make_shared<KfSioMessage>(message.get());
        eventListener(name, kfmessage, needAck, ackList);

        int ackSize = (int) ackList.size();
        for (int i = msgSize; i < ackSize; ++i) {
            KfSioMessage* cMsg = dynamic_cast<KfSioMessage*>(ackList.at(i).get());
            if (nullptr == cMsg) {
                continue;
            }
            ackMessage.push(cMsg->m_message);
        }
    };

    _KFSIO_CLIENT_LOCK;
    m_client->socket(socketNs)->on(eventName, fnc);
    _KFSIO_CLIENT_UNLOCK;
}

void KfSioClient::off(std::string const& eventName, const std::string& socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client->socket(socketNs)->off(eventName);
    _KFSIO_CLIENT_UNLOCK;
}

void KfSioClient::offAll(const std::string& socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client->socket(socketNs)->off_all();
    _KFSIO_CLIENT_UNLOCK;
}

void KfSioClient::close(const std::string& socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client->socket(socketNs)->close();
    _KFSIO_CLIENT_UNLOCK;
}

void KfSioClient::onError(ErrorListener listener, const std::string& socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client->socket(socketNs)->on_error([listener](const std::shared_ptr<sio::message>& message) {
        KfSioMessagePtr kfmsg = std::make_shared<KfSioMessage>(message.get());
        listener(kfmsg);
    });
    _KFSIO_CLIENT_UNLOCK;
}

void KfSioClient::offError(const std::string& socketNs)
{
    _KFSIO_CLIENT_LOCK;
    m_client->socket(socketNs)->off_error();
    _KFSIO_CLIENT_UNLOCK;
}

void KfSioClient::emit(const std::string& name, const std::string& message, const AckListener& ack, const std::string& socketNs)
{
    KfSioMessageList msgList;
    msgList.push_back(std::make_shared<KfSioMessage>(message));
    emit(name, msgList, ack, socketNs);
}

void KfSioClient::emit(const std::string& name, const KfSioMessageList& msglist, const AckListener& ack, const std::string& socketNs)
{
    sio::message::list sioMsgList = nullptr;
    if (!msglist.empty()) {
        for (const KfSioMessagePtr& msg : msglist) {
            KfSioMessage* cMsg = dynamic_cast<KfSioMessage*>(msg.get());
            if (nullptr == cMsg) {
                continue;
            }
            sioMsgList.push(cMsg->m_message);
        }
    }

    std::function<void(sio::message::list const&)> ackFun = nullptr;
    if (nullptr != ack) {
        ackFun = [ack](sio::message::list const& ackMsgList) {
            KfSioMessageList ackList;
            int msgSize = (int) ackMsgList.size();
            for (int i = 0; i < msgSize; ++i) {
                ackList.push_back(std::make_shared<KfSioMessage>(ackMsgList.at(i).get()));
            }
            ack(ackList);
        };
    }

    _KFSIO_CLIENT_LOCK;
    m_client->socket(socketNs)->emit(
        name,
        sioMsgList,
        ackFun
    );
    _KFSIO_CLIENT_UNLOCK;
}
