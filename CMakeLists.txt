cmake_minimum_required(VERSION 3.6)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.63.0 COMPONENTS system filesystem thread REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES
        include/connectionHandler.h
        include/enums.h
        include/MessageEncoderDecoder.h
        include/packets/ACKpacket.h
        include/packets/BCASTpacket.h
        include/packets/DATApacket.h
        include/packets/DELRQpacket.h
        include/packets/DIRQpacket.h
        include/packets/DISCpacket.h
        include/packets/ERRORpacket.h
        include/packets/LOGRQpacket.h
        include/packets/Packet.h
        include/packets/RRQpacket.h
        include/packets/WRQpacket.h
        include/concurrent_queue.h
        src/packets/ACKpacket.cpp
        src/packets/BCASTpacket.cpp
        src/packets/DATApacket.cpp
        src/packets/DELRQpacket.cpp
        src/packets/DIRQpacket.cpp
        src/packets/DISCpacket.cpp
        src/packets/ERRORpacket.cpp
        src/packets/LOGRQpacket.cpp
        src/packets/Packet.cpp
        src/packets/RRQpacket.cpp
        src/packets/WRQpacket.cpp
        src/concurrent_queue.cpp
        src/connectionHandler.cpp
        src/echoClient.cpp
        src/MessageEncoderDecoder.cpp)

add_executable(Boost_Echo_Client ${SOURCE_FILES})

target_link_libraries(Boost_Echo_Client ${Boost_LIBRARIES})