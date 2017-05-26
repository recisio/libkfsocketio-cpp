#ifndef _KFSIOMESSAGE_H
#define _KFSIOMESSAGE_H

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

#ifdef LIBKFSOCKETIO_EXPORTS
#define LIBKFSOCKETIO_SIOMESSAGE_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_SIOMESSAGE_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#include <memory>
#include <string>
#include <vector>
#include <map>

namespace sio {
class message;
}

class KfSioClient;

// Disable nothrow spec warning if needed
#ifdef NO_VS4290_WARNING
#pragma warning(disable : 4290)  
#endif

#define KFSIO_MSGTYPE_NONE      -1
#define KFSIO_MSGTYPE_INT       0
#define KFSIO_MSGTYPE_DOUBLE    1
#define KFSIO_MSGTYPE_STRING    2
#define KFSIO_MSGTYPE_BINARY    3
#define KFSIO_MSGTYPE_ARRAY     4
#define KFSIO_MSGTYPE_OBJECT    5
#define KFSIO_MSGTYPE_BOOLEAN   6
#define KFSIO_MSGTYPE_NULL      7

class LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage {
    friend class KfSioClient;

public:
    KfSioMessage();

    /// Creates an INTEGER-typed message
    KfSioMessage(const int& msg);
    /// Creates a DOUBLE-typed message
    KfSioMessage(const double& msg);
    /// Creates a STRING-typed message
    KfSioMessage(const std::string& msg);
    /// Creates a BINARY-typed message
    KfSioMessage(const std::shared_ptr<const std::string>& msg);
    /// Creates an ARRAY-typed message
    KfSioMessage(const std::vector<KfSioMessage>& msg);
    /// Creates an OBJECT-typed message
    KfSioMessage(const std::map<std::string, KfSioMessage>& msg);
    /// Creates a BOOLEAN-typed message
    KfSioMessage(const bool& msg);
    /// Creates a NULL-typed message
    KfSioMessage(const nullptr_t& msg);

    KfSioMessage(const KfSioMessage& copy);
    KfSioMessage(sio::message* internal);

    ~KfSioMessage();

    /// Creates an INTEGER-typed message
    void create(const int& msg);
    /// Creates a DOUBLE-typed message
    void create(const double& msg);
    /// Creates a STRING-typed message
    void create(const std::string& msg);
    /// Creates a BINARY-typed message
    void create(const std::shared_ptr<const std::string>& msg);
    /// Creates an ARRAY-typed message
    void create(const std::vector<KfSioMessage>& msg);
    /// Creates an OBJECT-typed message
    void create(const std::map<std::string, KfSioMessage>& msg);
    /// Creates a BOOLEAN-typed message
    void create(const bool& msg);
    /// Creates a NULL-typed message
    void create(const nullptr_t& msg);

    int getMessageType() const;
    const bool isInt() const;
    const bool isDouble() const;
    const bool isString() const;
    const bool isBinary() const;
    const bool isArray() const;
    const bool isObject() const;
    const bool isBool() const;
    const bool isNull() const;
    const bool isUndefined() const;

    int getInt() const throw(std::bad_typeid);
    double getDouble() const throw(std::bad_typeid);
    const std::string& getString() const throw(std::bad_typeid);
    const std::shared_ptr<const std::string>& getBinary() const throw(std::bad_typeid);
    std::vector<KfSioMessage> getArray() const throw(std::bad_typeid);
    std::map<std::string, KfSioMessage> getObject() const throw(std::bad_typeid);
    bool getBool() const throw(std::bad_typeid);

private:
    std::shared_ptr<sio::message> m_message;

};

typedef std::vector<KfSioMessage> KfSioMessageList;

#endif // _KFSIOMESSAGE_H
