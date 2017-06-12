#include <Windows.h>
#include <string>
#include <iostream>

#include "libkfsocketio.h"

#pragma comment (lib, "libkfsocketio.lib")

KfSioClient* client = nullptr;
bool exitApp = false;

void KF_CALLCONV OnSioClientOpen()
{
    std::cout << "Client opened!\n";
}

void KF_CALLCONV OnSioClientClose(unsigned int reason)
{
    std::cout << "Client closed!\n";

}

void KF_CALLCONV OnSioClientFail()
{
    std::cout << "Client failed!\n";
}

void KF_CALLCONV OnSioMessage(const char* name, KfSioMessage* message, bool needAck, KfSioMsgList ackMessage)
{
    std::cout << name << std::endl;
    std::string msgStr(KfSioMsgGetString(message));
    std::cout << msgStr << std::endl;

    if ("exit" == msgStr) {
        exitApp = true;
    }
}

int main()
{
    volatile bool messageReceived = false;

    client = KfSioCreate();

    KfSioSetClientOpenListener(client, OnSioClientOpen);
    KfSioSetClientCloseListener(client, OnSioClientClose);
    KfSioSetClientFailListener(client, OnSioClientFail);

    // You can deploy a socketio char example test server on heroku from https://github.com/socketio/chat-example
    KfSioConnect(client, "http://www.my-sio-server.srv");
    KfSioOn(client, "chat message", OnSioMessage);

    while (!exitApp) {
        Sleep(100);
    }

    return 0;
}
