#ifndef _LIBKFSOCKETIO_H
#define _LIBKFSOCKETIO_H

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
#define LIBKFSOCKETIO_ABSTRACT_DLL __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_ABSTRACT_DLL __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#ifndef KF_CALLCONV
#define KF_CALLCONV __cdecl
#endif // KF_CALLCONV

#define APICALL KF_CALLCONV

#include "IKfSioClient.h"
#include "IKfWebSocketServer.h"
#include "IKfSioMessage.h"

extern "C" {
    LIBKFSOCKETIO_ABSTRACT_DLL IKfSioClient* APICALL KfSioClientFactory();
    LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioClientDispose(IKfSioClient*);

    LIBKFSOCKETIO_ABSTRACT_DLL IKfWebSocketServer* APICALL KfWebSocketServerFactory();
    LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWebSocketServerDispose(IKfWebSocketServer*);

    LIBKFSOCKETIO_ABSTRACT_DLL IKfSioMessage* APICALL KfSioMessageFactory();
    LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioMessageDispose(IKfSioMessage*);
}

#endif // _LIBKFSOCKETIO_H
