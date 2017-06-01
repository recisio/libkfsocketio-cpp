#include "libkfsocketio.h"

#include "KfSioClient.h"
#include "KfWebSocketServer.h"
#include "KfSioMessage.h"

IKfSioClient* APICALL KfSioClientFactory()
{
    return new KfSioClient();
}

IKfWebSocketServer* APICALL KfWebSocketServerFactory()
{
    return new KfWebSocketServer();
}

IKfSioMessage* APICALL KfSioMessageFactory()
{
    return new KfSioMessage();
}

void APICALL KfSioClientDispose(IKfSioClient* client)
{
    delete (KfSioClient*) client;
}

void APICALL KfWebSocketServerDispose(IKfWebSocketServer* server)
{
    delete (KfWebSocketServer*) server;
}

void APICALL KfSioMessageDispose(IKfSioMessage* message)
{
    delete (KfSioMessage*) message;
}
