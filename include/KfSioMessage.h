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

class KfSioMessage {
public:
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage();

    /// Creates an INTEGER-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const int& msg);
    /// Creates a DOUBLE-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const double& msg);
    /// Creates a STRING-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const std::string& msg);
    /// Creates a BINARY-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const std::shared_ptr<const std::string>& msg);
    /// Creates an ARRAY-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const std::vector<KfSioMessage>& msg);
    /// Creates an OBJECT-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const std::map<std::string, KfSioMessage>& msg);
    /// Creates a BOOLEAN-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const bool& msg);
    /// Creates a NULL-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const nullptr_t& msg);

    LIBKFSOCKETIO_SIOMESSAGE_DLL KfSioMessage(const KfSioMessage& copy);
    KfSioMessage(sio::message* internal);

    LIBKFSOCKETIO_SIOMESSAGE_DLL ~KfSioMessage();

    /// Creates an INTEGER-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const int& msg);
    /// Creates a DOUBLE-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const double& msg);
    /// Creates a STRING-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const std::string& msg);
    /// Creates a BINARY-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const std::shared_ptr<const std::string>& msg);
    /// Creates an ARRAY-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const std::vector<KfSioMessage>& msg);
    /// Creates an OBJECT-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const std::map<std::string, KfSioMessage>& msg);
    /// Creates a BOOLEAN-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const bool& msg);
    /// Creates a NULL-typed message
    LIBKFSOCKETIO_SIOMESSAGE_DLL void create(const nullptr_t& msg);

private:
    std::shared_ptr<sio::message> m_message;

};

#endif // _KFSIOMESSAGE_H