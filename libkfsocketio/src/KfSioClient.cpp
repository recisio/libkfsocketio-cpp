#include "KfSioClient.h"

#include "KfSioListener.h"
#include "sio_client.h"

KfSioClient::KfSioClient() :
    m_client(new sio::client()),
    m_listener(new KfSioListener(m_client))
{
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

bool KfSioClient::isOpened() const
{
    return m_client->opened();
}

std::string const& KfSioClient::getSessionId() const
{
    return m_client->get_sessionid();
}

