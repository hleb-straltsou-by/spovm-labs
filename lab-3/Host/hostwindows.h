#ifdef WIN32 || WIN64

#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include<WinSock2.h>
#include"Host.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<thread>

using namespace std;


class HostWindows : public Host
{
public:
    HostWindows();
    ~HostWindows();

    void createStudentWithPeriod(int time);
    void createStudent();
    void createTutor(int time);
    void listenUserCommand();
    bool getConnection();
private:
    void sendInt(int number);
    void sendMessage(std::string message);
    SOCKET connection;
    SOCKADDR_IN addrH;
};

#efdif

#endif // TUTORWINDOWS_H
