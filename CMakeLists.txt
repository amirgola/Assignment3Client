cmake_minimum_required(VERSION 3.6)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.63.0 COMPONENTS system filesystem thread REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES
        include/connectionHandler.h
        src/connectionHandler.cpp
        src/echoClient.cpp)

add_executable(Boost_Echo_Client ${SOURCE_FILES})

target_link_libraries(Boost_Echo_Client ${Boost_LIBRARIES})