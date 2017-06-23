#include "libkfsocketio.h"

#include "KfSioClient.h"
#include "KfWebSocketServer.h"
#include "KfSioMessage.h"
#include "KfWebSocketMessage.h"

// General 

static uint32_t createKfString(const std::string& str, char** dest)
{
    uint32_t strSize = (uint32_t) str.size();

    (*dest) = new char[strSize + 1];
    memset(*dest, 0, strSize + 1);
    memcpy(*dest, str.c_str(), strSize);

    return strSize;
}

void APICALL KfReleaseString(char* str)
{
    if (nullptr != str) {
        delete[] str;
    }
}

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
            client->connect(std::string(uri), (KfSioClientQueryParam*) query, queryCount, (KfSioClientQueryParam*) httpExtraHeaders, httpExtraHeadersCount);
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
            if (nullptr == ack) {
                client->emit(std::string(name), std::string(message), nullptr, std::string(socketNs));
            } else {
                client->emit(std::string(name), std::string(message), [ack](KfSioMessageList msgList) {
                    (ack) ((KfSioMsgList) msgList);
                }, std::string(socketNs));
            }
        } catch (...) {}
    }
}


LIBKFSOCKETIO_ABSTRACT_DLL void APICALL KfSioEmitJson(
    KfSioClient* client,
    const char* name,
    const char* message,
    KfSioAckListener ack,
    const char* socketNs)
{
    if (nullptr != client) {
        try {
            if (nullptr == ack) {
                client->emitJson(std::string(name), std::string(message), nullptr, std::string(socketNs));
            } else {
                client->emitJson(std::string(name), std::string(message), [ack](KfSioMessageList msgList) {
                    (ack) ((KfSioMsgList) msgList);
                }, std::string(socketNs));
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

uint32_t APICALL KfSioGetSessionId(KfSioClient* client, char** str)
{
    if (nullptr == client) {
        return 0;
    }

    try {
        return createKfString(client->getSessionId(), str);
    } catch (...) {
        return 0;
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
                client->setClientCloseListener([listener](const sio::client::close_reason& reason) {
                    (listener) ((unsigned int) reason);
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
                client->setSocketOpenListener([listener](const std::string& nsp) {
                    (listener) (nsp.c_str());
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
                client->setSocketCloseListener([listener](const std::string& nsp) {
                    (listener) (nsp.c_str());
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
                client->on(std::string(eventName), nullptr, std::string(socketNs));
            } else {
                client->on(
                    std::string(eventName),
                    [eventListener](const char* name, KfSioMessagePtr message, bool needAck, KfSioMessageList ackMsg) {
                    (eventListener) (name, message, needAck, (KfSioMsgList) ackMsg);
                },
                    std::string(socketNs));
            }
        } catch (...) {}
    }
}

void APICALL KfSioOff(KfSioClient* client, const char* eventName, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->off(std::string(eventName), std::string(socketNs));
        } catch (...) {}
    }
}

void APICALL KfSioOffAll(KfSioClient* client, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->offAll(std::string(socketNs));
        } catch (...) {}
    }
}

void APICALL KfSioCloseSocket(KfSioClient* client, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->closeSocket(std::string(socketNs));
        } catch (...) {}
    }
}

void APICALL KfSioOnError(KfSioClient* client, KfSioErrorListener listener, const char* socketNs)
{
    if (nullptr != client) {
        try {
            if (nullptr == listener) {
                client->onError(nullptr, std::string(socketNs));
            } else {
                client->onError([listener](KfSioMessagePtr message) {
                    (listener) (message);
                }, std::string(socketNs));
            }
        } catch (...) {}
    }
}

void APICALL KfSioOffError(KfSioClient* client, const char* socketNs)
{
    if (nullptr != client) {
        try {
            client->offError(std::string(socketNs));
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

uint32_t APICALL KfSioMsgGetString(KfSioMessage* msg, char** str)
{
    if (nullptr == msg) {
        return 0;
    }

    try {
        return createKfString(msg->getString(), str);
    } catch (...) {
        return 0;
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
            if (nullptr == listener) {
                srv->setOpenListener(nullptr);
            } else {
                srv->setOpenListener([listener](KfWebSocketConnectionPtr con) {
                    if (nullptr != listener) {
                        (listener) (con);
                    }
                });
            }
        } catch (...) {
        }
    }
}

void APICALL KfWssSetCloseListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            if (nullptr == listener) {
                srv->setCloseListener(nullptr);
            } else {
                srv->setCloseListener([listener](KfWebSocketConnectionPtr con) {
                    if (nullptr != listener) {
                        (listener) (con);
                    }
                });
            }
        } catch (...) {
        }
    }
}

void APICALL KfWssSetFailListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            if (nullptr == listener) {
                srv->setFailListener(nullptr);
            } else {
                srv->setFailListener([listener](KfWebSocketConnectionPtr con) {
                    if (nullptr != listener) {
                        (listener) (con);
                    }
                });
            }
        } catch (...) {
        }
    }
}

void APICALL KfWssSetHttpListener(KfWebSocketServer* srv, KfWssConnectionListener listener)
{
    if (nullptr != srv) {
        try {
            if (nullptr == listener) {
                srv->setHttpListener(nullptr);
            } else {
                srv->setHttpListener([listener](KfWebSocketConnectionPtr con) {
                    if (nullptr != listener) {
                        (listener) (con);
                    }
                });
            }
        } catch (...) {
        }
    }
}

void APICALL KfWssSetMessageListener(KfWebSocketServer* srv, KfWssMessageListener listener)
{
    if (nullptr != srv) {
        try {
            if (nullptr == listener) {
                srv->setMessageListener(nullptr);
            } else {
                srv->setMessageListener([listener](KfWebSocketConnectionPtr con, KfWebSocketMessagePtr msg) {
                    if (nullptr != listener) {
                        (listener) (con, msg);
                    }
                });
            }
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

uint32_t APICALL KfWsmGetExtensionData(KfWebSocketMessage* msg, char** str)
{
    if (nullptr == msg) {
        return 0;
    }

    return createKfString(msg->getExtensionData(), str);
}

uint32_t APICALL KfWsmGetHeader(KfWebSocketMessage* msg, char** str)
{
    if (nullptr == msg) {
        return 0;
    }

    return createKfString(msg->getHeader(), str);
}

uint32_t APICALL KfWsmGetPayload(KfWebSocketMessage* msg, char** str)
{
    if (nullptr == msg) {
        return 0;
    }
    return createKfString(msg->getPayload(), str);
}

uint32_t APICALL KfWsmGetRawPayload(KfWebSocketMessage* msg, char** str)
{
    if (nullptr == msg) {
        return 0;
    }
    return createKfString(msg->getRawPayload(), str);
}

uint8_t APICALL KfWsmGetOpcode(KfWebSocketMessage* msg)
{
    if (nullptr == msg) {
        return 0;
    }
    return (uint8_t) msg->getOpcode();
}
