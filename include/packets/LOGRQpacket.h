#ifndef LOGRQPACKET_H_
#define LOGRQPACKET_H_

class LOGRQpacket : public Packet{
private:
    string userName_;
public:
    LOGRQpacket(string userName);
    string getUserName();
};

#endif