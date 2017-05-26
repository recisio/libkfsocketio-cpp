#ifndef _KFWEBSOCKETCONNECTION_H
#define _KFWEBSOCKETCONNECTION_H

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
#define LIBKFSOCKETIO_WEBSOCKETCONNECTION_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_WEBSOCKETCONNECTION_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#include <memory>

struct KfWebSocketConImplWrapper;

class LIBKFSOCKETIO_WEBSOCKETCONNECTION_DLL KfWebSocketConnection {

public:
    KfWebSocketConnection();
    KfWebSocketConnection(const KfWebSocketConnection& copy);
    KfWebSocketConnection(const KfWebSocketConImplWrapper& wrapper);
    virtual ~KfWebSocketConnection();

private:
    KfWebSocketConImplWrapper* m_connection;

};

typedef std::shared_ptr<KfWebSocketConnection> KfWebSocketConnectionSPtr;

#endif // _KFWEBSOCKETCONNECTION_H
