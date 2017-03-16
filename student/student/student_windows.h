#ifdef WIN32 || WIN64
#pragma once
#include"student.h"

class Student_windows: public Student
{
private:

    HANDLE hNamedPipe;
    HANDLE hSemaphore;
    HANDLE hCheckLabsEvent;
    HANDLE hAnsTutorEvent;

    bool writeInPipeNumber(int number);
    bool writeInPipeString(string string);
    bool writeInPipe(vector<string> labInfo);
    bool readFromPipe();

public:

    const int MAX_STR_SIZE = 80;
    bool connectToPipe(string pipePath);
    bool completeLab(vector<string> labInfo);
    bool setSemaphore(string name);
    bool setCheckLabsEvent(string name);
    bool setAnsTutorEvent(string name);
    void closeConnectionToPipe();
    Student_windows();
    ~Student_windows();

};
#endif
