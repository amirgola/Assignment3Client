cmake_minimum_required(VERSION 3.6)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Weffc++ -std=c++11 ")

find_package(Boost 1.63.0 COMPONENTS system filesystem thread REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

set(SOURCE_FILES
        include/connectionHandler.h
        include/enums.h
        include/MessageEncoderDecoder.h
        include/ACKpacket.h
        include/BCASTpacket.h
        include/DATApacket.h
        include/DELRQpacket.h
        include/DIRQpacket.h
        include/DISCpacket.h
        include/ERRORpacket.h
        include/LOGRQpacket.h
        include/Packet.h
        include/RRQpacket.h
        include/WRQpacket.h
        include/KeyboardTask.h
        include/SocketTask.h
        include/Protocol.h
        src/ACKpacket.cpp
        src/BCASTpacket.cpp
        src/DATApacket.cpp
        src/DELRQpacket.cpp
        src/DIRQpacket.cpp
        src/DISCpacket.cpp
        src/ERRORpacket.cpp
        src/LOGRQpacket.cpp
        src/Packet.cpp
        src/RRQpacket.cpp
        src/WRQpacket.cpp
        src/Protocol.cpp
        src/connectionHandler.cpp
        src/KeyboardTask.cpp
        src/SocketTask.cpp
        src/echoClient.cpp
        src/MessageEncoderDecoder.cpp)

add_executable(Boost_Echo_Client ${SOURCE_FILES})

target_link_libraries(Boost_Echo_Client ${Boost_LIBRARIES})