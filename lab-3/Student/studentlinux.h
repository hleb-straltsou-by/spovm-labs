#ifndef STUDENTLINUX_H
#define STUDENTLINUX_H

#include <iostream>
#include <stdio.h>          // printf
#include <string.h>         // strlen
#include <sys/socket.h>     // socket
#include <arpa/inet.h>      // inet_addr
#include "student.h"

#define BUFFER_SIZE 1024

#define SOCKET_PORT 4021

class StudentLinux : public Student
{
private:

    int sock;

    struct sockaddr_in server;

    char serverReply[BUFFER_SIZE];

    char clientRequest[BUFFER_SIZE];

public:

    StudentLinux();

    ~StudentLinux();

    bool getConnection();

    void sendMessage(string message);

    void completeLabs();

    string readMessage();

    void closeConnection();
};

#endif // STUDENTLINUX_H
