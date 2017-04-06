#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student
{

public:

    Student();

    ~Student();

    virtual bool getConnection() = 0;

    virtual void sendMessage(string message) = 0;

    virtual void completeLabs() = 0;

    virtual string readMessage() = 0;

    virtual void closeConnection() = 0;
};

#endif // STUDENT_H
