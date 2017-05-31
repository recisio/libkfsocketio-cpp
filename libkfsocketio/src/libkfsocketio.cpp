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
    _crt_signal_t c;
    return new KfSioMessage();
}
