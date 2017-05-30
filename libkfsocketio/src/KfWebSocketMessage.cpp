#include "KfWebSocketMessage.h"

KfWebSocketMessage::KfWebSocketMessage(const WSMessagePtr& message) :
    m_message(message)
{
}

KfWebSocketMessage::KfWebSocketMessage(const KfWebSocketMessage& copy) :
    m_message(copy.m_message)
{
}

void KfWebSocketMessage::setCompressed(const bool& isCompressed)
{
    m_message->set_compressed(isCompressed);
}

void KfWebSocketMessage::setFin(const bool& isFin)
{
    m_message->set_fin(isFin);
}

void KfWebSocketMessage::setHeader(const std::string& header)
{
    m_message->set_header(header);
}

void KfWebSocketMessage::setOpcode(const IKfWebSocketConnection::OpCode& opcode)
{
    m_message->set_opcode((websocketpp::frame::opcode::value) opcode);
}

void KfWebSocketMessage::setPayload(const std::string& payload)
{
    m_message->set_payload(payload);
}

void KfWebSocketMessage::appendPayload(const std::string& payload)
{
    m_message->append_payload(payload);
}

bool KfWebSocketMessage::isCompressed() const
{
    return m_message->get_compressed();
}

bool KfWebSocketMessage::isFin() const
{
    return m_message->get_fin();
}

bool KfWebSocketMessage::isPrepared() const
{
    return m_message->get_prepared();
}

std::string KfWebSocketMessage::getExtensionData() const
{
    return m_message->get_extension_data();
}

std::string KfWebSocketMessage::getHeader() const
{
    return m_message->get_header();
}

std::string KfWebSocketMessage::getPayload() const
{
    return m_message->get_payload();
}

std::string KfWebSocketMessage::getRawPayload() const
{
    return m_message->get_raw_payload();
}

IKfWebSocketConnection::OpCode KfWebSocketMessage::getOpcode() const
{
    return (IKfWebSocketConnection::OpCode) m_message->get_opcode();
}
