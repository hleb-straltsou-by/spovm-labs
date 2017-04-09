#ifndef MOVINGQUEUE_H
#define MOVINGQUEUE_H

#include "queue.h"
#include <iostream>
#include <vector>

using namespace std;

class StudentsQueue : public Queue
{
private:

    vector<int> queue;

public:

    StudentsQueue();

    ~StudentsQueue();

    void addToEnd(int value);

    int popFromBegin();

    void remove(int value);

    void print();

};

#endif // MOVINGQUEUE_H
