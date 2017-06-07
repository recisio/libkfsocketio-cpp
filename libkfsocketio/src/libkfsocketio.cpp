#include "libkfsocketio.h"

#include "KfSioClient.h"
#include "KfWebSocketServer.h"
#include "KfSioMessage.h"
#include "KfWebSocketMessage.h"

// Socket.IO Client

KfSioClient* APICALL KfSioCreate()
{
    KfSioClient* client = new KfSioClient();
    return client;
}

void APICALL KfSioDispose(KfSioClient* client)
{
    if (nullptr != client) {
        delete client;
    }
}

void APICALL KfSioConnect(
    KfSioClient* client,
    const char* uri,
    KfSioClientConnectQueryParam* query,
    unsigned int queryCount,
    KfSioClientConnectQueryParam* httpExtraHeaders,
    unsigned int httpExtraHeadersCount)
{
    if (nullptr != client) {
        try {
            client->connect(uri, (KfSioClientQueryParam*) query, queryCount, (KfSioClientQueryParam*) httpExtraHeaders, httpExtraHeadersCount);
        } catch (...) {}
    }
}

void APICALL KfSioEmit(
    KfSioClient* client,
    const char* name,
    const char* message,
    KfSioAckListener ack,
    const char* socketNs)
{
    if (nullptr != client) {
        try {
            if (nullptr != ack) {
                client->emit(name, message, nullptr, socketNs);
            } else {
                client->emit(name, message, [ack](KfSioMessageList msgList) {
                    (ack) ((KfSioMsgList) msgList);
                }, socketNs);
            }
        } catch (...) {}
    }
}

void APICALL KfSioClose(KfSioClient* client)
{
    if (nullptr != client) {
        try {
            client->close();
        } catch (...) {}
    }
}

void APICALL KfSioSyncClose(KfSioClient* client)
{
    if (nullptr != client) {
        try {
            client->syncClose();
        } catch (...) {}
    }
}

KfBool APICALL KfSioIsOpen(KfSioClient* client)
{
    if (nullptr == client) {
        return (KfBool) false;
    }
    try {
        return (KfBool) client->isOpen();
    } catch (...) {
        return (KfBool) false;
    }
}

const char* APICALL KfSioGetSessionId(KfSioClient* client)
{
    if (nullptr == client) {
        return "";
    }

    try {
        return client->getSessionId();
    } catch (...) {
        return "";
    }
}

void APICALL KfSioClearListeners(KfSioClient* client)
{
    if (nullptr != client) {
        try {
            client->clearListeners();
        } catch (...) {}
    }
}

