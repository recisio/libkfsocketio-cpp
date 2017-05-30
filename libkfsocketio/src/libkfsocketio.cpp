#include "libkfsocketio.h"

#include "KfSioClient.h"
#include "KfWebSocketServer.h"

IKfSioClient* __stdcall KfSioClientFactory()
{
    return new KfSioClient();
}

IKfWebSocketServer* __stdcall KfWebSocketServerFactory()
{
    return new KfWebSocketServer();
}