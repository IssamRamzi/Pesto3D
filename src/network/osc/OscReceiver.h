#pragma once

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#include <iostream>
#include <cstring>
#include <thread>

#define PORT 7000

class OscListener : public osc::OscPacketListener
{
public:
    void startListening(int port);
protected:
    virtual void ProcessMessage(const osc::ReceivedMessage &m, const IpEndpointName &remoteEndpoint) override;
};