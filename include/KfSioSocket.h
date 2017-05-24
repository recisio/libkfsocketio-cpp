#ifndef _KFSIOSOCKET_H
#define _KFSIOSOCKET_H

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
#define LIBKFSOCKETIO_SIOSOCKET_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_SIOSOCKET_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#include <string>

namespace sio {
class client;
}

class KfSioClient;

class KfSioSocket {


public:
    LIBKFSOCKETIO_SIOSOCKET_DLL KfSioSocket(KfSioClient* client);
    LIBKFSOCKETIO_SIOSOCKET_DLL virtual ~KfSioSocket();

    LIBKFSOCKETIO_SIOSOCKET_DLL void on(std::string const& eventName, void* eventListener, const std::string& socketNs = "");
    LIBKFSOCKETIO_SIOSOCKET_DLL void on(std::string const& eventName, void* eventListener, const std::string& socketNs = "");
    LIBKFSOCKETIO_SIOSOCKET_DLL void off(std::string const& eventName, const std::string& socketNs = "");
    LIBKFSOCKETIO_SIOSOCKET_DLL void offAll(const std::string& socketNs = "");
    LIBKFSOCKETIO_SIOSOCKET_DLL void close(const std::string& socketNs = "");
    LIBKFSOCKETIO_SIOSOCKET_DLL void onError(void* listener, const std::string& socketNs = "");
    LIBKFSOCKETIO_SIOSOCKET_DLL void offError(const std::string& socketNs = "");
    // LIBKFSOCKETIO_SIOSOCKET_DLL void emit(std::string const& name, message::list const& msglist = nullptr, std::function<void(message::list const&)> const& ack = nullptr, const std::string& socketNs = "");

private:
    KfSioClient* m_client;

};

#endif // !_KFSIOSOCKET_H
