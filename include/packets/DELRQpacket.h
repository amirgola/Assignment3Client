#ifndef DELRQPACKET_H_
#define DELRQPACKET_H_

class DELRQpacket : public Packet{
private:
    string fileName_;
public:
    DELRQpacket(string fileName);
    string getFileName();
};