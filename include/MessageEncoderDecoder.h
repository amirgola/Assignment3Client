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
    std::vector<char> bytes;
    std::vector<char> opCodeBytes;
    int opCodeLen;
    int len;
    std::string msgType;
    std::string strBuffer;
    bool finishFirstTwoBytes;
    std::vector<char> buffer;
    bool firstTime;
    //for data packet
    short pckSize;
    short blkNum;
    std::vector<char> *dataArr;
    int dataIndex;

    std::vector<char> shortToBytes(short num);
    short bytesToShort(std::vector<char> byteArr);
    std::string whichMsg(short i);
    void resetBuffer();
    void findOpCode(char nextByte);
    std::vector<char> bufferToByteArray();

public:
    Packet decodeNextByte(char nextByte);
    std::vector<char> encode(Packet message);
    ~MessageEncoderDecoder();
};

#endif
