//
// Created by Medhopz on 1/17/2017.
//

Packet handleKeyboard::process ( String str) {
    std::size_t found = str.find_first_of(" ");
    std::string command = std::string::str.substr(0, found);
    std::string fileName = std::string::str.substr(found);
    switch(str) {
        case "DIRQ":
            return DIRQpacket();
            status = "DIRQ";
            break;
        case "DELRQ":
            sendList->push(DELRQpacket(fileName));
            status = "DELRQ";
            break;
        case "RRQ":
            sendList->push(RRQpacket(fileName));
            status = "RRQ";
            break;
        case "WRQ":
            //split file into packets. put the packets into a vector
            splitFileIntoDataPackets(fileName);
            //send first packet
            sendList->push(WRQpacket(fileName));
            status = "WRQ";
            break;
        case "LOGRQ":
            sendList->push(LOGRQpacket(fileName));
            status = "LOGRQ";
            break;
        case "DISC":
            sendList->push(DISCQpacket());
            status = "DISC";
            break;
    }
}