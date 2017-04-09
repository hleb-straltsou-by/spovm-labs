#ifndef STUDENTWINDOWS_H
#define STUDENTWINDOWS_H

#ifdef WIN32 || WIN64

#pragma comment(lib, "Ws2_32.lib")
#include<iostream>
#include<stdio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include"Student.h"
#include <winsock2.h>
#include<vector>

class StudentWindows : public Student
{
public:
    StudentWindows();
    ~StudentWindows();
    bool getConnection();
    void completeLabs();
    void sendMessage(std::string message);
    std::string readMessage() ;
    void closeConnection() ;

private:
    void sendInt(int number);
    void getInt(int &i);

    SOCKET connection;
    SOCKADDR_IN addr;
    const int PORT = 1101;
    std::vector<std::string> labs;
    void check();
};

#endif

#endif // STUDENTWINDOWS_H
