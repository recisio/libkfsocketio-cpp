#include "KfWebSocketMessage.h"

#include "KfWebSocketMessageImplWrapper.h"

KfWebSocketMessage::KfWebSocketMessage(const KfWebSocketMessageImplWrapper& message) :
    m_message(new KfWebSocketMessageImplWrapper({message.message}))
{
}

KfWebSocketMessage::KfWebSocketMessage(const KfWebSocketMessage& copy) :
    m_message(new KfWebSocketMessageImplWrapper({copy.m_message->message}))
{
}

KfWebSocketMessage::~KfWebSocketMessage()
{
    delete m_message;
}

void KfWebSocketMessage::setCompressed(const bool& isCompressed)
{
    m_message->message->set_compressed(isCompressed);
}

void KfWebSocketMessage::setFin(const bool& isFin)
{
    m_message->message->set_fin(isFin);
}

void KfWebSocketMessage::setHeader(const std::string& header)
{
    m_message->message->set_header(header);
}

void KfWebSocketMessage::setOpcode(const KfWebSocketConnection::OpCode& opcode)
{
    m_message->message->set_opcode((websocketpp::frame::opcode::value) opcode);
}

void KfWebSocketMessage::setPayload(const std::string& payload)
{
    m_message->message->set_payload(payload);
}

void KfWebSocketMessage::appendPayload(const std::string& payload)
{
    m_message->message->append_payload(payload);
}

bool KfWebSocketMessage::isCompressed() const
{
    return m_message->message->get_compressed();
}

bool KfWebSocketMessage::isFin() const
{
    return m_message->message->get_fin();
}

bool KfWebSocketMessage::isPrepared() const
{
    return m_message->message->get_prepared();
}

std::string KfWebSocketMessage::getExtensionData() const
{
    return m_message->message->get_extension_data();
}

std::string KfWebSocketMessage::getHeader() const
{
    return m_message->message->get_header();
}

std::string KfWebSocketMessage::getPayload() const
{
    return m_message->message->get_payload();
}

std::string KfWebSocketMessage::getRawPayload() const
{
    return m_message->message->get_raw_payload();
}

KfWebSocketConnection::OpCode KfWebSocketMessage::getOpcode() const
{
    return (KfWebSocketConnection::OpCode) m_message->message->get_opcode();
}
