#include <vector>
#include "./../include/MessageEncoderDecoder.h"
#include "./../include/enums.h"
#include "../include/RRQpacket.h"
#include "../include/WRQpacket.h"
#include "../include/DATApacket.h"
#include "../include/ACKpacket.h"
#include "../include/ERRORpacket.h"
#include "../include/DISCpacket.h"
#include "../include/BCASTpacket.h"
#include "../include/DELRQpacket.h"
#include "../include/LOGRQpacket.h"
#include "../include/DIRQpacket.h"
#include "../include/Packet.h"

MessageEncoderDecoder::MessageEncoderDecoder():opCode(0),strBuffer(""),buffer(), pckSize(0), blkNum(-1), dataArr(), errCode(-1){

}

Packet* MessageEncoderDecoder::decodeNextByte(char nextByte) {
    // if we have two bytes - then we can decode the rest of the message
    if (opCode != 0) {
        switch (opCode) {
            case enumNamespace::PacketType::RRQ : {
                if (nextByte != '\0') {
                    buffer.push_back(nextByte);
                } else {
                    strBuffer = std::string(buffer.begin(), buffer.end());
                    resetBuffer();
                    return new RRQpacket(strBuffer);
                }
                break;
            }
            case enumNamespace::PacketType::WRQ: {
                if (nextByte != '\0') {
                    buffer.push_back(nextByte);
                } else {
                    strBuffer = std::string(buffer.begin(), buffer.end());
                    resetBuffer();
                    return new WRQpacket(strBuffer);
                }
                break;
            }
            case enumNamespace::PacketType::DATA: {
                if (buffer.size() < 4) { // 0,1,2,3 position get filled in buffer
                    buffer.push_back(nextByte);
                    if (buffer.size() == 2) {
                        pckSize = bytesToShort(reinterpret_cast<char *>(buffer.data()));
                        dataArr = new std::vector<char>();
                    }
                    if (buffer.size() == 4) {
                        std::vector<char> newVector(buffer.begin() + 2, buffer.end());
                        blkNum = bytesToShort(reinterpret_cast<char *>(newVector.data()));
                    }
                } else {
                    dataArr->push_back(nextByte);
                }
                if (buffer.size() >= 4 && dataArr->size() == pckSize) {
                    resetBuffer();
                    return new DATApacket(pckSize, blkNum, *dataArr);
                }
                break;
            }
            case enumNamespace::PacketType::ACK: {
                buffer.push_back(nextByte);
                if (buffer.size() >= 2) {
                    std::vector<char> newVector(buffer);
                    resetBuffer();
                    return new ACKpacket(bytesToShort(reinterpret_cast<char *>(newVector.data())));
                }
                break;
            }
            case enumNamespace::PacketType::ERROR: {
                if (buffer.size() < 2 || nextByte != '\0')
                    buffer.push_back(nextByte);
                else {
                    short errorCode = errCode;
                    resetBuffer();
                    return new ERRORpacket(errorCode, "");
                }

                if (buffer.size() == 2) {
                    errCode = bytesToShort(reinterpret_cast<char *>(buffer.data()));
                }

                break;
            }
            case enumNamespace::PacketType::DIRQ: {
                resetBuffer();
                return new DIRQpacket();
            }
            case enumNamespace::PacketType::LOGRQ: {
                if (nextByte != '\0') {
                    buffer.push_back(nextByte);
                } else {
                    strBuffer = std::string(buffer.begin(), buffer.end());
                    resetBuffer();
                    return new LOGRQpacket(strBuffer);
                }
                break;
            }
            case enumNamespace::PacketType::DELRQ: {
                if (nextByte != '\0') {
                    buffer.push_back(nextByte);
                } else {
                    strBuffer = std::string(buffer.begin(), buffer.end());
                    resetBuffer();
                    return new DELRQpacket(strBuffer);
                }
                break;
            }
            case enumNamespace::PacketType::BCAST: {
                if (buffer.size() == 0 || nextByte != '\0')
                    buffer.push_back(nextByte);
                else {
                    char delAdd = buffer.at(0);
                    strBuffer = std::string(buffer.begin() + 1, buffer.end());
                    resetBuffer();
                    return new BCASTpacket(delAdd, strBuffer);
                }

                break;
            }
            case enumNamespace::PacketType::DISC: {
                resetBuffer();
                return new DISCpacket();
            }
            case enumNamespace::PacketType::UNKNOWN:
            default: {
                resetBuffer();
                return new ERRORpacket(4, "unknown OP code");
            }
        }
    }

    return nullptr;
}

