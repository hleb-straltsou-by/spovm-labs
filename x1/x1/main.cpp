#include <iostream>
#include <wait.h>		//wait
#include <unistd.h>		//fork, getpid, getppid, execve
#include <sys/types.h>	//pid_t
#include <sys/stat.h>   //mkfile, unlink
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

struct ProcessInfo{
    pid_t pid;
};

#define FIFO_NAME "/tmp/named_pip"

int main()
{

    mkfifo(FIFO_NAME, 0600);
    char buf[1024] = "xxx";
    cout << char(4 + 48);
    cout << " ";
    cout << buf << endl;
    char numbuf[2];
    numbuf[0] = char(7 + '0');
    numbuf[1] = '\0';
    cout << numbuf << endl;

    ProcessInfo studentProcessInfo;
    pid_t studentPid = fork();
    studentProcessInfo.pid = studentPid;
    switch(studentPid){
        case -1:{
            cout << "Error! Cannot initiate student process..." << endl;
            return 0;
        }
        case 0:{
            cout << "\nStudent process has been created." << endl;
            cout << "---------------------------------" << endl;
            cout << "**** Process info ****" << endl;
            cout << "Student pid: " << getpid() << endl;
            cout << "Parent pid: " << getppid() << endl;
            cout << "Before execv" << endl;
            char* const argv[2] = {"empty", NULL};  // argv must not be NULL
            execv("/home/gleb/spovm/lab-1/x2/build-x2-Desktop-Debug/x2", argv);
            cout << "After execv" << endl;
            break;
        }
        default:{
            cout << "Parent process." << endl;
            cout << "-----------------------------------" << endl;
            cout << "Student pid: " << studentProcessInfo.pid << endl;
            cout << "Parent pid: " << getpid() << endl;
            break;
        }
    }

    cout << "\n\nInitializing tutor process...\n" << endl;

    ProcessInfo tutorProcessInfo;
    pid_t tutorPid = fork();
    tutorProcessInfo.pid = tutorPid;
    switch(tutorPid){
        case -1:{
            cout << "Error! Cannot initiate student process..." << endl;
            return 0;
        }
        case 0:{
            cout << "\nTutor process has been created." << endl;
            cout << "---------------------------------" << endl;
            cout << "**** Process info ****" << endl;
            cout << "tutor pid: " << getpid() << endl;
            cout << "Parent pid: " << getppid() << endl;
            cout << "Before execv" << endl;
            char* const argv[2] = {"empty", NULL};  // argv must not be NULL
            execv("//home/gleb/spovm/lab-1/x3/build-x3-Desktop-Debug/x3", argv);
            cout << "After execv" << endl;
            break;
        }
        default:{
            cout << "Parent process." << endl;
            cout << "-----------------------------------" << endl;
            cout << "tutor pid: " << tutorProcessInfo.pid << endl;
            cout << "Parent pid: " << getpid() << endl;
            break;
        }
    }

    return 0;
}

