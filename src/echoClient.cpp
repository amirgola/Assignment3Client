#include <stdlib.h>
#include "./../include/connectionHandler.h"
#include <iostream>
#include "../include/packets/Packet.h"
#include "./../include/KeyboardTask.h"
#include "./../include/SocketTask.h"
#include "./../include/enums.h"

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
enumNamespace::PacketType enumNamespace::g_status;
std::string enumNamespace::g_fileNameString;

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    Protocol protocol(&connectionHandler);
    int pendingAcks = 0;
    boost::mutex mutex;

    KeyboardTask keyboardTask(&pendingAcks, &mutex, &protocol);
    SocketTask socketTask(&pendingAcks, &mutex, &protocol);

    boost::thread th1(keyboardTask);
    boost::thread th2(socketTask);

    // maybe we need something else?
    th1.join();
    th2.join();

    return 0;
}
