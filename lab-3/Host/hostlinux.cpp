#include "hostlinux.h"

vector<string> HostLinux::commands;

HostLinux::HostLinux() : Host()
{
    HostLinux::commands.push_back("create student");
    HostLinux::commands.push_back("delete student ");
}

HostLinux::~HostLinux()
{}

void HostLinux::createStudent()
{
    struct processInfo processInfo;
    pid_t pid = fork();
    processInfo.pid = pid;
    switch(pid) {
        case -1: {
            printf("Error! Cannot create student process.\n");
            return;
        }
        case 0: {
            execlp("/usr/bin/xterm", "xterm", "-e", "/home/gleb/spovm/labs/lab-1/lab-3/build-Student-Desktop-Debug/Student", NULL, NULL);
            break;
        }
        default: {
            break;
        }
    }
}

void HostLinux::createStudentWithPeriod(int period)
{
    while(true)
    {
        sleep(period);
        createStudent();
    }
}

void HostLinux::createTutor(int logFrequency)
{
    char* args = parseIntToString(logFrequency);

    struct processInfo processInfo;
    pid_t pid = fork();
    processInfo.pid = pid;
    switch(pid) {
    case -1: {
        printf("Error! Cannot create tutor process.\n");
        return;
    }
    case 0: {
        execlp("/usr/bin/xterm", "xterm", "-e", "/home/gleb/spovm/labs/lab-1/lab-3/build-Tutor-Desktop-Debug/Tutor", args, NULL);
        break;
    }
    default: {
        break;
    }
   }
}

void HostLinux::listenUserCommand()
{
    pthread_t thread;
    int *arg = (int*)malloc(1);
    if(pthread_create(&thread, NULL, handleUserCommands, (void*)arg) < 0)
    {
        printf("Error! Cannot create thread to listen users commands.\n");
        return;
    }
}

void* HostLinux::handleUserCommands(void *arg)
{
    printf("Available commands:\n");
    printf("create student\n");
    printf("delete student student_id\n");
    char command[BUFFER_SIZE];
    while(true)
    {
        cin.getline(command, BUFFER_SIZE);
        string stringCommand = command;
        if(commands.at(0).compare(command) == 0){
            printf("CREATE OK");
            HostLinux::createStudentStatic();
        } else if(commands.at(1).compare(stringCommand.substr(0, 15)) == 0){
            printf("DELETE OK\n");
            string studentId = stringCommand.substr(15);
            cout << studentId << endl;
            deleteStudent(5);
        }
    }
}

char* HostLinux::parseIntToString(int number)
{
    stringstream strStream;
    strStream << number;
    string strNumber;
    strStream >> strNumber;
    char* str = (char*)malloc(BUFFER_SIZE);
    strcpy(str, strNumber.c_str());
    return str;
}

void HostLinux::createStudentStatic()
{
    struct processInfo processInfo;
    pid_t pid = fork();
    processInfo.pid = pid;
    switch(pid) {
        case -1: {
            printf("Error! Cannot create student process.\n");
            return;
        }
        case 0: {
            execlp("/usr/bin/xterm", "xterm", "-e", "/home/gleb/spovm/labs/lab-1/lab-3/build-Student-Desktop-Debug/Student", NULL, NULL);
            break;
        }
        default: {
            break;
        }
    }
}

void HostLinux::deleteStudent(int idStudent)
{}

