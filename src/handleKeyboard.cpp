//
// Created by Medhopz on 1/17/2017.
//

Packet handleKeyboard::process ( String str) {
    std::size_t found = str.find_first_of(" ");
    std::string command = std::string::str.substr(0, found);
    std::string fileName = std::string::str.substr(found);
    switch(command) {
        case DIRQ:
            enumNamespace::g_status = enumNamespace::PacketType::DIRQ;
            return DIRQpacket();
        case DELRQ:
            enumNamespace::g_status = enumNamespace::PacketType::DELRQ;
            return DELRQpacket(fileName);
        case RRQ:
            enumNamespace::g_status = enumNamespace::PacketType::RRQ;
            return RRQpacket(fileName);
        case WRQ:
            //split file into packets. put the packets into a vector
            splitFileIntoDataPackets(fileName);
            enumNamespace::g_status = enumNamespace::PacketType::WRQ;
            return WRQpacket(fileName);
        case LOGRQ:
            enumNamespace::g_status = enumNamespace::PacketType::LOGRQ;
            return LOGRQpacket(fileName);
        case DISC:
            enumNamespace::g_status = enumNamespace::PacketType::DISC;
            return DISCQpacket();
    }
}