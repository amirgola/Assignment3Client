#include <vector>
#include "./../include/MessageEncoderDecoder.h"
#include "./../include/enums.h"
#include "./../include/Packets/Packet.h"



Packet MessageEncoderDecoder::decodeNextByte(char nextByte){
    // if we have two bytes - then we can decode the rest of the message
    if(opCode == 0) {

    } else {
//        switch(opCode) {
//            case enumNamespace::PacketType::RRQ :
//                break;       // and exits the switch
//            case enumNamespace::PacketType::WRQ:
//                break;
//        }
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

    }

    std::string MessageEncoderDecoder::whichMsg(short i){

    }

    void MessageEncoderDecoder::resetBuffer(){

    }

    void MessageEncoderDecoder::findOpCode(char nextByte){

    }

    std::vector<char> MessageEncoderDecoder::bufferToByteArray(){

    }