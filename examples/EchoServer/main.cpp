#include <iostream>
#include <Windows.h>

#include "KfWebSocketServer.h"

#pragma comment (lib, "libkfsocketio.lib")

int main()
{
    KfWebSocketServer server;

    server.setOpenListener([](KfWebSocketConnection& con) {
        std::cout << "New connection!" << std::endl;
        con.send("Welcome to the KfWebSocket echo server test!", KfWebSocketConnection::OpCode::OPCODE_TEXT);
    });

    server.setMessageListener([](KfWebSocketConnection& con, KfWebSocketMessage& message) {
        std::cout << message.getPayload() << std::endl;
        con.send(message.getPayload(), message.getOpcode());
    });

    server.setCloseListener([](KfWebSocketConnection& con) {
        std::cout << "Connection lost" << std::endl;
    });

    server.run(9191);
    return 0;
}
