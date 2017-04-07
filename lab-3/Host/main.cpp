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

struct processInfo {
    pid_t pid;
};

#define FIFO_NAME "/tmp/named_pipe"
#define SEMAPHORE_NAME "/my_named_semaphore"

#endif

#include <iostream>
using namespace std;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main()
{

    #ifdef __linux

    char buffer[BUFFER_SIZE] = "command line arguments";

    // creating tutor process
    struct processInfo processInfo_2;
    pid_t pid_2 = fork();
    processInfo_2.pid = pid_2;
    switch(pid_2) {
    case -1: {
        cout << "Error, can not create tutor process" << endl;
        return 0;
    }
    case 0: {
        cout << "Tutor process has been created" << endl;
        cout << "Tutor PID: " << getpid() << endl;
        cout << "Host PID: " << getppid() << endl;
        execlp("/usr/bin/xterm", "xterm", "-e", "/home/gleb/spovm/labs/lab-1/lab-3/build-Tutor-Desktop-Debug/Tutor", buffer, NULL);
        cout << "After execlp" << endl;
        break;
    }
    default: {
        cout << "Host process" << endl;
        cout << "Tutor PID: " << processInfo_2.pid << endl;
        cout << "Host PID: " << getpid() << endl;
        break;
    }
   }

    sleep(2);

    struct processInfo processInfo_1;                   // declare structure to store info of student process
    // creating students processes
    for(int i = 0; i < 2; i++)
    {
        pid_t pid_1 = fork();                           // creating of new daughter process
        processInfo_1.pid = pid_1;
        switch(pid_1) {
            case -1: {
                cout << "Error, can not create student process" << endl;
                return 0;
            }
            case 0: {
                cout << "Student process has been created" << endl;
                cout << "Student PID: " << getpid() << endl;
                cout << "Host PID: " << getppid() << endl;
                execlp("/usr/bin/xterm", "xterm", "-e", "/home/gleb/spovm/labs/lab-1/lab-3/build-Student-Desktop-Debug/Student", buffer, NULL);
                cout << "After execlp" << endl;
                break;
            }
            default: {
                cout << "Host process" << endl;
                cout << "Student PID: " << processInfo_1.pid << endl;
                cout << "Host PID: " << getpid() << endl;
                break;
            }
        }
    }

    #endif
}

