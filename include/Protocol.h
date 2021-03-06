//
// Created by Medhopz on 1/17/2017.
//

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H

#include "DATApacket.h"
#include "./../include/MessageEncoderDecoder.h"
#include "./../include/connectionHandler.h"

class Protocol {
private:
    //for data packet
    std::vector<char> dirqArr;
    std::vector<DATApacket*> *sendDataArr;

    std::vector<char> readFileBytes(const char *name);
    bool finishDownload;
    std::string fileDownloadName;
    std:: string fileUploadName;
    int lastPckSent;

    ConnectionHandler* _connectionHandler;
    MessageEncoderDecoder encDec;

public:
    void process(Packet* message);
    void splitFileIntoDataPackets(const char* fileName);
    void printDirq( std::vector<char> dirqArr);
    Protocol(ConnectionHandler* connectionHandler);
    void AckProcess(Packet* message);
    void sendData();
    void sendPacket(Packet* packet);
    ConnectionHandler* getConnectionHandler();
    ~Protocol();
    Protocol& operator=(const Protocol& other);
    Protocol(const Protocol& other);
};

#endif //BOOST_ECHO_CLIENT_PROTOCOL_H