#include "KfWebSocketMessage.h"

KfWebSocketMessage::KfWebSocketMessage(const WSMessagePtr& message) :
    m_message(message)
{
}

KfWebSocketMessage::KfWebSocketMessage(const KfWebSocketMessage& copy) :
    m_message(copy.m_message)
{
}

void KF_CALLCONV KfWebSocketMessage::setCompressed(const bool& isCompressed)
{
    m_message->set_compressed(isCompressed);
}

void KF_CALLCONV KfWebSocketMessage::setFin(const bool& isFin)
{
    m_message->set_fin(isFin);
}

void KF_CALLCONV KfWebSocketMessage::setHeader(const char* header)
{
    m_message->set_header(header);
}

void KF_CALLCONV KfWebSocketMessage::setOpcode(const IKfWebSocketConnection::OpCode& opcode)
{
    m_message->set_opcode((websocketpp::frame::opcode::value) opcode);
}

void KF_CALLCONV KfWebSocketMessage::setPayload(const char* payload)
{
    m_message->set_payload(payload);
}

void KF_CALLCONV KfWebSocketMessage::appendPayload(const char* payload)
{
    m_message->append_payload(payload);
}

bool KF_CALLCONV KfWebSocketMessage::isCompressed() const
{
    return m_message->get_compressed();
}

bool KF_CALLCONV KfWebSocketMessage::isFin() const
{
    return m_message->get_fin();
}

bool KF_CALLCONV KfWebSocketMessage::isPrepared() const
{
    return m_message->get_prepared();
}

const char* KF_CALLCONV KfWebSocketMessage::getExtensionData() const
{
    return m_message->get_extension_data().c_str();
}

const char* KF_CALLCONV KfWebSocketMessage::getHeader() const
{
    return m_message->get_header().c_str();
}

const char* KF_CALLCONV KfWebSocketMessage::getPayload() const
{
    return m_message->get_payload().c_str();
}

const char* KF_CALLCONV KfWebSocketMessage::getRawPayload() const
{
    return m_message->get_raw_payload().c_str();
}

IKfWebSocketConnection::OpCode KF_CALLCONV KfWebSocketMessage::getOpcode() const
{
    return (IKfWebSocketConnection::OpCode) m_message->get_opcode();
}
