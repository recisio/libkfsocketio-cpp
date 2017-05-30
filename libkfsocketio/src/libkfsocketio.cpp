#include "libkfsocketio.h"

#include "KfSioClient.h"
#include "KfWebSocketServer.h"
#include "KfSioMessage.h"

IKfSioClient* __stdcall KfSioClientFactory()
{
    return new KfSioClient();
}

IKfWebSocketServer* __stdcall KfWebSocketServerFactory()
{
    return new KfWebSocketServer();
}

IKfSioMessage* __stdcall KfSioMessageFactory()
{
    return new KfSioMessage();
}
