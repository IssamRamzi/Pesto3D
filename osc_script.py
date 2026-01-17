from pythonosc import udp_client
import time
import random

ip = "127.0.0.1"
port = 7000
client = udp_client.SimpleUDPClient(ip, port)

print(f"Sending test messages to {ip}:{port} on address /test1")

try:
    while True:

        arg1 = True                  #bool
        arg2 = random.randint(0, 100) #int32
        arg3 = 3.333333               #float
        arg4 = "nibnibnibnibnib"         #string
        client.send_message("/test1", [arg1, arg2, arg3, arg4])
        print(f"Sent: [ {arg1}, {arg2}, {arg3}, \"{arg4}\" ]")
        time.sleep(1.0) 

except KeyboardInterrupt:
    print("\nStopped.")
