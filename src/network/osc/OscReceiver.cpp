#include "OscReceiver.h"

void OscListener::startListening(int port)
{
    //need to add try catch for error later but flemme now
    std::thread([this, port]() {
        UdpListeningReceiveSocket oscSocket(
            IpEndpointName(IpEndpointName::ANY_ADDRESS, port),
            this
        );
        std::cout << "OSC listening on port :" << port << std::endl;
        oscSocket.Run();
    }).detach();
}


void OscListener::ProcessMessage(const osc::ReceivedMessage &m, const IpEndpointName &remoteEndpoint)
{
    (void)remoteEndpoint;
    try {
        if (std::strcmp(m.AddressPattern(), "/test1") == 0) {
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            bool a1;
            osc::int32 a2;
            float a3;
            const char *a4;
            args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;
            std::cout << "Received message test/1 with arguments :"
            << a1 << " " << a2 << " " << a3 << " " << a4 << std::endl;
        }
    } catch (osc::Exception& e) {
        std::cout << "error while parsing message:"
        << m.AddressPattern() << ": " << e.what() << std::endl;
    }
}
