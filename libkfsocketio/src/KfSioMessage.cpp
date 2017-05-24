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

KfSioMessage::KfSioMessage(const std::vector<KfSioMessage>& msg) :
    KfSioMessage()
{
    create(msg);
}

KfSioMessage::KfSioMessage(const std::map<std::string, KfSioMessage>& msg) :
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

void KfSioMessage::create(const std::vector<KfSioMessage>& msg)
{
    sio::array_message::ptr apiMessage = sio::array_message::create();
    sio::array_message* apiMessagePtr = (sio::array_message*) apiMessage.get();

    for (const KfSioMessage& message : msg) {
        apiMessagePtr->push(message.m_message);
    }

    m_message = apiMessage;
}

void KfSioMessage::create(const std::map<std::string, KfSioMessage>& msg)
{
    sio::object_message::ptr apiMessage = sio::object_message::create();
    sio::object_message* apiMessagePtr = (sio::object_message*) apiMessage.get();

    for (const std::pair<std::string, KfSioMessage> message : msg) {
        apiMessagePtr->insert(message.first, message.second.m_message);
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
