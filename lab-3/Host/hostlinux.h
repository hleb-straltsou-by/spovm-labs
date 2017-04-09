#ifndef HOSTLINUX_H
#define HOSTLINUX_H

#include "host.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>     //for threading , link with lpthread
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

#define BUFFER_SIZE 1024

struct processInfo {
    pid_t pid;
};

class HostLinux : public Host
{
    static vector<string> commands;

public:

    HostLinux();

    ~HostLinux();

    void createStudent();

    static void createStudentStatic();

    void createStudentWithPeriod(int period);

    void createTutor(int logFrequency);

    void listenUserCommand();

private:

    char* parseIntToString(int number);

    static void deleteStudent(int idStudent);

    static void *handleUserCommands(void *arg);
};

#endif // HOSTLINUX_H
