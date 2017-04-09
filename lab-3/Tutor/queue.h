#ifndef QUEUE_H
#define QUEUE_H

class Queue
{

public:

    Queue();

    ~Queue();

    virtual void addToEnd(int value) = 0;

    virtual int popFromBegin() = 0;

    virtual void remove(int value) = 0;

};

#endif // QUEUE_H
