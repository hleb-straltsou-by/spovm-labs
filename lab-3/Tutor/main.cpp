#include <iostream>
#include "tutorlinux.h"

using namespace std;

int main()
{
    cout << "Tutor proccess has been lunched." << endl;

    TutorLinux tutor;

    tutor.start();

    return 0;
}

