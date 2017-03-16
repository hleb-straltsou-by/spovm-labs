#ifdef __linux
#ifndef TUTOR_LINUX_H
#define TUTOR_LINUX_H

#include <iostream>
#include <tutor.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

class Tutor_linux : public Tutor
{  
private:

    FILE* pipe;

    vector<string> subjects;

    const int static MAX_SYMBOL_COUNT = 4;

public:

    Tutor_linux(vector<string> subjects);

    ~Tutor_linux();

    bool connectToPipe(string pipePath);

    void checkLabs();

    void closeConnectionToPipe();

private:

    int parseInteger();

    string getStringFromPipe(int size);

    bool compareWithTutorSubjects(string lab);
};

#endif // TUTOR_LINUX_H

#endif
