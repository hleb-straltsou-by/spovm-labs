#ifndef TUTOR_H
#define TUTOR_H

#include <iostream>

using namespace std;

class Tutor
{
public:

    Tutor();

    ~Tutor();

    virtual bool connectToPipe(string pipePath) = 0;

    virtual void checkLabs() = 0;

    virtual void closeConnectionToPipe() = 0;
};

#endif // TUTOR_H
