//
// Created by Medhopz on 1/17/2017.
//

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H

#include "./packets/DATApacket.h"
#include "./../include/concurrent_queue.h"

class Protocol {
private:
    //for data packet
    short pckSize;
    short blkNum;
    std::vector<char> *downloadArr;
    std::vector<char> *dirqArr;
    std::vector<DATApacket> *sendDataArr;

    std::vector<char> readFileBytes(const char *name);
    bool finishDownload;
    std::string fileDownloadName;
    std:: string fileUploadName;
    int lastPckSent;
    concurrent_queue<Packet>* sendList;

public:
    Protocol(concurrent_queue<Packet>* outgoingMessages);
    void process(Packet* message);
    void splitFileIntoDataPackets(const char* fileName);

    void printDirq( std::vector<char> dirqArr);
    ~Protocol();
};

#endif //BOOST_ECHO_CLIENT_PROTOCOL_H