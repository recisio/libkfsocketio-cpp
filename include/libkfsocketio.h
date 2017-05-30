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

#include <memory>

#include "IKfSioClient.h"
#include "IKfWebSocketServer.h"

extern "C" LIBKFSOCKETIO_ABSTRACT_DLL IKfSioClient* __stdcall KfSioClientFactory();
extern "C" LIBKFSOCKETIO_ABSTRACT_DLL IKfWebSocketServer* __stdcall KfWebSocketServerFactory();


#endif // _LIBKFSOCKETIO_H
