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

KfWebSocketServer* APICALL KfWssCreate()
{
    KfWebSocketServer* server = new KfWebSocketServer();
    return server;
}

void APICALL KfWssDispose(KfWebSocketServer* srv)
{
    if (nullptr != srv) {
        delete srv;
    }
}

KfBool APICALL KfWssRun(KfWebSocketServer* srv, uint16_t port)
{
    if (nullptr != srv) {
        try {
            srv->run(port);
            return (KfBool) 1;
        } catch (...) {
        }
    }
    return (KfBool) 0;
}

KfBool APICALL KfWssStart(KfWebSocketServer* srv, uint16_t port)
{
    if (nullptr != srv) {
        try {
            srv->start(port);
            return (KfBool) 1;
        } catch (...) {
        }
    }
    return (KfBool) 0;
}

size_t APICALL KfWssPoll(KfWebSocketServer* srv)
{
    if (nullptr != srv) {
        try {
            return srv->poll();
        } catch (...) {
        }
    }
    return 0;
}

size_t APICALL KfWssPollOne(KfWebSocketServer* srv)
{
    if (nullptr != srv) {
        try {
            return srv->pollOne();
        } catch (...) {
        }
    }
    return 0;
}

void APICALL KfWssStop(KfWebSocketServer* srv)
{
    if (nullptr != srv) {
        try {
            srv->stop();
        } catch (...) {
        }
    }
}

uint8_t APICALL KfWssIsListening(KfWebSocketServer* srv)
{
    if (nullptr != srv) {
        try {
            return srv->isListening() ? 1 : 0;
        } catch (...) {
        }
    }
    return 0;
}

void APICALL KfWssUnbindListeners(KfWebSocketServer* srv)
{
    if (nullptr != srv) {
        try {
            srv->unbindListeners();
        } catch (...) {
        }
    }
}

void APICALL KfWssSetOpenListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            srv->setOpenListener(listener);
        } catch (...) {
        }
    }
}

void APICALL KfWssSetCloseListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            srv->setCloseListener(listener);
        } catch (...) {
        }
    }
}

void APICALL KfWssSetFailListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            srv->setFailListener(listener);
        } catch (...) {
        }
    }
}

void APICALL KfWssSetHttpListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            srv->setHttpListener(listener);
        } catch (...) {
        }
    }
}

void APICALL KfWssSetInterruptListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            srv->setInterruptListener(listener);
        } catch (...) {
        }
    }
}

void APICALL KfWssSetMessageListener(KfWebSocketServer* srv, KfWssMessageListener listener)
{
    if (nullptr != srv) {
        try {
            srv->setMessageListener(listener);
        } catch (...) {
        }
    }
}

// =========== Web Socket Connection

uint8_t APICALL KfWscAreEqual(KfWebSocketConnection* left, KfWebSocketConnection* right)
{
    if (nullptr == left && nullptr == right) {
        return 1;
    }

    if (nullptr == left || nullptr == right) {
        return 0;
    }

    return (*left) == (*right);
}

void APICALL KfWscSend(KfWebSocketConnection* con, const char* payload, uint8_t opcode)
{
    if (nullptr != con) {
        try {
            con->send(payload, (KfWebSocketConnection::OpCode) opcode);
        } catch (...) {
        }
    }
}

void APICALL KfWscClose(KfWebSocketConnection* con)
{
    if (nullptr != con) {
        try {
            con->close();
        } catch (...) {
        }
    }
}

void APICALL KfWscCloseWithStatus(KfWebSocketConnection* con, uint32_t status, const char* reason)
{
    if (nullptr != con) {
        try {
            con->close((KfWebSocketConnection::CloseStatus) status, reason);
        } catch (...) {
        }
    }
}

const char* APICALL KfWscGetRemoteEndpoint(KfWebSocketConnection* con)
{
    if (nullptr != con) {
        try {
            return con->getRemoteEndpoint();
        } catch (...) {
        }
    }
    return "";
}

uint8_t APICALL KfWscGetState(KfWebSocketConnection* con)
{
    if (nullptr == con) {
        return 0;
    }
    return (uint8_t) con->getState();
}

// =========== Web Socket Message

uint8_t APICALL KfWsmIsCompressed(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return 0;
    }
    return msg->isCompressed() ? 1 : 0;
}

uint8_t APICALL KfWsmIsFin(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return 0;
    }
    return msg->isFin() ? 1 : 0;
}

uint8_t APICALL KfWsmIsPrepared(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return 0;
    }
    return msg->isPrepared() ? 1 : 0;
}

const char* APICALL KfWsmGetExtensionData(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return "";
    }
    return msg->getExtensionData();
}

const char* APICALL KfWsmGetHeader(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return "";
    }
    return msg->getHeader();
}

const char* APICALL KfWsmGetPayload(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return "";
    }
    return msg->getPayload();
}

const char* APICALL KfWsmGetRawPayload(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return "";
    }
    return msg->getRawPayload();
}

uint8_t APICALL KfWsmGetOpcode(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return 0;
    }
    return (uint8_t) msg->getOpcode();
}
