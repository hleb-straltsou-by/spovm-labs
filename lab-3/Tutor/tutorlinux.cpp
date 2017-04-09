#include "tutorlinux.h"

pthread_mutex_t TutorLinux::mutex;

vector<string> TutorLinux::subjects;

StudentsQueue TutorLinux::studentsQueue;

TutorLinux::TutorLinux() : Tutor()
{
    vector<string> subjects;
    subjects.push_back("spovm");
    subjects.push_back("cpp");
    this->subjects = subjects;
}

TutorLinux::~TutorLinux()
{}

void TutorLinux::start(int period)
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

    // start logger
    pthread_t thread;
    int *periodPointer = (int*)malloc(1);
    *periodPointer = period;
    if(pthread_create(&thread, NULL, logStudents, (void*)periodPointer) < 0)
    {
        printf("Error! Cannot create thread to log active clients.\n");
        return;
    }
    printf("Logger of students has been created.\n");

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
{}

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
    char clientMessage[BUFFER_SIZE], serverMessage[BUFFER_SIZE];
    int readSize;
    string reply;

    TutorLinux::studentsQueue.addToEnd(socket);

    pthread_mutex_lock(&TutorLinux::mutex);

    reply = "Good afternoon, my favorite student, what labs do you want to complete?\n";
    strcpy(serverMessage, reply.c_str());
    write(socket, serverMessage, strlen(serverMessage));

    sleep(2);

    while((readSize = recv(socket, clientMessage, BUFFER_SIZE, 0)) > 0)
    {
        string lab = clientMessage;
        if(checkLab(lab))
        {
            reply = lab + " lab is successfully taken! Good job, student!";
            strcpy(serverMessage, reply.c_str());
            write(socket, serverMessage, strlen(serverMessage));
        } else {
            reply = lab + " lab is not taken! Illegal name of subject!";
            strcpy(serverMessage, reply.c_str());
            write(socket, serverMessage, strlen(serverMessage));
        }
        memset(&clientMessage, 0, sizeof(clientMessage));                           // clear clientMessage string
    }

    if(readSize == 0)
    {
        printf("Client has been disconnected.\n");
        fflush(stdout);
    }
    if(readSize == -1)
    {
        printf("Reading client message has been failed.\n");
        fflush(stdout);
    }

    free(socketDesc);

    TutorLinux::studentsQueue.remove(socket);

    pthread_mutex_unlock(&TutorLinux::mutex);
}

 bool TutorLinux::checkLab(string lab)
 {
     for(unsigned int i = 0; i < TutorLinux::subjects.size(); i++)
     {
         if(lab == TutorLinux::subjects[i])
         {
             return true;
         }
     }
     return false;
 }

void* TutorLinux::logStudents(void *period)
{
    int periodValue = *(int*)period;
    while(true)
    {
        sleep(periodValue);
        TutorLinux::studentsQueue.print();
    }
}
