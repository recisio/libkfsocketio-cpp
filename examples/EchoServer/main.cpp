#include <string>
#include <iostream>
#include <Windows.h>

#include "libkfsocketio.h"

#pragma comment (lib, "libkfsocketio.lib")

KfWebSocketServer* server = nullptr;

void OnWssOpen(KfWebSocketConnection* con)
{
    std::cout << "New connection!" << std::endl;
    KfWscSend(con, "Welcome to the KfWebSocket echo server test!", KFWSC_OPCODE_TEXT);
}

void OnWssClose(KfWebSocketConnection*)
{
    std::cout << "Connection lost" << std::endl;
}

void OnWssMessage(KfWebSocketConnection* con, KfWebSocketMessage* msg)
{
    std::string message(KfWsmGetPayload(msg));
    std::cout << message << std::endl;

    KfWscSend(con, message.c_str(), KfWsmGetOpcode(msg));

    if ("exit" == message && nullptr != server) {
        KfWssStop(server);
    }
}

int main()
{
    server = KfWssCreate();

    KfWssSetOpenListener(server, OnWssOpen);
    KfWssSetMessageListener(server, OnWssMessage);
    KfWssSetCloseListener(server, OnWssClose);

    KfWssRun(server, 9191);

    KfWssDispose(server);

    return 0;
}
