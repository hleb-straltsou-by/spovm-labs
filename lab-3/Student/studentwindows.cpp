
#include "studentwindows.h"

#ifdef WIN32 || WIN64

StudentWindows::StudentWindows()
{
#include "StudentWindows.h"
#include<thread>


StudentWindows::StudentWindows()
{
    labs.push_back("spovm");
    labs.push_back("cpp");
    labs.push_back("apc");

}

StudentWindows::~StudentWindows()
{}

bool StudentWindows::getConnection() {
    WSADATA wsaData;
    WORD version = MAKEWORD(2, 2);
    int res = WSAStartup(version, &wsaData);
    if (res)
    {
        printf("winsock not bi initialized !\n");
        return false;
    }

    int addrlen = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;


    printf("connected to tutor\n");
    return true;
}

void StudentWindows::sendMessage(std::string message) {
    int size = message.size();
    sendInt(size);
    ::send(connection, message.c_str() , size, NULL);
 }

void StudentWindows::sendInt(int i) {
    ::send(connection, (char*)&i, sizeof(int), NULL);
}

void StudentWindows::getInt(int &i) {
    ::recv(connection, (char*)&i, sizeof(int), NULL);
}


void StudentWindows::closeConnection() {
    closesocket(connection);
}

std::string StudentWindows::readMessage() {
    int size;
    getInt(size);
    char *_message = (char*)malloc(size);
    ::recv(connection, _message, size, NULL);
    _message[size] = '\0';
    std::string message(_message);
    return message;
}

void StudentWindows::completeLabs() {
    int addrlen = sizeof(addr);
    printf("compete labs\n");
    connection = ::socket(AF_INET, SOCK_STREAM, NULL);
    if (::connect(connection, (SOCKADDR*)&addr, addrlen) != 0) {
        printf("Error connect");
        return;
    }
    std::string welcome = readMessage();
    if (!strcmp(welcome.c_str(),"Let's go!")) {
        printf("let's go!\n");
        sendInt(labs.size());
        for (int i = 0; i < labs.size(); i++) {
            sendMessage(labs[i]);
        }
        std::string ans = readMessage();
        std::cout << ans.c_str() << std::endl;
    }
    else {
        printf("whata fuck!!");

    }
}

void StudentWindows::check() {
    int n;
    scanf("%d", &n);
    if (n == 1) {
        printf("Sosi");
    }
}
}

#endif

