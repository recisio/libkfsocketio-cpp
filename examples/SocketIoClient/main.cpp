#include <Windows.h>
#include <iostream>
#include "KfSioClient.h"

#pragma comment (lib, "libkfsocketio.lib")

int main()
{
    volatile bool messageReceived = false;
    KfSioClient client;
    
    client.setReconnectDelayMax(1000);
    
    client.on("chat message", [&messageReceived](const std::string& name, const KfSioMessage& message, bool, KfSioMessageList&) {
        if (message.isString()) {
            std::string msg = message.getString();
            if ("exit" == msg) {
                messageReceived = true;
            }
        }
    });

    client.setClientOpenListener([&client]() {
        client.emit("chat message", KfSioMessageList({"Hello !"}));
    });

    client.connect("https://calm-hollows-71137.herokuapp.com");


    while (!messageReceived) {
        Sleep(200);
    }

    Sleep(1000);

    return 0;
}
