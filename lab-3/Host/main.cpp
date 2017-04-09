#ifdef WIN32 || WIN64
#include"HostWindows.h"
#endif

#ifdef __linux
#include <unistd.h>		//fork, getpid, getppid, execve
#include <sys/types.h>	//pid_t
#include <time.h>		//ctime, time_t
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>    //mkfile
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include "host.h"
#include <sstream>
#include "hostlinux.h"
#endif

#include <iostream>

using namespace std;

#include <fcntl.h>

#define CLIENT_INITIAL_SIZE 3
#define BUFFER_SIZE 1024
#define DEFAULT_LOG_FREQUENCY 4
#define DEFAULT_CREATING_PERIODS 7

int parseStringToInt(char *stringNumber);

int main(int argc, char** argv)
{
    int logFrequency;
    int studentsCreatingPeriod;

    if(argc <= 1){
        printf("Illegal command line arguments. 1 - log frequency, 2 - period for creating students.\n");
        printf("Will be used defaul params:\nlog frequency: 4 seconds\nperiod for creating students: 5 seconds\n");
        logFrequency = DEFAULT_LOG_FREQUENCY;
        studentsCreatingPeriod = DEFAULT_CREATING_PERIODS;
    } else {
        logFrequency = parseStringToInt(argv[1]);
        studentsCreatingPeriod = parseStringToInt(argv[2]);
    }

    Host *host;

    #ifdef __linux
    host = new HostLinux;
    #endif

    #ifdef WIN32 || WIN64
    host = new HostWindows;
    #endif

    host->createTutor(logFrequency);

    sleep(2);

    for(int i = 0; i < CLIENT_INITIAL_SIZE; i++)
    {
        host->createStudent();
    }

    host->listenUserCommand();
    host->createStudentWithPeriod(studentsCreatingPeriod);

}

int parseStringToInt(char *stringNumber)
{
    if(stringNumber == NULL)
    {
        return 0;
    }
    int length = strlen(stringNumber), result = 0, k = 1;
    for(int i = length - 1; i >= 0; i--)
    {
        result += ((int)(stringNumber[i]) - 48) * k;
        k *= 10;
    }
    return result;
}
