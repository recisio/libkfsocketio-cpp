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

#define KFSIOMSG_INT       0
#define KFSIOMSG_DOUBLE    1
#define KFSIOMSG_STRING    2
#define KFSIOMSG_BINARY    3
#define KFSIOMSG_ARRAY     4
#define KFSIOMSG_OBJECT    5
#define KFSIOMSG_BOOLEAN   6
#define KFSIOMSG_NULL      7

class KfWebSocketServer;
class KfWebSocketConnection;
class KfWebSocketMessage;
class KfSioClient;
class KfSioMessage;

struct KfSioMsgListItem;

CEXT typedef KfSioMsgListItem* KfSioMsgList;
CEXT typedef uint8_t KfBool;

#pragma pack(push, 1)
CEXT typedef struct {
    const char* key;
    const char* value;
} KfSioClientConnectQueryParam;
#pragma pack(pop)

// =========== Socket.Io Client

CEXT typedef void (APICALL *KfSioConnectionListener)(void);
CEXT typedef void (APICALL *KfSioCloseListener)(unsigned int reason);
CEXT typedef void (APICALL *KfSioReconnectListener)(unsigned int nAttempts, unsigned int delay);
CEXT typedef void (APICALL *KfSioSocketListener)(const char* nsp);
CEXT typedef void (APICALL *KfSioEventListener)(const char* name, KfSioMessage* message, bool needAck, KfSioMsgList ackMessage);
CEXT typedef void (APICALL *KfSioErrorListener)(KfSioMessage* message);
CEXT typedef void (APICALL *KfSioAckListener)(KfSioMsgList);

LIBKFSOCKETIO_ABSTRACT_DLL KfSioClient* APICALL KfSioCreate();
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioDispose(KfSioClient*);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioConnect(
    KfSioClient* client,
    const char* uri,
    KfSioClientConnectQueryParam* query = nullptr,
    unsigned int queryCount = 0,
    KfSioClientConnectQueryParam* httpExtraHeaders = nullptr,
    unsigned int httpExtraHeadersCount = 0);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioEmit(
    KfSioClient* client,
    const char* name,
    const char* message,
    KfSioAckListener ack = nullptr,
    const char* socketNs = "");
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioClose(KfSioClient* client);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSyncClose(KfSioClient* client);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioIsOpen(KfSioClient* client);
LIBKFSOCKETIO_ABSTRACT_DLL const char* APICALL KfSioGetSessionId(KfSioClient* client);

LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioClearListeners(KfSioClient* client);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetClientOpenListener(KfSioClient* client, KfSioConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetClientCloseListener(KfSioClient* client, KfSioCloseListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetClientFailListener(KfSioClient* client, KfSioConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetClientReconnectingListener(KfSioClient* client, KfSioConnectionListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetClientReconnectListener(KfSioClient* client, KfSioReconnectListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetSocketOpenListener(KfSioClient* client, KfSioSocketListener listener);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetSocketCloseListener(KfSioClient* client, KfSioSocketListener listener);

LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetReconnectAttempts(KfSioClient* client, int attempts);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetReconnectDelay(KfSioClient* client, unsigned int millis);
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioSetReconnectDelayMax(KfSioClient* client, unsigned int millis);

LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioOn(KfSioClient* client, const char* eventName, KfSioEventListener eventListener, const char* socketNs = "");
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioOff(KfSioClient* client, const char* eventName, const char* socketNs = "");
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioOffAll(KfSioClient* client, const char* socketNs = "");
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioCloseSocket(KfSioClient* client, const char* socketNs = "");
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioOnError(KfSioClient* client, KfSioErrorListener listener, const char* socketNs = "");
LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioOffError(KfSioClient* client, const char* socketNs = "");

// =========== Socket.Io Message

LIBKFSOCKETIO_ABSTRACT_DLL int APICALL KfSioMsgGetType(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsInt(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsDouble(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsString(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsBinary(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsArray(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsObject(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsBool(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgIsNull(KfSioMessage* msg);

LIBKFSOCKETIO_ABSTRACT_DLL int APICALL KfSioMsgGetInt(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL double APICALL KfSioMsgGetDouble(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL const char* APICALL KfSioMsgGetString(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfSioMsgList APICALL KfSioMsgGetArray(KfSioMessage* msg);
LIBKFSOCKETIO_ABSTRACT_DLL KfBool APICALL KfSioMsgGetBool(KfSioMessage* msg);

// =========== Web Socket Server

CEXT typedef void (APICALL *KfWssConnectionListener)(KfWebSocketConnection*);
CEXT typedef void (APICALL *KfWssMessageListener)(KfWebSocketConnection*, KfWebSocketMessage*);

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
