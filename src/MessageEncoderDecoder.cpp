#include <vector>
#include "./../include/MessageEncoderDecoder.h"
#include "./../include/enums.h"
#include "./../include/Packets/Packet.h"



Packet MessageEncoderDecoder::decodeNextByte(char nextByte){
    // if we have two bytes - then we can decode the rest of the message
    if(opCode == 0) {
        findOpCode(nextByte);
    } else {
        switch(opCode) {
            case enumNamespace::PacketType::RRQ :
//                if(nextByte != '\0') {
//                    buffer.
//                } else {
//                    try {
//                        strBuffer = new String(buffer.array(), "UTF-8");
//                        resetBuffer();
//                        return new RRQpacket(strBuffer);
//                    } catch (UnsupportedEncodingException e) {
//                        e.printStackTrace();
//                    }
//                }
//                break;
                break;
            case enumNamespace::PacketType::WRQ:
                break;
            case enumNamespace::PacketType::DATA:
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

    }

    void MessageEncoderDecoder::findOpCode(char nextByte){
        opCodeBytes[opCodeLen++] = nextByte;
        if(opCodeLen == 2) {
            opCode = bytesToShort(opCodeBytes);
        }
    }

    std::vector<char> MessageEncoderDecoder::bufferToByteArray(){

    }