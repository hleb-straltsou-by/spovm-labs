#ifdef WIN32 || WIN64

#include "tutorwindows.h"

HostWindows::HostWindows()
{}


HostWindows::~HostWindows()
{}

void HostWindows::createStudent() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess("C:\\Users\\Ñåðãåé\\Documents\\Visual Studio 2015\\Projects\\University Version 2.0\\Debug\\Student(Client).exe",
            NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
            return;
}

void HostWindows::createStudentWithPeriod(int time) {
    while (true) {
        createStudent();
        Sleep(1000 * time);
    }
}

void HostWindows::createTutor(int time) {
    char *timeString = (char*)malloc(3);
    itoa(time, timeString, 10);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess("C:\\Users\\Ñåðãåé\\Documents\\Visual Studio 2015\\Projects\\University Version 2.0\\Debug\\Tutor(Server).exe",
        const_cast<LPSTR>(timeString), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
        return;
}

void HostWindows::listenUserCommand() {
    int addrlen = sizeof(addrH);
    connection = ::socket(AF_INET, SOCK_STREAM, NULL);
    if (::connect(connection, (SOCKADDR*)&addrH, addrlen) != 0) {
        printf("Error connect");
        return;
    }
    while (true) {
        char str[200];
        char *command;
        gets_s(str);
        command = strtok(str, " ");
        char *id;
        id = strtok(NULL, " ");
        if (!strcmp(command,"del")) {
            sendMessage("del");
            int index = atoi(id);
            sendInt(index);
        }
        else if (!strcmp(command, "add")) {
            createStudent();
        }
        else {
            printf("Unknown command!\n");
        }


    }
}

bool HostWindows::getConnection() {
    WSADATA wsaData;
    WORD version = MAKEWORD(2, 1);
    int res = WSAStartup(version, &wsaData);
    if (res)
    {
        printf("winsock not bi initialized !\n");
        return false;
    }

    int addrlen = sizeof(addrH);
    addrH.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrH.sin_port = htons(1110);
    addrH.sin_family = AF_INET;


    std::thread t = std::thread(&HostWindows::listenUserCommand, this);
    t.detach();
    return true;
}


void HostWindows::sendMessage(std::string message) {
    int size = message.size();
    sendInt(size);
    ::send(connection, message.c_str() , size, NULL);
 }

void HostWindows::sendInt(int i) {
    ::send(connection, (char*)&i, sizeof(int), NULL);
}

#endif
