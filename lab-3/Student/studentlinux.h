#ifndef STUDENTLINUX_H
#define STUDENTLINUX_H

#include <iostream>
#include <stdio.h>          // printf
#include <string.h>         // strlen
#include <sys/socket.h>     // socket
#include <arpa/inet.h>      // inet_addr
#include "student.h"

#define NAME_SIZE 100
#define BUFFER_SIZE 1024
#define SOCKET_PORT 4025

class StudentLinux : public Student
{
private:

    int sock;

    struct sockaddr_in server;

    vector<string> labList;

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
