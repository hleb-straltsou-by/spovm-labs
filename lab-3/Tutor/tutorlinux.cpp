#include "tutorlinux.h"

TutorLinux::TutorLinux() : Tutor()
{}

TutorLinux::~TutorLinux()
{}

void TutorLinux::start()
{
    // create socket
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDesc == -1)
    {
        printf("Error! Cannot create socket.\n");
    }
    printf("Socket has been created.\n");

    // prepare the sockaddr_in structure
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SOCKET_PORT);

    // bind
    if(bind(socketDesc, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Error! Bind failed.\n");
        return;
    }
    printf("Bind has been done.\n");

    // set listening for connections from clients
    listen(socketDesc, 3);

    // accept incoming connections form clients
    printf("Waiting for incoming connections from clients.\n");
    int socketAddressSize = sizeof(struct sockaddr_in);
    int newSocket, *newSocketPointer;
    struct sockaddr_in client;
    while((newSocket = accept(socketDesc, (struct sockaddr *)&client, (socklen_t*)&socketAddressSize)))
    {
        printf("Connection accepted.\n");
        newSocketPointer = (int*)malloc(1);
        *newSocketPointer = newSocket;
        if(!createConnectionHandler(newSocketPointer)){
            printf("Error! Cannot create thread handler for client.\n");
            return;
        }

    }

    if(newSocket < 0)
    {
        printf("Error! Accept has been failed.\n");
    }
}

void TutorLinux::end()
{

}

bool TutorLinux::createConnectionHandler(int* socket)
{
    pthread_t thread;
    if(pthread_create(&thread, NULL, handleConnection, (void*)socket) < 0)
    {
        printf("Error! Cannot create thread to handle connection.\n");
        return false;
    }
    return true;
}

void* TutorLinux::handleConnection(void *socketDesc)
{
    int socket = *(int*)socketDesc;
    char clientMessage[BUFFER_SIZE], *serverMessage;
    int readSize;

    serverMessage = "Good afternoon, my favorite student, what do you want?\n";
    write(socket, serverMessage, strlen(serverMessage));

    while((readSize = recv(socket, clientMessage, BUFFER_SIZE, 0)) > 0)
    {
        printf("%s\n", clientMessage);
        //serverMessage = "Server has been received client message.\n";
        write(socket, clientMessage, strlen(clientMessage));
        memset(&clientMessage, 0, sizeof(clientMessage));                           // clear clientMessage string
    }

    if(readSize == 0)
    {
        cout << "Client has been disconnected.\n" << endl;
        fflush(stdout);
    }
    if(readSize == -1)
    {
        cout << "Reading client message has been failed.\n" << endl;
        fflush(stdout);
    }

    free(socketDesc);
}

