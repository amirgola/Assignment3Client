#ifndef RRQPACKET_H_
#define RRQPACKET_H_

class RRQpacket : public Packet{
private:
    string fileName_;
public:
    RRQpacket(string fileName);
    string getFileName();
};

#endif