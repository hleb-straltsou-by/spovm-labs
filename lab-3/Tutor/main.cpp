#ifdef WIN32 || WIN64
#include"TutorWindows.h"
#include <set>
#endif

#ifdef __linux
#include <iostream>
#include "studentsqueue.h"
#include "tutorlinux.h"
#endif

using namespace std;

int parseStringToInt(char *stringNumber);

int main(int argc, char **argv)
{
    printf("Tutor proccess has been lunched.\n");

    int period = parseStringToInt(argv[1]);

    Tutor *tutor;

    #ifdef __linux
    tutor = new TutorLinux;
    #endif

    #ifdef WIN32 || WIN64
    tutor = new TutorWindows;
    #endif

    tutor->start(period);

    return 0;
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


