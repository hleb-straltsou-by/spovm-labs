#ifndef STUDENT_LINUX_H
#define STUDENT_LINUX_H

#include <iostream>
#include <stdio.h>
#include <student.h>
#include <vector>
#include <unistd.h>

using namespace std;

#define FIFO_NAME "./fifofile"

class Student_linux : public Student
{
private:

    FILE* pipe;

public:

    Student_linux();

    ~Student_linux();

    bool connectToPipe(string pipePath);

    void completeLab(vector<string> labList);

    void closeConnectionToPipe();

};

#endif // STUDENT_LINUX_H
