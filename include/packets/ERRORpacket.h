#ifndef ERRORPACKET_H_
#define ERRORPACKET_H_

class ERRORpacket : public Packet{
private:
    short errCode;
    string errMsg;
public:
    ERRORpacket(short errCode, string errMsg);
    short getErrCode();
    string getErrMsg();
};

#endif