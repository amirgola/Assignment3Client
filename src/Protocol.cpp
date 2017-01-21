#include <vector>
#include "./../include/Protocol.h"
#include "./../include/enums.h"
#include "./../include/packets/Packet.h"
#include "../include/packets/ERRORpacket.h"
#include "../include/packets/ACKpacket.h"
#include "../include/packets/RRQpacket.h"
#include "../include/packets/WRQpacket.h"
#include "../include/packets/DELRQpacket.h"
#include "../include/packets/BCASTpacket.h"
#include "../include/packets/DATApacket.h"
#include "./../include/MessageEncoderDecoder.h"

#include <iostream>
#include <fstream>
#include <math.h>

Protocol::Protocol(ConnectionHandler* connectionHandler): _connectionHandler(connectionHandler){
    encDec = MessageEncoderDecoder();
}

void Protocol::process(Packet* message) {
    short opCode = message->getOpCode();
    std::cout << "op code " << opCode << std::endl;
    switch (opCode) {
        case enumNamespace::PacketType::ACK:
            AckProcess(message);
            std::cout << "ACK " << ((ACKpacket *) message)->getBlockNumber() << std::endl;
            break;
        case enumNamespace::PacketType::BCAST:
            if (((BCASTpacket *) message)->getDelAdd() == 1) {
                std::cout << "BCAST add " << ((BCASTpacket *) message)->getFileName() << std::endl;
            } else {
                std::cout << "BCAST del " << ((BCASTpacket *) message)->getFileName() << std::endl;
            }
            break;
        case enumNamespace::PacketType::ERROR:
            std::cout << "ERROR " << ((ERRORpacket *) message)->getErrCode() << std::endl;
            break;
        case enumNamespace::PacketType::DATA: {
            DATApacket *dataPacket = ((DATApacket *) message);
            if (enumNamespace::g_status == enumNamespace::PacketType::RRQ) {
                std::ofstream incomingFile;
                std::string filePath = "./" + enumNamespace::g_fileNameString;

                if (dataPacket->getBlockNumber() == 1) {
                    incomingFile.open(filePath, std::ios::binary);
                } else {
                    incomingFile.open(filePath, std::ios::app | std::ios::binary);
                }

                if (incomingFile.is_open()) {
                    std::vector<char> dataVector = dataPacket->getData();
                    std::string strData(dataVector.begin(), dataVector.end());

                    incomingFile.write(strData.c_str(), dataPacket->getPacketSize());
                    incomingFile.close();
                } else {
                    std::cout << "File cannot be written" << enumNamespace::g_fileNameString << std::endl;
                    sendPacket(new ERRORpacket(2, "File cannot be written"));
                }

                if (dataPacket->getPacketSize() < 512) {
                    enumNamespace::g_status = enumNamespace::PacketType::WAITING;
                    std::cout << "RRQ " << enumNamespace::g_fileNameString << " complete" << std::endl;
                }

                ACKpacket *acKpacket = new ACKpacket(dataPacket->getBlockNumber());
                sendPacket(acKpacket);
                delete acKpacket;

            } else if (enumNamespace::g_status == enumNamespace::PacketType::DIRQ) {
                dirqArr.clear();
                for (int i = 0; i < dataPacket->getPacketSize(); ++i) {
                    dirqArr.push_back((char &&) dataPacket->getData().at(i));
                }

                if (dataPacket->getPacketSize() < 512) { // we can assume we get the packets in the right order
                    finishDownload = true;
                    enumNamespace::g_status = enumNamespace::PacketType::WAITING;
                    if (dirqArr.size() > 0) {
                        printDirq(dirqArr);
                    }
                }

                ACKpacket *acKpacket = new ACKpacket(dataPacket->getBlockNumber());
                sendPacket(acKpacket);
                delete acKpacket;
                delete dataPacket;
            }
            break;
        }
    }
}

void Protocol::AckProcess(Packet* message) {
    switch (enumNamespace::g_status) {
        case enumNamespace::PacketType::WRQ: {
            // split
            const char *cstr = enumNamespace::g_fileNameString.c_str();
            splitFileIntoDataPackets(cstr);
            // send first
            sendData();
            enumNamespace::g_status = enumNamespace::PacketType::DATA;
            break;
        }
        case enumNamespace::PacketType::DATA: {
            // send next data
            if (lastPckSent == ((ACKpacket *) message)->getBlockNumber()) {
                sendData();
            }
            break;
        }
        case enumNamespace::PacketType::DISC: {
            // close socket
            _connectionHandler->close();
            enumNamespace::g_status = enumNamespace::PacketType::DISCONNECTED;
            break;
        }
        default:
            break;
    }
}

void Protocol::sendData(){
    if (sendDataArr!= nullptr && sendDataArr->size() != 0) {
        lastPckSent = sendDataArr->front()->getBlockNumber();

        // encode the packet
        sendPacket(sendDataArr->front());

        sendDataArr->erase(sendDataArr->begin());
    } else {
        std::cout << "WRQ " << fileUploadName << " complete" << std::endl;
        enumNamespace::g_status = enumNamespace::PacketType::WAITING;
    }
}

void Protocol::sendPacket(Packet* packet){
    std::vector<char> encodedMessage = encDec.encode(packet);
    std::string toSend(encodedMessage.begin(), encodedMessage.end());
    if (!_connectionHandler->sendBytes(toSend.c_str(),toSend.length())) {
        enumNamespace::g_status = enumNamespace::PacketType::DISCONNECTED;
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
    if(sendDataArr == nullptr)
        sendDataArr = new std::vector<DATApacket*>();
    for (int j = 0; j <a.size() ; ++j) {
        if(te.size() < 512) {
            te.push_back((char &&) a.at(j));
        } else {
            sendDataArr->push_back(new DATApacket(te.size(), blkNum, te));
            te.clear();
            te.push_back((char &&) a.at(j));
            blkNum++;
        }
    }
    sendDataArr->push_back(new DATApacket(te.size(), blkNum, te)); // add the last packet with size < 512

}

std::vector<char> Protocol::readFileBytes(char const *filename) {
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

ConnectionHandler* Protocol::getConnectionHandler(){
    return _connectionHandler;
}

Protocol::~Protocol(){
    delete sendDataArr;
    delete _connectionHandler;
}