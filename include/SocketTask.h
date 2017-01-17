//
// Created by Stephanie Schustermann on 17/01/2017.
//

#ifndef BOOST_ECHO_CLIENT_SOCKETTASK_H
#define BOOST_ECHO_CLIENT_SOCKETTASK_H


class SocketTask {
private:
    int _id;
public:
    SocketTask(int number);
    void operator()();
};


#endif //BOOST_ECHO_CLIENT_SOCKETTASK_H
