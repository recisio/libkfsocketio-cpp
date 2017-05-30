#include "KfSioMessage.h"

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

#include "sio_message.h"

KfSioMessage::KfSioMessage() :
    m_message(nullptr)
{

}

KfSioMessage::KfSioMessage(const int& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const double& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const std::string& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const std::shared_ptr<const std::string>& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const std::vector<KfSioMessagePtr>& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const std::map<std::string, KfSioMessagePtr>& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const bool& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const nullptr_t& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const KfSioMessage& copy) :
    m_message(copy.m_message)
{
}

KfSioMessage::KfSioMessage(sio::message* internal) :
    KfSioMessage()
{
    switch (internal->get_flag()) {
        case sio::message::flag_integer:
            create((int) internal->get_int());
            break;
        case sio::message::flag_double:
            create(internal->get_double());
            break;
        case sio::message::flag_string:
            create(internal->get_string());
            break;
        case sio::message::flag_binary:
            create(internal->get_binary());
            break;
        case sio::message::flag_array:
        {
            sio::array_message::ptr apiMessage = sio::array_message::create();
            sio::array_message* apiMessagePtr = (sio::array_message*) apiMessage.get();

            std::vector<std::shared_ptr<sio::message> > vec = internal->get_vector();
            for (std::shared_ptr<sio::message> message : vec) {
                apiMessagePtr->push(message);
            }

            m_message = apiMessage;
        }
        break;
        case sio::message::flag_object:
        {
            sio::object_message::ptr apiMessage = sio::object_message::create();
            sio::object_message* apiMessagePtr = (sio::object_message*) apiMessage.get();

            std::map<std::string, std::shared_ptr<sio::message> > mmap = internal->get_map();
            for (std::pair<std::string, std::shared_ptr<sio::message> > message : mmap) {
                apiMessagePtr->insert(message.first, message.second);
            }

            m_message = apiMessage;
        }
        break;
        case sio::message::flag_boolean:
            create(internal->get_bool());
            break;
        case sio::message::flag_null:
        default:
            create(nullptr);
    }
}

KfSioMessage::~KfSioMessage()
{
}

void KfSioMessage::create(const int& msg)
{
    m_message = sio::int_message::create((int64_t) msg);
}

void KfSioMessage::create(const double& msg)
{
    m_message = sio::double_message::create(msg);
}

void KfSioMessage::create(const std::string& msg)
{
    m_message = sio::string_message::create(msg);
}

void KfSioMessage::create(const std::shared_ptr<const std::string>& msg)
{
    m_message = sio::binary_message::create(msg);
}

void KfSioMessage::create(const std::vector<KfSioMessagePtr>& msg)
{
    sio::array_message::ptr apiMessage = sio::array_message::create();
    sio::array_message* apiMessagePtr = (sio::array_message*) apiMessage.get();

    for (const KfSioMessagePtr& message : msg) {
        KfSioMessage* cMsg = dynamic_cast<KfSioMessage*>(message.get());
        if (nullptr == cMsg) {
            continue;
        }
        apiMessagePtr->push(cMsg->m_message);
    }

    m_message = apiMessage;
}

void KfSioMessage::create(const std::map<std::string, KfSioMessagePtr>& msg)
{
    sio::object_message::ptr apiMessage = sio::object_message::create();
    sio::object_message* apiMessagePtr = (sio::object_message*) apiMessage.get();

    for (const std::pair<std::string, KfSioMessagePtr> message : msg) {
        KfSioMessage* cMsg = dynamic_cast<KfSioMessage*>(message.second.get());
        if (nullptr == cMsg) {
            continue;
        }
        apiMessagePtr->insert(message.first, cMsg->m_message);
    }

    m_message = apiMessage;
}

void KfSioMessage::create(const bool& msg)
{
    m_message = sio::bool_message::create(msg);
}

void KfSioMessage::create(const nullptr_t& msg)
{
    m_message = sio::null_message::create();
}

int KfSioMessage::getMessageType() const
{
    if (nullptr == m_message) {
        return KFSIO_MSGTYPE_NONE;
    }

    switch (m_message->get_flag()) {
        case sio::message::flag_integer:
            return KFSIO_MSGTYPE_INT;
        case sio::message::flag_double:
            return KFSIO_MSGTYPE_DOUBLE;
        case sio::message::flag_string:
            return KFSIO_MSGTYPE_STRING;
        case sio::message::flag_binary:
            return KFSIO_MSGTYPE_BINARY;
        case sio::message::flag_array:
            return KFSIO_MSGTYPE_ARRAY;
        case sio::message::flag_object:
            return KFSIO_MSGTYPE_OBJECT;
        case sio::message::flag_boolean:
            return KFSIO_MSGTYPE_BOOLEAN;
        case sio::message::flag_null:
            return KFSIO_MSGTYPE_NULL;
        default:
            return KFSIO_MSGTYPE_NONE;
    }
}

bool KfSioMessage::isInt() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_integer);
}

bool KfSioMessage::isDouble() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_double);
}

bool KfSioMessage::isString() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_string);
}

bool KfSioMessage::isBinary() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_binary);
}

bool KfSioMessage::isArray() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_array);
}

bool KfSioMessage::isObject() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_object);
}

bool KfSioMessage::isBool() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_boolean);
}

bool KfSioMessage::isNull() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_null);
}

bool KfSioMessage::isUndefined() const
{
    return nullptr == m_message;
}

int KfSioMessage::getInt() const
{
    if (!isInt()) {
        throw std::bad_typeid();
    }

    return (int) m_message->get_int();
}

double KfSioMessage::getDouble() const
{
    if (!isDouble()) {
        throw std::bad_typeid();
    }

    return m_message->get_double();
}

const std::string& KfSioMessage::getString() const
{
    if (!isString()) {
        throw std::bad_typeid();
    }

    return m_message->get_string();
}

const std::shared_ptr<const std::string>& KfSioMessage::getBinary() const
{
    if (!isBinary()) {
        throw std::bad_typeid();
    }

    return m_message->get_binary();
}

std::vector<KfSioMessagePtr> KfSioMessage::getArray() const
{
    if (!isArray()) {
        throw std::bad_typeid();
    }

    std::vector<KfSioMessagePtr> ret;
    const std::vector<std::shared_ptr<sio::message> >& vVec = m_message->get_vector();

    for (const std::shared_ptr<sio::message>& ptr : vVec) {
        ret.push_back(std::make_shared<KfSioMessage>(ptr.get()));
    }

    return ret;
}

std::map<std::string, KfSioMessagePtr> KfSioMessage::getObject() const
{
    if (!isObject()) {
        throw std::bad_typeid();
    }

    std::map<std::string, KfSioMessagePtr> ret;
    const std::map<std::string, std::shared_ptr<sio::message> >& vMap = m_message->get_map();

    for (const std::pair<std::string, std::shared_ptr<sio::message> >& vPair : vMap) {
        ret[vPair.first] = std::make_shared<KfSioMessage>(vPair.second.get());
    }

    return ret;
}

bool KfSioMessage::getBool() const
{
    if (!isBool()) {
        throw std::bad_typeid();
    }

    return m_message->get_bool();
}
