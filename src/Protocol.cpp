#include <vector>
#include "./../include/Protocol.h"
#include "./../include/enums.h"
#include "./../include/Packets/Packet.h"
#include "../include/packets/ERRORpacket.h"
#include "../include/packets/ACKpacket.h"
#include "../include/packets/RRQpacket.h"
#include "../include/packets/WRQpacket.h"
#include "../include/packets/DELRQpacket.h"
#include "../include/packets/BCASTpacket.h"
#include "../include/packets/DATApacket.h"

#include <iostream>
#include <fstream>
#include <math.h>

Protocol::Protocol(concurrent_queue<Packet>* outgoingMessages): sendList(outgoingMessages){}

void Protocol::process(Packet* message) {
    short opCode = message->getOpCode();
    switch(opCode) {
        case enumNamespace::PacketType::ACK:
            if(enumNamespace::g_status == enumNamespace::PacketType::WRQ) {
                if( lastPckSent == ((ACKpacket *) message)->getBlockNumber() ) {
                    if (sendDataArr->size() != 0) {
                        lastPckSent = sendDataArr->back().getBlockNumber();
                        sendList->push(sendDataArr->front());
                        sendDataArr->erase(sendDataArr->begin());
                    } else {
                        std::cout << "WRQ " << fileUploadName << " complete" << std::endl;
                        enumNamespace::g_status = enumNamespace::PacketType::WAITING;
                    }
                }
            } else if(enumNamespace::g_status == enumNamespace::PacketType::DISC) {
                enumNamespace::g_status = enumNamespace::PacketType::WAITING;
                //disconnect(); // do we need to send another ACK or is this ok?
            }
            std::cout << "ACK <" << ((ACKpacket *) message)->getBlockNumber() << ">" << std::endl;
            break;

        case enumNamespace::PacketType::BCAST:
            std::cout << "BCAST <" << ((BCASTpacket*)message)->getDelAdd() <<"><" <<((BCASTpacket*)message)->getFileName() << std::endl;
            break;

        case enumNamespace::PacketType::ERROR:
            std::cout << "ERROR <" << ((ERRORpacket*)message)->getErrCode() << ">" << std::endl;
            break;

        case enumNamespace::PacketType::DATA:
            if(enumNamespace::g_status == enumNamespace::PacketType::RRQ) {
                for (int i = 0; i < ((DATApacket*)message)->getData().size(); ++i) {
                    downloadArr->push_back((char &&) ((DATApacket*)message)->getData().at(i));
                }
                sendList->push( ACKpacket( ((DATApacket*)message)->getBlockNumber()));
                if(((DATApacket*)message)->getData().size() < 512) {
                    enumNamespace::g_status = enumNamespace::PacketType::WAITING;
                    std::cout << "RRQ <" << fileDownloadName << ">" << " complete" << std::endl;
                }

            } else if(enumNamespace::g_status == enumNamespace::PacketType::DIRQ) {
                for (int i = 0; i < ((DATApacket*)message)->getData().size(); ++i) {
                    dirqArr->push_back((char &&) ((DATApacket*)message)->getData().at(i));
                }
                    sendList->push( ACKpacket( ((DATApacket*)message)->getBlockNumber()));
                if(((DATApacket*)message)->getData().size() < 512) { // we can assume we get the packets in the right order
                    finishDownload = true;
                    enumNamespace::g_status = enumNamespace::PacketType::WAITING;
                    //we can add this to the Queue...
                    printDirq(*dirqArr); // not sure if * is right here
                }
            }
            break;

    }



}

void Protocol::printDirq(std::vector<char> arr) {
    for (int i = 0; i < arr.size() ; ++i) {
        if(arr.at(i) != '\0') {
            std::cout << arr.at(i);
        } else {
            std::cout << std::endl;
        }
    }
}


void Protocol::splitFileIntoDataPackets(const char* fileName) {
    std::vector<char> a = readFileBytes(fileName);
    int blkNum = 1;
    std::vector<char> te;
    for (int j = 0; j <a.size() ; ++j) {
        if(te.size() <= 512) {
            te.push_back((char &&) a.at(j));
        } else {
            sendDataArr->push_back(DATApacket(te.size(), blkNum, te));
            te.clear();
            blkNum++;
        }
    }
    sendDataArr->push_back(DATApacket(te.size(), blkNum, te)); // add the last packet with size < 512

}

std::vector<char> Protocol::readFileBytes(char const *filename)
{
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}
