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
    osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
    try {
        if (std::strcmp(m.AddressPattern(), "/attractor/pos") == 0) {
            float x;
            float y;
            float z;
            args >> x >> y >> z >> osc::EndMessage;
            _attractorX = x;
            _attractorY = y;
            _attractorZ = z; //-> for now this does nothing since depth is a bitch to implement in mediapipe

            std::cout << "Received message test/1 with arguments :"
            << x << " " << y << " " << z << " "<< std::endl;
        } else if (std::strcmp(m.AddressPattern(), "/attractor/radius") == 0) {
            float radius;
            args >> radius >> osc::EndMessage;
            _radius = radius;
        }else if (std::strcmp(m.AddressPattern(), "/note") == 0) {
            float note;
            float confidence;
            float volume;
            int channel;
            args >> note >> confidence >> volume >> channel >> osc::EndMessage;
            _force = volume;

            std::cout << "Received message note:" << note << " confidence:"
                      << confidence << " volume:" << volume
                      << " channel:" << channel << std::endl;
        }
    } catch (osc::Exception& e) {
        std::cout << "error while parsing message:"
        << m.AddressPattern() << ": " << e.what() << std::endl;
    }
}
