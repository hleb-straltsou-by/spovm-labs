#ifndef TUTORLINUX_H
#define TUTORLINUX_H

using namespace std;

#include<iostream>
#include<stdio.h>
#include<string.h>      //strlen
#include<stdlib.h>      //malloc
#include<sys/socket.h>  //sockets
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>      //write
#include<pthread.h>     //for threading , link with lpthread
#include "tutor.h"

#define BUFFER_SIZE 1024
#define SOCKET_PORT 4021

class TutorLinux : public Tutor
{
private:

    int socketDesc;

public:

    TutorLinux();

    ~TutorLinux();

    void start();

    void end();

private:

    bool createConnectionHandler(int* socket);

    static void *handleConnection(void *socketDesc);

};

#endif // TUTORLINUX_H
