#ifndef MessageEncoderDecoder_H_
#define MessageEncoderDecoder_H_

#include "./packets/Packet.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class MessageEncoderDecoder {
private:
    short opCode;
    std::vector<char> opCodeBytes;
    int opCodeLen;
    std::string strBuffer;
    std::vector<char> buffer;
    //for data packet
    short pckSize;
    short blkNum;
    std::vector<char> *dataArr;
    short errCode;

    void shortToBytes(short num, char* bytesArr);
    short bytesToShort(std::vector<char> byteArr);
    void resetBuffer();
    void findOpCode(char nextByte);

public:
    Packet decodeNextByte(char nextByte);
    std::vector<char> encode(Packet* message);
    ~MessageEncoderDecoder();
};

#endif
