#ifdef WIN32 || WIN64
#pragma once
#include"tutor.h"
#include<string>
#include<vector>
#include<set>

class Tutor_windows:public Tutor
{
private:
    HANDLE hCheckLabsEvent;
    HANDLE hAnsTutorEvent;
    HANDLE hNamedPipe;
    HANDLE hSemaphore;

    BOOL fConnection;

    set<string> subjects;
    bool labOk;
    int size ;
    bool writeInPipeNumber();
    bool readFromPipe();
    bool readFromPipeNumber();
    bool readFromPipeString();
public:
    const int MAX_STR_SIZE = 80;
    bool setSemaphore(string name);
    bool setCheckLabsEvent(string name);
    bool setAnsTutorEvent(string name);


    void checkLabs();
    bool connectToPipe(string pipePath);
    void closeConnectionToPipe();
    Tutor_windows();
    ~Tutor_windows();
};

#endif
