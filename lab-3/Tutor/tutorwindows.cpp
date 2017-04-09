#ifdef WIN32 || WIN64
#include "TutorWindows.h"
#include<map>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>


TutorWindows::TutorWindows()
{


    subjects.insert("cpp");
    subjects.insert("apc");
    subjects.insert("shem");
    subjects.insert("spovm");
    hSemaphore = CreateSemaphore(NULL, 0, 1, "semaphore");
    ReleaseSemaphore(hSemaphore, 1, NULL);
    hSemaphoreAccess = CreateSemaphore(NULL, 0, 1, "semaphoreAccess");
    ReleaseSemaphore(hSemaphoreAccess, 1, NULL);

    std::thread t  = std::thread(&TutorWindows::outInfo,this);
    t.detach();
    std::thread t1 = std::thread(&TutorWindows::listenTutorCommands, this);
    t1.detach();



}


TutorWindows::~TutorWindows()
{
}


void TutorWindows::start(int logFrequency){
    outputPeriod = logFrequency;
    WSADATA wsaData;
    WORD clientVersion = MAKEWORD(2, 1);
    int res = WSAStartup(clientVersion, &wsaData);
    if (res)
    {
        printf("winsock not bi initialized !\n");
        return;
    }
    int addrlen = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    sListen = ::socket(AF_INET, SOCK_STREAM, NULL);
    ::bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    ::listen(sListen, SOMAXCONN);
}

void TutorWindows::end() {

}

void TutorWindows::checkLabs() {
    int addrlen = sizeof(addr);
    while (true) {
        SOCKET connection = ::accept(sListen, (SOCKADDR*)&addr, &addrlen);
        if (connection == 0) {
            printf("Error connections\n");
            return;
        }
        else {
            getAccess();
            connections.insert(std::pair<int, SOCKET>(countConn, connection));
            printf("Hello Student %d pls wait\n", countConn + 1);



            std::thread clientThread(&TutorWindows::newThread, this, countConn);
            clientThread.detach();

            currentStudentIndex.push_back(countConn++);
            retAccess();
        }
    }
}


void TutorWindows::newThread(int index) {
    WaitForSingleObject(hSemaphore, INFINITE);
    bool labOk = true;
    sendMessage("Let's go!", connections[index]);
    int sizeOfLab;
    getInt(sizeOfLab, connections[index]);
    for (int k = 0; k < sizeOfLab; k++) {
        std::string lab = readMessage(connections[index]);
        if (subjects.count(lab) == 0) {
            labOk = false;
        }
    }
    Sleep(12000);
    if (labOk) {
        sendMessage("Lab's is complete!", connections[index]);
    }
    else {
        sendMessage("Lab's is not complete!", connections[index]);
    }

    if ((index = findElement(index)) >= 0) {
        currentStudentIndex.erase(currentStudentIndex.begin() + index);
        connections.erase(index);
    }
    printf("Good bye student %d! Have a nice day\n", index + 1);
    ReleaseSemaphore(hSemaphore, 1, NULL);
}

void TutorWindows::sendMessage(std::string message,SOCKET connection) {
    int size = message.size();
    sendInt(size,connection);
    ::send(connection, message.c_str(), size, NULL);
}

void TutorWindows::sendInt(int i, SOCKET connection) {
    ::send(connection, (char*)&i, sizeof(int), NULL);
}

void TutorWindows::getInt(int &i, SOCKET connection) {
    ::recv(connection, (char*)&i, sizeof(int), NULL);
}




std::string TutorWindows::readMessage(SOCKET connection) {
    int size;
    getInt(size,connection);
    char *_message = (char*)malloc(size);
    ::recv(connection, _message, size, NULL);
    _message[size] = '\0';
    std::string message(_message);
    return message;
}

void TutorWindows::outInfo() {

    while (true) {
        printf("\n-------------------\n");
        printf("Students:\n");
        int size = currentStudentIndex.size();
        for each (int index in currentStudentIndex)
        {
            printf("Student #%d\n", index + 1);
        }
        printf("-------------------\n");
        Sleep(outputPeriod * 1000);
    }
}

void TutorWindows::listenTutorCommands() {
    WSADATA wsaData;
    WORD clientVersion = MAKEWORD(2, 1);
    int res = WSAStartup(clientVersion, &wsaData);
    if (res)
    {
        printf("winsock not bi initialized !\n");
        return;
    }


    SOCKADDR_IN addrH;
    int addrlen = sizeof(addrH);
    addrH.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrH.sin_port = htons(1110);
    addrH.sin_family = AF_INET;
    SOCKET sListenH;
    sListenH = ::socket(AF_INET, SOCK_STREAM, NULL);
    res = ::bind(sListenH, (SOCKADDR*)&addrH, sizeof(addr));
    res = ::listen(sListenH, SOMAXCONN);

    SOCKET connection = ::accept(sListenH, (SOCKADDR*)&addrH, &addrlen);
    while(true) {

        if (connection == 0) {
            printf("Error connections\n");
            return;
        }
        else {
            std::string command = readMessage(connection);
            int index;
            getInt(index, connection);
            delStudent(index);
        }
    }


}

void TutorWindows::delStudent(int index) {
    if (connections.count(index)) {
        getAccess();
        SOCKET socket = connections[index];
        if (index = findElement(index) > 0) {
            currentStudentIndex.erase(currentStudentIndex.begin() + index);
        }
        std::map<int, SOCKET>::iterator it = connections.begin();
        for (int i = 0; i < index; i++, it++);
        for (int i = index; i < currentStudentIndex.size(); i++,it++) {
            currentStudentIndex[i] -= 1;
            const_cast<int&>(it->first) = currentStudentIndex[i];

        }
        sendMessage("you now delete, sorry",connections[index]);
        connections.erase(index);
        countConn--;
        retAccess();
    }
}

int TutorWindows::findElement(int element) {
    int midd = 0;
    int left = 0;
    int right = currentStudentIndex.size();
    while (true)
    {
        midd = (left + right) / 2;

        if (element < currentStudentIndex[midd])
            right = midd - 1;
        else if (element > currentStudentIndex[midd])
            left = midd + 1;
        else
            return midd;

        if (left > right)
            return -1;
    }
}

void TutorWindows::getAccess() {
    WaitForSingleObject(hSemaphoreAccess, INFINITE);
}

void TutorWindows::retAccess() {
    ReleaseSemaphore(hSemaphoreAccess, 1, NULL);
}

#endif

