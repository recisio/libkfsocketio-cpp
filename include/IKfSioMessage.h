#ifndef _IKFSIOMESSAGE_H
#define _IKFSIOMESSAGE_H

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

#include <string>
#include <vector>
#include <memory>
#include <map>

class IKfSioMessage;

typedef std::shared_ptr<IKfSioMessage> KfSioMessagePtr;
typedef std::vector<KfSioMessagePtr> KfSioMessageList;

class IKfSioMessage {

public:
    /// Creates an INTEGER-typed message
    virtual void create(const int& msg) = 0;
    /// Creates a DOUBLE-typed message
    virtual void create(const double& msg) = 0;
    /// Creates a STRING-typed message
    virtual void create(const std::string& msg) = 0;
    /// Creates a BINARY-typed message
    virtual void create(const std::shared_ptr<const std::string>& msg) = 0;
    /// Creates an ARRAY-typed message
    virtual void create(const std::vector<KfSioMessagePtr>& msg) = 0;
    /// Creates an OBJECT-typed message
    virtual void create(const std::map<std::string, KfSioMessagePtr>& msg) = 0;
    /// Creates a BOOLEAN-typed message
    virtual void create(const bool& msg) = 0;
    /// Creates a NULL-typed message
    virtual void create(const nullptr_t& msg) = 0;

    virtual int getMessageType() const = 0;
    virtual const bool isInt() const = 0;
    virtual const bool isDouble() const = 0;
    virtual const bool isString() const = 0;
    virtual const bool isBinary() const = 0;
    virtual const bool isArray() const = 0;
    virtual const bool isObject() const = 0;
    virtual const bool isBool() const = 0;
    virtual const bool isNull() const = 0;
    virtual const bool isUndefined() const = 0;

    virtual int getInt() const = 0;
    virtual double getDouble() const = 0;
    virtual const std::string& getString() const = 0;
    virtual const std::shared_ptr<const std::string>& getBinary() const = 0;
    virtual std::vector<KfSioMessagePtr> getArray() const = 0;
    virtual std::map<std::string, KfSioMessagePtr> getObject() const = 0;
    virtual bool getBool() const = 0;

};

#endif // _IKFSIOMESSAGE_H
