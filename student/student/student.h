#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

class Student
{
public:

    Student();

    ~Student();

    virtual bool connectToPipe(string pipePath) = 0;

    virtual void completeLab(vector<string> labList) = 0;

    virtual void closeConnectionToPipe() = 0;
};

#endif // STUDENT_H
