//
// Created by Stephanie Schustermann on 17/01/2017.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDTASK_H
#define BOOST_ECHO_CLIENT_KEYBOARDTASK_H

class KeyboardTask {
private:
    int _id;
public:
    KeyboardTask(int number);
    void operator()();
};

#endif //BOOST_ECHO_CLIENT_KEYBOARDTASK_H
