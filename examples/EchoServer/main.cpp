#include <iostream>
#include <Windows.h>

#include "KfWebSocketServer.h"

#pragma comment (lib, "libkfsocketio.lib")

int main()
{
    KfWebSocketServer server;

    server.setOpenListener([](const KfWebSocketConnection& co) {
        std::cout << "New connection!" << std::endl;
    });

    server.setMessageListener([](const KfWebSocketConnection& con) {
        std::cout << "New message !" << std::endl;
    });

    server.setCloseListener([](const KfWebSocketConnection& con) {
        std::cout << "Connection closed!" << std::endl;
    });

    server.run(9191);
    return 0;
}
