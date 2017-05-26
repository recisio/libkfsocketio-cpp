#include "KfWebSocketServer.h"

#include "KfWebSocketServerHandler.h"

KfWebSocketServer::KfWebSocketServer() :
    m_handler(new KfWebSocketServerHandler())
{

}

KfWebSocketServer::~KfWebSocketServer()
{
    delete m_handler;
}