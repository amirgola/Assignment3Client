#include <vector>
#include "./../include/MessageEncoderDecoder.h"
#include "./../include/enums.h"
#include "./../include/Packets/Packet.h"
#include "../include/packets/RRQpacket.h"
#include "../include/packets/WRQpacket.h"
#include "../include/packets/DATApacket.h"


Packet MessageEncoderDecoder::decodeNextByte(char nextByte){
    // if we have two bytes - then we can decode the rest of the message
    if(opCode == 0) {
        findOpCode(nextByte);
    } else {
        switch(opCode) {
            case enumNamespace::PacketType::RRQ :
                if(nextByte != '\0') {
                    buffer.push_back(nextByte);
                } else {
                    strBuffer = std::string(buffer.begin(), buffer.end());
                    resetBuffer();
                    return RRQpacket(strBuffer);
                }
                break;
            case enumNamespace::PacketType::WRQ:
                if(nextByte != '\0') {
                    buffer.push_back(nextByte);
                } else {
                    strBuffer = std::string(buffer.begin(), buffer.end());
                    resetBuffer();
                    return WRQpacket(strBuffer);
                }
                break;
            case enumNamespace::PacketType::DATA:
                if(buffer.size() < 4) { // 0,1,2,3 position get filled in buffer
                    buffer.push_back(nextByte);
                    if (buffer.size() == 2) {
                        pckSize = bytesToShort(buffer);
                        dataArr = new std::vector<char>();
                    }
                    if (buffer.size() == 4) {
                        std::vector<char> newVector(buffer.begin()+2,buffer.end());
                        blkNum = bytesToShort(newVector);
                    }
                } else {
                    dataArr->push_back(nextByte);
                    if (dataArr->size() == pckSize) {
                        resetBuffer();
                        return DATApacket(pckSize, blkNum, *dataArr);
                    }
                }
                break;
            case enumNamespace::PacketType::ACK:
                break;
            case enumNamespace::PacketType::ERROR:
                break;
            case enumNamespace::PacketType::DIRQ:
                break;
            case enumNamespace::PacketType::LOGRQ:
                break;
            case enumNamespace::PacketType::DELRQ:
                break;
            case enumNamespace::PacketType::BCAST:
                break;
            case enumNamespace::PacketType::DISC:
                break;
            case enumNamespace::PacketType::UNKNOWN:
            default:
                break;
        }
    }
}


std::vector<char> MessageEncoderDecoder::encode(Packet message){

}


//class MessageEncoderDecoder {
//private:
//    short opCode;
//    vector<char> bytes;
//    vector<char> opCodeBytes;
//    int opCodeLen;
//    int len;
//    String msgType;
//    String str;
//    boolean finishFirstTwoBytes;
//    ByteBuffer buffer;
//    boolean firstTime;
//    //for data packet
//    short pckSize;
//    short blkNum;
//    vector<char> dataArr;
//    int dataIndex;

    std::vector<char> MessageEncoderDecoder::shortToBytes(short num){

    }

    short MessageEncoderDecoder::bytesToShort(std::vector<char> byteArr){
        short result = (short)((byteArr[0] & 0xff) << 8);
        result += (short)(byteArr[1] & 0xff);
        return result;
    }

    std::string MessageEncoderDecoder::whichMsg(short i){

    }

    void MessageEncoderDecoder::resetBuffer(){
        finishFirstTwoBytes = false;
        buffer.clear();
        firstTime = true;
        //reset the opcode array
        opCodeLen = 0;
        opCodeBytes[0] = 0;
        opCodeBytes[1] = 0;
    }

    void MessageEncoderDecoder::findOpCode(char nextByte){
        opCodeBytes[opCodeLen++] = nextByte;
        if(opCodeLen == 2) {
            opCode = bytesToShort(opCodeBytes);
        }
    }

    std::vector<char> MessageEncoderDecoder::bufferToByteArray(){

    }