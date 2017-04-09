#ifdef WIN32 || WIN64
#pragma comment(lib, "Ws2_32.lib")
#include<iostream>
#include<stdio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include"StudentWindows.h"
#endif

#include <iostream>
#include <studentlinux.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <fcntl.h>

using namespace std;

int main()
{
    cout << "Student process is lunched." << endl;

    sleep(5);

    Student *student;

    #ifdef __linux
    student = new StudentLinux;
    #endif

    #ifdef WIN32 || WIN64
    student = new StudentWindows;
    #endif

    if(!student->getConnection()){
        cout << "Error! Cannot connect to the server." << endl;
        sleep(5);
        return -1;
    }

    cout << student->readMessage();

    student->completeLabs();

    cout << "Client has been successfully finish his work." << endl;
    sleep(5);

    return 0;
}

