#include <vector>
#include "./../include/MessageEncoderDecoder.h"
#include "./../include/enums.h"
#include "./../include/packets/RRQpacket.h"
#include "./../include/packets/WRQpacket.h"
#include "./../include/packets/DATApacket.h"
#include "./../include/packets/ACKpacket.h"
#include "./../include/packets/ERRORpacket.h"
#include "./../include/packets/DISCpacket.h"
#include "./../include/packets/BCASTpacket.h"
#include "./../include/packets/DELRQpacket.h"
#include "./../include/packets/LOGRQpacket.h"
#include "./../include/packets/DIRQpacket.h"
#include "./../include/packets/Packet.h"


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
                    return  new WRQpacket(strBuffer);
                }
                break;
            }
            case enumNamespace::PacketType::DATA: {
                if (buffer.size() < 4) { // 0,1,2,3 position get filled in buffer
                    buffer.push_back(nextByte);
                    if (buffer.size() == 2) {
                        pckSize = bytesToShort(reinterpret_cast<char*>(buffer.data()));
                        dataArr = new std::vector<char>();
                    }
                    if (buffer.size() == 4) {
                        std::vector<char> newVector(buffer.begin() + 2, buffer.end());
                        blkNum = bytesToShort(reinterpret_cast<char*>(newVector.data()));
                    }
                } else {
                    dataArr->push_back(nextByte);
                    if (dataArr->size() == pckSize) {
                        resetBuffer();
                        return new DATApacket(pckSize, blkNum, *dataArr);
                    }
                }
                break;
            }
            case enumNamespace::PacketType::ACK: {
                buffer.push_back(nextByte);
                if (buffer.size() >= 2) {
                    std::vector<char> newVector(buffer);
                    resetBuffer();
                    return new ACKpacket(bytesToShort(reinterpret_cast<char*>(newVector.data())));
                }
                break;
            }
            case enumNamespace::PacketType::ERROR: {
                if (nextByte != '\0') {
                    buffer.push_back(nextByte);
                    if (buffer.size() == 2) {
                        errCode = bytesToShort(reinterpret_cast<char*>(buffer.data()));
                    }
                } else {
                    short errorCode = errCode;
                    resetBuffer();
                    return new ERRORpacket(errorCode, std::string(buffer.begin() + 2, buffer.end()));
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
                if (nextByte != '\0') {
                    buffer.push_back(nextByte);
                } else {
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
            char *pctSizeArray;
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
            temp = std::vector<char>(((RRQpacket *) message)->getFileName().begin(),
                                     ((RRQpacket *) message)->getFileName().end());

            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);
            for (int i = 0; i < temp.size(); ++i) {
                res.push_back((char &&) temp.at(i));
            }
            res.push_back(0);

            return res;
        }
        case enumNamespace::PacketType::WRQ: {

            shortToBytes(message->getOpCode(), opCodeArray);
            temp = std::vector<char>(((WRQpacket *) message)->getFileName().begin(),
                                     ((WRQpacket *) message)->getFileName().end());

            res.push_back(opCodeArray[0]);
            res.push_back(opCodeArray[1]);
            for (int i = 0; i < temp.size(); ++i) {
                res.push_back((char &&) temp.at(i));
            }
            res.push_back(0);

            return res;
        }
        case enumNamespace::PacketType::DIRQ: {
            char *result;
            shortToBytes(message->getOpCode(), result);
            std::string tempResult(result);
            std::vector<char> bufferResult(tempResult.begin(), tempResult.end());
            return bufferResult;
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
            char *discResult;
            shortToBytes(message->getOpCode(), discResult);
            std::string discTempResult(discResult);
            std::vector<char> bufferDiscResult(discTempResult.begin(), discTempResult.end());
            return bufferDiscResult;
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

}
