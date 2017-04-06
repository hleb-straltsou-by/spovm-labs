#include <iostream>
#include <studentlinux.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <fcntl.h>

using namespace std;

int main()
{
    cout << "Student process is lunched." << endl;

    sleep(2);

    StudentLinux student;

    if(!student.getConnection()){
        cout << "Error! Cannot connect to the server." << endl;
        return -1;
    }

    cout << student.readMessage();
    while(1){
        sleep(1);
        student.sendMessage("I'm student");
        cout << "Server reply: " << student.readMessage() << endl << endl;
    }

    cout << "Client has been successfully finish his work." << endl;
    return 0;
}

