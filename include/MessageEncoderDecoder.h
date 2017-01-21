#ifndef MESSAGEENCODERDECODER_H_
#define MESSAGEENCODERDECODER_H_

#include "Packet.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class MessageEncoderDecoder {
private:
    short opCode;
    std::string strBuffer;
    std::vector<char> buffer;
    //for data packet
    short pckSize;
    short blkNum;
    std::vector<char> *dataArr;
    short errCode;

    void shortToBytes(short num, char* bytesArr);
    short bytesToShort(char* bytesArr);
    void resetBuffer();
public:
    MessageEncoderDecoder();
    Packet* decodeNextByte(char nextByte);
    std::vector<char> encode(Packet* message);
    short decodePacketType(char bytes[]);
    ~MessageEncoderDecoder();
};

#endif
