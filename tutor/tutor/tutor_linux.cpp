#ifdef __linux
#include "tutor_linux.h"

#define FIFO_NAME "/tmp/named_pip"
#define BUFFER_SIZE 1024

Tutor_linux::Tutor_linux(vector<string> subjects) : Tutor()
{
    this->subjects = subjects;
}

Tutor_linux::~Tutor_linux()
{}

bool Tutor_linux::connectToPipe(string pipePath)
{
    this->pipe = fopen(pipePath.c_str(), "r");
    if(this->pipe == NULL)
    {
        cout << "Error! Tutor cannot connect to pipe!" << endl;
        return false;
    }
    cout << "Tutor has been connected to pipe." << endl;
    return true;
}

void Tutor_linux::checkLabs()
{
    int labsCount = parseInteger();
    cout << "Tutor check " << labsCount << " labs" << endl;
    for(int i = 0; i < labsCount; i++)
    {
        int symbolCount = parseInteger();
        string lab = getStringFromPipe(symbolCount);
        compareWithTutorSubjects(lab);
    }
}

void Tutor_linux::closeConnectionToPipe()
{
    fclose(this->pipe);
    unlink(FIFO_NAME);
}

int Tutor_linux::parseInteger()
{
    char symbol = 'q';
    char buffer[Tutor_linux::MAX_SYMBOL_COUNT];
    int i;
    for(i = 0; i < Tutor_linux::MAX_SYMBOL_COUNT && symbol != ' ' && !feof(pipe); i++)
    {
        symbol = fgetc(pipe);
        buffer[i] = symbol;
    }
    int symbolCount = 0, multiplier = 1;
    i -= 2;
    for(i; i >= 0; i--){
        symbolCount += (buffer[i] - 48) * multiplier;
        multiplier *= 10;
    }
    return symbolCount;
}

string Tutor_linux::getStringFromPipe(int size)
{
    char readingBuffer[BUFFER_SIZE];
    fgets(readingBuffer, size+1, pipe);
    fseek(pipe, -1, SEEK_CUR);
    return string(readingBuffer);
}

bool Tutor_linux::compareWithTutorSubjects(string lab)
{
    for(int i = 0; i < subjects.size(); i++)
    {
        if(lab == subjects[i])
        {
            cout << lab + " lab is successfully taken! Good job student!" << endl;
            return true;
        }
    }
    cout << lab + " lab is not taken! Illegal subject of lab!" << endl;
    return false;
}

#endif
