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

#include <boost/lexical_cast.hpp>

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

KfSioMessage::KfSioMessage(const char* msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const std::shared_ptr<const std::string>& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(KfSioMessageList msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const bool& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const KfSioMessage& copy) :
    m_message(copy.m_message)
{
}

KfSioMessage::KfSioMessage(const std::shared_ptr<sio::message>& sptr) :
    KfSioMessage()
{
    m_message = sptr;
}

KfSioMessage::~KfSioMessage()
{
}

void KF_CALLCONV KfSioMessage::create(const int& msg)
{
    m_message = sio::int_message::create((int64_t) msg);
}

void KF_CALLCONV KfSioMessage::create(const double& msg)
{
    m_message = sio::double_message::create(msg);
}

void KF_CALLCONV KfSioMessage::create(const char* msg)
{
    m_message = sio::string_message::create(msg);
}

void KF_CALLCONV KfSioMessage::create(const std::shared_ptr<const std::string>& msg)
{
    m_message = sio::binary_message::create(msg);
}

void KF_CALLCONV KfSioMessage::create(KfSioMessageList msg)
{
    sio::array_message::ptr apiMessage = sio::array_message::create();
    sio::array_message* apiMessagePtr = (sio::array_message*) apiMessage.get();

    while (nullptr != msg) {
        KfSioMessageListItem* current = msg;
        msg = current->next;

        KfSioMessage* cMsg = dynamic_cast<KfSioMessage*>(current->item);
        if (nullptr == cMsg) {
            continue;
        }
        apiMessagePtr->push(cMsg->m_message);
    }

    m_message = apiMessage;
}

void KF_CALLCONV KfSioMessage::create(const bool& msg)
{
    m_message = sio::bool_message::create(msg);
}

int KF_CALLCONV KfSioMessage::getMessageType() const
{
    if (nullptr == m_message) {
        return KFSIO_MSGTYPE_NULL;
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
        default:
            return KFSIO_MSGTYPE_NULL;
    }
}

bool KF_CALLCONV KfSioMessage::isInt() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_integer);
}

bool KF_CALLCONV KfSioMessage::isDouble() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_double);
}

bool KF_CALLCONV KfSioMessage::isString() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_string);
}

bool KF_CALLCONV KfSioMessage::isBinary() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_binary);
}

bool KF_CALLCONV KfSioMessage::isArray() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_array);
}

bool KF_CALLCONV KfSioMessage::isObject() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_object);
}

bool KF_CALLCONV KfSioMessage::isBool() const
{
    return (nullptr != m_message && m_message->get_flag() == sio::message::flag_boolean);
}

bool KF_CALLCONV KfSioMessage::isNull() const
{
    return (nullptr == m_message || m_message->get_flag() == sio::message::flag_null);
}

int KF_CALLCONV KfSioMessage::getInt() const
{
    if (!isInt()) {
        throw std::bad_typeid();
    }

    return (int) m_message->get_int();
}

double KF_CALLCONV KfSioMessage::getDouble() const
{
    if (!isDouble()) {
        throw std::bad_typeid();
    }

    return m_message->get_double();
}

std::string KF_CALLCONV KfSioMessage::getString() const
{
    if (!isString() && !isObject()) {
        throw std::bad_typeid();
    }

    if (isString()) {
        return m_message->get_string();
    }

    return getObjectJson(m_message->get_map());
}

std::string KF_CALLCONV KfSioMessage::getJsonValue(sio::message::ptr pt) const
{
    std::string json;
    switch (pt->get_flag()) {
        case sio::message::flag_array:
            json += getArrayJson(pt->get_vector());
            break;
        case sio::message::flag_boolean:
            json += pt->get_bool() ? "true" : "false";
            break;
        case sio::message::flag_double:
            json += boost::lexical_cast<std::string>(pt->get_double());
            break;
        case sio::message::flag_integer:
            json += boost::lexical_cast<std::string>(pt->get_int());
            break;
        case sio::message::flag_null:
            json += "null";
            break;
        case sio::message::flag_object:
            json += getObjectJson(pt->get_map());
            break;
        case sio::message::flag_string:
            json += "\"" + pt->get_string() + "\"";
            break;
    }
    return json;
}

std::string KF_CALLCONV KfSioMessage::getArrayJson(std::vector<sio::message::ptr> vec) const
{
    std::string json;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (json.empty()) {
            json += '[';
        } else {
            json += ", ";
        }

        json += getJsonValue(*it);
    }

    if (!json.empty()) {
        json += ']';
    }

    return json;
}

std::string KF_CALLCONV KfSioMessage::getObjectJson(std::map<std::string, sio::message::ptr> msgMap) const
{
    std::string json;
    for (auto it = msgMap.begin(); it != msgMap.end(); ++it) {
        if (json.empty()) {
            json += '{';
        } else {
            json += ", ";
        }

        json += "\"" + it->first + "\" : ";

        json += getJsonValue(it->second);
    }

    if (!json.empty()) {
        json += '}';
    }

    return json;
}

const std::shared_ptr<const std::string>& KF_CALLCONV KfSioMessage::getBinary() const
{
    if (!isBinary()) {
        throw std::bad_typeid();
    }

    return m_message->get_binary();
}

KfSioMessageList KF_CALLCONV KfSioMessage::getArray() const
{
    if (!isArray()) {
        throw std::bad_typeid();
    }

    KfSioMessageList ar = nullptr;
    const std::vector<std::shared_ptr<sio::message> >& vVec = m_message->get_vector();

    KfSioMessageListItem* previous = nullptr;
    for (const std::shared_ptr<sio::message>& ptr : vVec) {
        KfSioMessageListItem* current = new KfSioMessageListItem();
        if (nullptr == previous) {
            ar = current;
        } else {
            previous->next = current;
        }

        current->item = new KfSioMessage(ptr);
        previous = current;
    }

    return ar;
}

void KF_CALLCONV KfSioMessage::releaseArray(KfSioMessageList arr) const
{
    while (arr != nullptr) {
        KfSioMessageListItem* current = arr;
        arr = current->next;

        KfSioMessage* item = dynamic_cast<KfSioMessage*>(current->item);
        if (nullptr != item) {
            delete item;
        }

        delete current;
    }
}

bool KF_CALLCONV KfSioMessage::getBool() const
{
    if (!isBool()) {
        throw std::bad_typeid();
    }

    return m_message->get_bool();
}

