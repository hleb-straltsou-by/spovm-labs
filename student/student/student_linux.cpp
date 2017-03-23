#include "student_linux.h"

#define ZERO_CODE 48
#define BUFFER_SIZE 256

Student_linux::Student_linux() : Student()
{}

Student_linux::~Student_linux()
{}

bool Student_linux::connectToPipe(string pipePath)
{
    this->pipe = fopen(pipePath.c_str(), "w");
    if(this->pipe == NULL)
    {
        cout << "Error! Student cannot connect to pipe!" << endl;
        return false;
    }
    cout << "Student is connected to pipe." << endl;
    return true;
}

void Student_linux::completeLab(vector<string> labList)
{
    // writing labs count to pipe
    char numberBuffer[BUFFER_SIZE];
    numberBuffer[0] = char(labList.size() + ZERO_CODE);
    numberBuffer[1] = '\0';
    fputs(numberBuffer, this->pipe);
    fputs(" ", this->pipe);
    for(int i = 0; i < labList.size(); i++)
    {
        // writing lab size and its symbols to pipe
        numberBuffer[0] = char(labList[i].length() + ZERO_CODE);
        numberBuffer[1] = '\0';
        fputs(numberBuffer, this->pipe);
        fputs(" ", this->pipe);
        fputs(labList[i].c_str(), this->pipe);
        cout << "lab " + labList[i] << " is send!" << endl;
    }
}

void Student_linux::closeConnectionToPipe()
{
    fclose(this->pipe);
}
