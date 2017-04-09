#ifndef TUTORWINDOWS_H
#define TUTORWINDOWS_H

#ifdef WIN32 || WIN64

#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include<stdio.h>
#include<WinSock2.h>
#include"Tutor.h"
#include<thread>
#include<string.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>

class TutorWindows
{
public:
    TutorWindows();
    ~TutorWindows();
    void start(int logFrequency);
    void checkLabs();
    void end();
    void newThread(int i);

private:
    int countConn = 0;
    int outputPeriod = 5;

    SOCKADDR_IN addr;
    bool connectionsNow[100];
    std::vector<int> currentStudentIndex;
    const int PORT = 1101;
    SOCKET sListen;
    HANDLE hSemaphore;
    HANDLE hSemaphoreAccess;
    std::map<int, SOCKET> connections;
    std::map<int, std::thread> workers;

    std::set<std::string> subjects;


    void sendInt(int number, SOCKET connection);
    void sendMessage(std::string message, SOCKET connection);
    std::string readMessage( SOCKET connection);
    void getInt(int &number, SOCKET connection);
    void outInfo();
    void listenTutorCommands();
    void delStudent(int index);

    int findElement(int element);
    void getAccess();
    void retAccess();
};

#endif

#endif // TUTORWINDOWS_H
