#include <iostream>
#include <Windows.h>

#include "libkfsocketio.h"

#pragma comment (lib, "libkfsocketio.lib")

int main()
{
    IKfWebSocketServer* server = KfWebSocketServerFactory();

    server->setOpenListener([](IKfWebSocketConnection& con) {
        std::cout << "New connection!" << std::endl;
        con.send("Welcome to the KfWebSocket echo server test!", IKfWebSocketConnection::OpCode::OPCODE_TEXT);
    });

    server->setMessageListener([](IKfWebSocketConnection& con, IKfWebSocketMessage& message) {
        std::cout << message.getPayload() << std::endl;
        con.send(message.getPayload(), message.getOpcode());
    });

    server->setCloseListener([](IKfWebSocketConnection& con) {
        std::cout << "Connection lost" << std::endl;
    });

    try {
        server->run(9191);
    } catch (...) {
    }

    delete server;

    return 0;
}