short MessageEncoderDecoder::decodePacketType(char bytes[]){
    //&a[0]
    opCode = bytesToShort(&bytes[0]);
    return opCode;
}

std::vector<char> MessageEncoderDecoder::encode(Packet* message) {
    char opCodeArray[2];
    char blkNumArray[2];
    std::vector<char> temp;
    std::vector<char> res;
    opCode = message->getOpCode();

    switch(opCode) {
        case enumNamespace::PacketType::DATA: {

            res.clear();
            char pctSizeArray[2];
            shortToBytes(message->getOpCode(), opCodeArray);
            DATApacket *packet = (DATApacket *) message;
            shortToBytes(packet->getPacketSize(), pctSizeArray);
            shortToBytes(packet->getBlockNumber(), blkNumArray);
            temp.clear();
            temp = packet->getData();
            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);
            res.push_back(pctSizeArray[0]);
            res.push_back(pctSizeArray[1]);
            res.push_back(blkNumArray[0]);
            res.push_back(blkNumArray[1]);

            for (int i = 0; i < temp.size(); i++) {
                res.push_back(temp[i]);
            }

            return res;
        }
        case enumNamespace::PacketType::LOGRQ: {
            res.clear();
            LOGRQpacket *logPacket = (LOGRQpacket *) message;
            shortToBytes(opCode, opCodeArray);
            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);
            for(char& c : logPacket->getUserName()) {
                res.push_back(c);
            }

            res.push_back(0);
            return res;
        }
        case enumNamespace::PacketType::ACK: {
            shortToBytes(((ACKpacket *) message)->getBlockNumber(), blkNumArray);
            shortToBytes(message->getOpCode(), opCodeArray);
            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);
            res.push_back(blkNumArray[0]);
            res.push_back(blkNumArray[1]);
            return res;
        }
        case enumNamespace::PacketType::RRQ: {
            shortToBytes(message->getOpCode(), opCodeArray);
            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);
            for(char& c : ((RRQpacket *) message)->getFileName()) {
                res.push_back(c);
            }

            res.push_back(0);

            return res;
        }
        case enumNamespace::PacketType::WRQ: {

            shortToBytes(message->getOpCode(), opCodeArray);
            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);

            for(char& c : ((WRQpacket *) message)->getFileName()) {
                res.push_back(c);
            }

            res.push_back(0);

            return res;
        }
        case enumNamespace::PacketType::DIRQ: {
            shortToBytes(message->getOpCode(), opCodeArray);
            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);

            return res;
        }
        case enumNamespace::PacketType::DELRQ: {
            shortToBytes(message->getOpCode(), opCodeArray);

            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);

            for(char& c : ((DELRQpacket *) message)->getFileName()) {
                res.push_back(c);
            }
            res.push_back(0);
            return res;
        }
        case enumNamespace::PacketType::DISC: {
            shortToBytes(message->getOpCode(), opCodeArray);
            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);
            return res;
        }
        default: {
            res.clear();
            return res;
        }
    }
}

void MessageEncoderDecoder::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

short MessageEncoderDecoder::bytesToShort(char* bytesArr){
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

void MessageEncoderDecoder::resetBuffer(){
    buffer.clear();
    errCode = 0;
}

MessageEncoderDecoder::~MessageEncoderDecoder(){
    delete dataArr;
}

MessageEncoderDecoder& MessageEncoderDecoder::operator=(const MessageEncoderDecoder& other){
    if(this!= &other){
        delete dataArr;

        opCode = other.opCode;
        strBuffer = other.strBuffer;
        buffer = other.buffer;
        pckSize = other.pckSize;
        blkNum = other.blkNum;
        dataArr = other.dataArr;
        errCode = other.errCode;
    }
    return *this;
}

MessageEncoderDecoder::MessageEncoderDecoder(const MessageEncoderDecoder& other):opCode(other.opCode),
             strBuffer(other.strBuffer),buffer(other.buffer), pckSize(other.pckSize), blkNum(other.blkNum),
             dataArr(other.dataArr), errCode(other.errCode){
}