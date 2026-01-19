#pragma once

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <atomic>

#define PORT 3333

class OscListener : public osc::OscPacketListener
{
public:
    std::atomic<float> _attractorX{0.0f};
    std::atomic<float> _attractorY{0.0f};
    std::atomic<float> _attractorZ{0.0f};
    std::atomic<float> _radius{0.0f};
    std::atomic<float> _force{0.0f};

    void startListening(int port);

protected:
    virtual void ProcessMessage(const osc::ReceivedMessage &m, const IpEndpointName &remoteEndpoint) override;
};
