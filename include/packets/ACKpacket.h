#ifndef ACKPACKET_H_
#define ACKPACKET_H_

class ACKpacket : public Packet{
private:
    short blockNumber_;
public:
    ACKpacket(short i);
    short getBlockNumber();
};

#endif