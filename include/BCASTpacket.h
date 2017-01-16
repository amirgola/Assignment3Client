#ifndef BCASTPACKET_H_
#define BCASTPACKET_H_

class BCASTpacket : public Packet{
private:
    string filename_;
    char delAdd_;
public:
    BCASTpacket(char delAdd, string fileName);
    string getFilname();
    char getDelAdd();
};

