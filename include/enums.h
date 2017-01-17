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
        WAITING
    };
    extern enumNamespace::PacketType g_status;
    extern std::string g_fileNameString;
}

