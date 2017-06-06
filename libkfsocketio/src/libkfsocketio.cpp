#include "libkfsocketio.h"

#include "KfSioClient.h"
#include "KfWebSocketServer.h"
#include "KfSioMessage.h"
#include "KfWebSocketMessage.h"

/*
IKfSioClient* APICALL KfSioClientFactory()
{
    return new KfSioClient();
}

IKfSioMessage* APICALL KfSioMessageFactory()
{
    return new KfSioMessage();
}

void APICALL KfSioClientDispose(IKfSioClient* client)
{
    delete (KfSioClient*) client;
}

void APICALL KfSioMessageDispose(IKfSioMessage* message)
{
    delete (KfSioMessage*) message;
}
*/

// Web Socket Server

WebSocketServerPtr APICALL KfWssCreate()
{
    return (WebSocketServerPtr) new KfWebSocketServer();
}

void APICALL KfWssDispose(WebSocketServerPtr srv)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        delete server;
    }
}

void APICALL KfWssRun(WebSocketServerPtr srv, uint16_t port)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        server->run(port);
    }
}

void APICALL KfWssStart(WebSocketServerPtr srv, uint16_t port)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        server->start(port);
    }
}

size_t APICALL KfWssPoll(WebSocketServerPtr srv)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        return server->poll();
    }
    return 0;
}

size_t APICALL KfWssPollOne(WebSocketServerPtr srv)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        return server->pollOne();
    }
    return 0;
}

void APICALL KfWssStop(WebSocketServerPtr srv)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        server->stop();
    }
}

uint8_t APICALL KfWssIsListening(WebSocketServerPtr srv)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        return server->isListening() ? 1 : 0;
    }
    return 0;
}

void APICALL KfWssUnbindListeners(WebSocketServerPtr srv)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        server->unbindListeners();
    }
}

void APICALL KfWssSetOpenListener(WebSocketServerPtr srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        if (nullptr == listener) {
            server->setOpenListener(nullptr);
        } else {
            server->setOpenListener([listener](KfWebSocketConnectionPtr con) {
                (listener) (static_cast<WebSocketConnectionPtr>(con));
            });
        }
    }
}

void APICALL KfWssSetCloseListener(WebSocketServerPtr srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        if (nullptr == listener) {
            server->setCloseListener(nullptr);
        } else {
            server->setCloseListener([listener](KfWebSocketConnectionPtr con) {
                (listener) (static_cast<WebSocketConnectionPtr>(con));
            });
        }
    }
}

void APICALL KfWssSetFailListener(WebSocketServerPtr srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        if (nullptr == listener) {
            server->setFailListener(nullptr);
        } else {
            server->setFailListener([listener](KfWebSocketConnectionPtr con) {
                (listener) (static_cast<WebSocketConnectionPtr>(con));
            });
        }
    }
}

void APICALL KfWssSetHttpListener(WebSocketServerPtr srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        if (nullptr == listener) {
            server->setHttpListener(nullptr);
        } else {
            server->setHttpListener([listener](KfWebSocketConnectionPtr con) {
                (listener) (static_cast<WebSocketConnectionPtr>(con));
            });
        }
    }
}

void APICALL KfWssSetInterruptListener(WebSocketServerPtr srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        if (nullptr == listener) {
            server->setInterruptListener(nullptr);
        } else {
            server->setInterruptListener([listener](KfWebSocketConnectionPtr con) {
                (listener) (static_cast<WebSocketConnectionPtr>(con));
            });
        }
    }
}

void APICALL KfWssSetMessageListener(WebSocketServerPtr srv, KfWssMessageListener listener)
{
    if (nullptr != srv) {
        KfWebSocketServer* server = static_cast<KfWebSocketServer*>(srv);
        if (nullptr == listener) {
            server->setMessageListener(nullptr);
        } else {
            server->setMessageListener([listener](KfWebSocketConnectionPtr con, KfWebSocketMessagePtr msg) {
                (listener) (static_cast<WebSocketConnectionPtr>(con), static_cast<WebSocketMessagePtr>(msg));
            });
        }
    }
}

// =========== Web Socket Connection

uint8_t APICALL KfWscAreEqual(WebSocketConnectionPtr left, WebSocketConnectionPtr right)
{
    KfWebSocketConnection* l = static_cast<KfWebSocketConnection*>(left);
    KfWebSocketConnection* r = static_cast<KfWebSocketConnection*>(right);

    if (nullptr == l && nullptr == r) {
        return 1;
    }

    if (nullptr == l || nullptr == r) {
        return 0;
    }

    return (*l) == (*r);
}

void APICALL KfWscSend(WebSocketConnectionPtr con, const char* payload, uint8_t opcode)
{
    KfWebSocketConnection* connection = static_cast<KfWebSocketConnection*>(con);
    if (nullptr == connection) {
        return;
    }

    connection->send(payload, (KfWebSocketConnection::OpCode) opcode);
}

void APICALL KfWscClose(WebSocketConnectionPtr con)
{
    KfWebSocketConnection* connection = static_cast<KfWebSocketConnection*>(con);
    if (nullptr == connection) {
        return;
    }
    connection->close();
}

void APICALL KfWscCloseWithStatus(WebSocketConnectionPtr con, uint32_t status, const char* reason)
{
    KfWebSocketConnection* connection = static_cast<KfWebSocketConnection*>(con);
    if (nullptr == connection) {
        return;
    }
    connection->close((KfWebSocketConnection::CloseStatus) status, reason);
}

const char* APICALL KfWscGetRemoteEndpoint(WebSocketConnectionPtr con)
{
    KfWebSocketConnection* connection = static_cast<KfWebSocketConnection*>(con);
    if (nullptr == connection) {
        return "";
    }
    return connection->getRemoteEndpoint();
}

uint8_t APICALL KfWscGetState(WebSocketConnectionPtr con)
{
    KfWebSocketConnection* connection = static_cast<KfWebSocketConnection*>(con);
    if (nullptr == connection) {
        return 0;
    }
    return (uint8_t) connection->getState();
}

// =========== Web Socket Message

uint8_t APICALL KfWsmIsCompressed(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return 0;
    }
    return message->isCompressed() ? 1 : 0;
}

uint8_t APICALL KfWsmIsFin(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return 0;
    }
    return message->isFin() ? 1 : 0;
}

uint8_t APICALL KfWsmIsPrepared(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return 0;
    }
    return message->isPrepared() ? 1 : 0;
}

const char* APICALL KfWsmGetExtensionData(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return "";
    }
    return message->getExtensionData();
}

const char* APICALL KfWsmGetHeader(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return "";
    }
    return message->getHeader();
}

const char* APICALL KfWsmGetPayload(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return "";
    }
    return message->getPayload();
}

const char* APICALL KfWsmGetRawPayload(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return "";
    }
    return message->getRawPayload();
}

uint8_t APICALL KfWsmGetOpcode(WebSocketMessagePtr msg)
{
    KfWebSocketMessage* message = static_cast<KfWebSocketMessage*>(msg);
    if (nullptr == message) {
        return 0;
    }
    return (uint8_t) message->getOpcode();
}
