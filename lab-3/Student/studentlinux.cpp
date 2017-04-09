#include "studentlinux.h"

StudentLinux::StudentLinux() : Student()
{
    labList.push_back("spovm");
    labList.push_back("apk");
    labList.push_back("cpp");
}

StudentLinux::~StudentLinux()
{}

bool StudentLinux::getConnection()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        printf("Error! Could not create socket\n");
        return false;
    }
    printf("Socked is created.\n");
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(SOCKET_PORT);

    // Connect to server
    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Error! Connect failed.\n");
        return false;
    }
    printf("Client has been connected to the server.\n");
    return true;
}

void StudentLinux::sendMessage(string message)
{    
    memset(&clientRequest, 0, BUFFER_SIZE);
    strcpy(clientRequest, message.c_str());
    if(send(sock, message.c_str(), message.size(), 0) < 0)
    {
        printf("Error! Send of message to the server is failed.\n");
    }
    printf("Message to the server has been sent.\n");
}

void StudentLinux::completeLabs()
{
    for(unsigned int i = 0; i < labList.size(); i++)
    {
        sendMessage(labList[i]);
        cout << readMessage() << endl;
    }
}

string StudentLinux::readMessage()
{
    memset(&serverReply, 0, BUFFER_SIZE);
    if(recv(sock, serverReply, BUFFER_SIZE, 0) < 0)
    {
        printf("Error! Reading of message from the server is failed.\n");
    }
    string replyStr = serverReply;
    printf("Message from the server is received.\n");
    return replyStr;
}

void StudentLinux::closeConnection()
{
    //close(SOCKET_PORT);
}
