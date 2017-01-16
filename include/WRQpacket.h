#ifndef WRQPACKET_H_
#define WRQPACKET_H_

class WRQpacket : public Packet{
private:
    string fileName_;
public:
    WRQpacket(string fileName);
    string getFileName();
};