void APICALL KfSioSetClientOpenListener(KfSioClient* client, KfSioConnectionListener listener)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->setClientOpenListener(nullptr);
            } else {
                client->setClientOpenListener([listener]() {
                    (listener) ();
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioSetClientCloseListener(KfSioClient* client, KfSioCloseListener listener)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->setClientCloseListener(nullptr);
            } else {
                client->setClientCloseListener([listener](const unsigned int& reason) {
                    (listener) (reason);
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioSetClientFailListener(KfSioClient* client, KfSioConnectionListener listener)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->setClientFailListener(nullptr);
            } else {
                client->setClientFailListener([listener]() {
                    (listener) ();
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioSetClientReconnectingListener(KfSioClient* client, KfSioConnectionListener listener)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->setClientReconnectingListener(nullptr);
            } else {
                client->setClientReconnectingListener([listener]() {
                    (listener) ();
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioSetClientReconnectListener(KfSioClient* client, KfSioReconnectListener listener)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->setClientReconnectListener(nullptr);
            } else {
                client->setClientReconnectListener([listener](unsigned int nAttempts, unsigned int delay) {
                    (listener) (nAttempts, delay);
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioSetSocketOpenListener(KfSioClient* client, KfSioSocketListener listener)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->setSocketOpenListener(nullptr);
            } else {
                client->setSocketOpenListener([listener](const char* nsp) {
                    (listener) (nsp);
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioSetSocketCloseListener(KfSioClient* client, KfSioSocketListener listener)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->setSocketCloseListener(nullptr);
            } else {
                client->setSocketCloseListener([listener](const char* nsp) {
                    (listener) (nsp);
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioSetReconnectAttempts(KfSioClient* client, int attempts)
{
    if (nullptr != client) {
        try {
            client->setReconnectAttempts(attempts);
        } catch (...) {}
    }
}

void APICALL KfSioSetReconnectDelay(KfSioClient* client, unsigned int millis)
{
    if (nullptr != client) {
        try {
            client->setReconnectDelay(millis);
        } catch (...) {}
    }
}

void APICALL KfSioSetReconnectDelayMax(KfSioClient* client, unsigned int millis)
{
    if (nullptr != client) {
        try {
            client->setReconnectDelayMax(millis);
        } catch (...) {}
    }
}

void APICALL KfSioOn(KfSioClient* client, const char* eventName, KfSioEventListener eventListener, const char* socketNs)
{
    if (nullptr != client) {
        try {
            if (nullptr == eventListener) {
                client->on(eventName, nullptr, socketNs);
            } else {
                client->on(
                    eventName,
                    [eventListener](const char* name, KfSioMessagePtr message, bool needAck, KfSioMessageList ackMsg) {
                    (eventListener) (name, message, needAck, (KfSioMsgList) ackMsg);
                },
                    socketNs);
            }
        } catch (...) {}
    }
}

void APICALL KfSioOff(KfSioClient* client, const char* eventName, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->off(eventName, socketNs);
        } catch (...) {}
    }
}

void APICALL KfSioOffAll(KfSioClient* client, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->offAll(socketNs);
        } catch (...) {}
    }
}

void APICALL KfSioCloseSocket(KfSioClient* client, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->closeSocket(socketNs);
        } catch (...) {}
    }
}

void APICALL KfSioOnError(KfSioClient* client, KfSioErrorListener listener, const char* socketNs)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->onError(nullptr, socketNs);
            } else {
                client->onError([listener](KfSioMessagePtr message) {
                    (listener) (message);
                });
            }
        } catch (...) {}
    }
}

void APICALL KfSioOffError(KfSioClient* client, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->offError(socketNs);
        } catch (...) {}
    }
}

// =========== Socket.Io Message

int APICALL KfSioMsgGetType(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return KFSIOMSG_NULL;
    }
    return (KfBool) msg->getMessageType();
}

KfBool APICALL KfSioMsgIsInt(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }
    return (KfBool) msg->isInt();
}

KfBool APICALL KfSioMsgIsDouble(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }
    return (KfBool) msg->isDouble();
}

KfBool APICALL KfSioMsgIsString(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }
    return (KfBool) msg->isString();
}

KfBool APICALL KfSioMsgIsBinary(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }

    return (KfBool) msg->isBinary();
}

KfBool APICALL KfSioMsgIsArray(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }
    return (KfBool) msg->isArray();
}

KfBool APICALL KfSioMsgIsObject(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }
    return (KfBool) msg->isObject();
}

KfBool APICALL KfSioMsgIsBool(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }
    return (KfBool) msg->isBool();
}

KfBool APICALL KfSioMsgIsNull(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) true;
    }
    return (KfBool) msg->isNull();
}

int APICALL KfSioMsgGetInt(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return -1;
    }
    try {
        return msg->getInt();
    } catch (...) {
        return -1;
    }
}

double APICALL KfSioMsgGetDouble(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return -1.0;
    }
    try {
        return msg->getDouble();
    } catch (...) {
        return -1.0;
    }
}

const char* APICALL KfSioMsgGetString(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return "";
    }
    try {
        return msg->getString();
    } catch (...) {
        return "";
    }
}

KfSioMsgList APICALL KfSioMsgGetArray(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return nullptr;
    }
    try {
        return (KfSioMsgList) msg->getArray();
    } catch (...) {
        return nullptr;
    }
}

KfBool APICALL KfSioMsgGetBool(KfSioMessage* msg)
{
    if (nullptr == msg) {
        return (KfBool) false;
    }
    try {
        return (KfBool) msg->getBool();
    } catch (...) {
        return false;
    }
}

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
