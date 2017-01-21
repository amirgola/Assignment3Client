#ifndef ENUMS_H_
#define ENUMS_H_
namespace enumNamespace{
    enum PacketType {
        RRQ = 1,
        WRQ,
        DATA,
        ACK,
        ERROR,
        DIRQ,
        LOGRQ,
        DELRQ,
        BCAST,
        DISC,
        UNKNOWN,
        WAITING,
        DISCONNECTED,
        STARTED
    };
    extern enumNamespace::PacketType g_status;
    extern std::string g_fileNameString;
}

#endif