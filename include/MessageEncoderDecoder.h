#ifndef MessageEncoderDecoder_H_
#define MessageEncoderDecoder_H_

class MessageEncoderDecoder {
private:
    short opCode;
    vector<char> bytes;
    vector<char> opCodeBytes;
    int opCodeLen;
    int len;
    String msgType;
    String str;
    boolean finishFirstTwoBytes;
    ByteBuffer buffer;
    boolean firstTime;
    //for data packet
    short pckSize;
    short blkNum;
    vector<char> dataArr;
    int dataIndex;

    vector<char> shortToBytes(short num);
    short bytesToShort(vector<char> byteArr);
    string whichMsg(short i);
    void resetBuffer();
    void findOpCode(byte nextByte);
    vector<char> bufferToByteArray();

public:
    Packet decodeNextByte(char nextByte);

    vector<char> encode(Packet message);
};
