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

#ifdef __cplusplus
#define CEXT extern "C"
#include <cstdint>
#else
#define CEXT
#endif // __cplusplus

#ifdef LIBKFSOCKETIO_EXPORTS
#define LIBKFSOCKETIO_ABSTRACT_DLL CEXT __declspec(dllexport) 
#else
#define LIBKFSOCKETIO_ABSTRACT_DLL CEXT __declspec(dllimport) 
#endif // LIBKFSOCKETIO_EXPORTS

#ifndef KF_CALLCONV
#define KF_CALLCONV __cdecl
#endif // KF_CALLCONV

#define APICALL KF_CALLCONV

#define KFWSC_OPCODE_CONTINUATION 0x0
#define KFWSC_OPCODE_TEXT 0x1
#define KFWSC_OPCODE_BINARY 0x2
#define KFWSC_OPCODE_RSV3 0x3
#define KFWSC_OPCODE_RSV4 0x4
#define KFWSC_OPCODE_RSV5 0x5
#define KFWSC_OPCODE_RSV6 0x6
#define KFWSC_OPCODE_RSV7 0x7
#define KFWSC_OPCODE_CLOSE 0x8
#define KFWSC_OPCODE_PING 0x9
#define KFWSC_OPCODE_PONG 0xA
#define KFWSC_OPCODE_CONTROL_RSVB 0xB
#define KFWSC_OPCODE_CONTROL_RSVC 0xC
#define KFWSC_OPCODE_CONTROL_RSVD 0xD
#define KFWSC_OPCODE_CONTROL_RSVE 0xE
#define KFWSC_OPCODE_CONTROL_RSVF 0xF

#define KFWSC_CLOSESTATUS_BLANK 0
#define KFWSC_CLOSESTATUS_OMIT_HANDSHAKE 1
#define KFWSC_CLOSESTATUS_FORCE_TCP_DROP 2
#define KFWSC_CLOSESTATUS_NORMAL 1000
#define KFWSC_CLOSESTATUS_GOING_AWAY 1001
#define KFWSC_CLOSESTATUS_PROTOCOL_ERROR 1002
#define KFWSC_CLOSESTATUS_UNSUPPORTED_DATA 1003
#define KFWSC_CLOSESTATUS_NO_STATUS 1005
#define KFWSC_CLOSESTATUS_ABNORMAL_CLOSE 1006
#define KFWSC_CLOSESTATUS_INVALID_PAYLOAD 1007
#define KFWSC_CLOSESTATUS_POLICY_VIOLATION 1008
#define KFWSC_CLOSESTATUS_MESSAGE_TOO_BIG 1009
#define KFWSC_CLOSESTATUS_EXTENSION_REQUIRED 1010
#define KFWSC_CLOSESTATUS_INTERNAL_ENDPOINT_ERROR 1011
#define KFWSC_CLOSESTATUS_SERVICE_RESTART 1012
#define KFWSC_CLOSESTATUS_TRY_AGAIN_LATER 1013
#define KFWSC_CLOSESTATUS_TLS_HANDSHAKE 1015
#define KFWSC_CLOSESTATUS_SUBPROTOCOL_ERROR 3000
#define KFWSC_CLOSESTATUS_INVALID_SUBPROTOCOL_DATA 3001
#define KFWSC_CLOSESTATUS_INVALID_LOW 999
#define KFWSC_CLOSESTATUS_INVALID_HIGH 5000

#define KFWSC_STATE_CONNECTING 0
#define KFWSC_STATE_OPEN  1
#define KFWSC_STATE_CLOSING 2
#define KFWSC_STATE_CLOSED 3

class KfWebSocketServer;
class KfWebSocketConnection;
class KfWebSocketMessage;
class KfSioClient;

typedef uint8_t KfBool;

// =========== Socket.Io Client

// LIBKFSOCKETIO_ABSTRACT_DLL SioClientPtr APICALL KfSioClientFactory();
// LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioClientDispose(KfSioClientPtr);

// =========== Socket.Io Message

// LIBKFSOCKETIO_ABSTRACT_DLL IKfSioMessage* APICALL KfSioMessageFactory();
// LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioMessageDispose(IKfSioMessage*);

// =========== Web Socket Server

typedef void (APICALL *KfWssConnectionListener)(KfWebSocketConnection*);
typedef void (APICALL *KfWssMessageListener)(KfWebSocketConnection*, KfWebSocketMessage*);

LIBKFSOCKETIO_ABSTRACT_DLL KfWebSocketServer* APICALL KfWssCreate();
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssDispose(KfWebSocketServer* srv);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfWssRun(KfWebSocketServer* srv, uint16_t port);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfWssStart(KfWebSocketServer* srv, uint16_t port);
LIBKFSOCKETIO_ABSTRACT_DLL size_t APICALL KfWssPoll(KfWebSocketServer* srv);
LIBKFSOCKETIO_ABSTRACT_DLL size_t APICALL KfWssPollOne(KfWebSocketServer* srv);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssStop(KfWebSocketServer* srv);
LIBKFSOCKETIO_ABSTRACT_DLL uint8_t APICALL KfWssIsListening(KfWebSocketServer* srv);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssUnbindListeners(KfWebSocketServer* srv);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssSetOpenListener(KfWebSocketServer* srv, KfWssConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssSetCloseListener(KfWebSocketServer* srv, KfWssConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssSetFailListener(KfWebSocketServer* srv, KfWssConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssSetHttpListener(KfWebSocketServer* srv, KfWssConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssSetInterruptListener(KfWebSocketServer* srv, KfWssConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWssSetMessageListener(KfWebSocketServer* srv, KfWssMessageListener listener);

// =========== Web Socket Connection

LIBKFSOCKETIO_ABSTRACT_DLL uint8_t APICALL KfWscAreEqual(KfWebSocketConnection* left, KfWebSocketConnection* right);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWscSend(KfWebSocketConnection* con, const char* payload, uint8_t opcode);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWscClose(KfWebSocketConnection* con);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfWscCloseWithStatus(KfWebSocketConnection* con, uint32_t status, const char* reason);
LIBKFSOCKETIO_ABSTRACT_DLL const char* APICALL KfWscGetRemoteEndpoint(KfWebSocketConnection* con);
LIBKFSOCKETIO_ABSTRACT_DLL uint8_t APICALL KfWscGetState(KfWebSocketConnection* con);

// =========== Web Socket Message

LIBKFSOCKETIO_ABSTRACT_DLL uint8_t APICALL KfWsmIsCompressed(KfWebSocketMessage*);
LIBKFSOCKETIO_ABSTRACT_DLL uint8_t APICALL KfWsmIsFin(KfWebSocketMessage*);
LIBKFSOCKETIO_ABSTRACT_DLL uint8_t APICALL KfWsmIsPrepared(KfWebSocketMessage*);
LIBKFSOCKETIO_ABSTRACT_DLL const char* APICALL KfWsmGetExtensionData(KfWebSocketMessage*);
LIBKFSOCKETIO_ABSTRACT_DLL const char* APICALL KfWsmGetHeader(KfWebSocketMessage*);
LIBKFSOCKETIO_ABSTRACT_DLL const char* APICALL KfWsmGetPayload(KfWebSocketMessage*);
LIBKFSOCKETIO_ABSTRACT_DLL const char* APICALL KfWsmGetRawPayload(KfWebSocketMessage*);
LIBKFSOCKETIO_ABSTRACT_DLL uint8_t APICALL KfWsmGetOpcode(KfWebSocketMessage*);

#endif // _LIBKFSOCKETIO_H
