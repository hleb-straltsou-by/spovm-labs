#ifndef TUTORLINUX_H
#define TUTORLINUX_H

using namespace std;

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>      //strlen
#include <stdlib.h>      //malloc
#include <sys/socket.h>  //sockets
#include <arpa/inet.h>   //inet_addr
#include <unistd.h>      //write
#include <pthread.h>     //for threading , link with lpthread
#include "tutor.h"
#include "studentsqueue.h"

#define BUFFER_SIZE 1024
#define SOCKET_PORT 4025

class TutorLinux : public Tutor
{
private:

    int socketDesc;

    static vector<string> subjects;

    static StudentsQueue studentsQueue;

    static pthread_mutex_t mutex;

public:

    TutorLinux();

    ~TutorLinux();

    void start(int logFrequency);

    void end();

private:

    bool createConnectionHandler(int* socket);

    static void *handleConnection(void *socketDesc);

    static bool checkLab(string lab);

    static void *logStudents(void *arg);

};

#endif // TUTORLINUX_H
