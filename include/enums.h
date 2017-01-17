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
        UNKNOWN
    };

    extern enumNamespace::PacketType g_status;
}