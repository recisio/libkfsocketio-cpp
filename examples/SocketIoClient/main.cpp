#include <Windows.h>
#include <iostream>

#include "libkfsocketio.h"

#pragma comment (lib, "libkfsocketio.lib")

int main()
{
    volatile bool messageReceived = false;
    IKfSioClient* client = KfSioClientFactory();

    client->setReconnectDelayMax(1000);

    client->on("chat message", [&messageReceived](const std::string& name, const KfSioMessagePtr& message, bool, KfSioMessageList&) {
        if (message->isString()) {
            std::string msg = message->getString();
            std::cout << msg << std::endl;
            if ("exit" == msg) {
                messageReceived = true;
            }
        } 
    });

    // You can deploy a socketio char example test server on heroku from https://github.com/socketio/chat-example
    client->connect("https://your-socketio-chat-server.srv");

    while (!messageReceived) {
        Sleep(200);
    }

    delete client;

    return 0;
}
