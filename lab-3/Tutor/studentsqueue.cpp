#include "studentsqueue.h"

StudentsQueue::StudentsQueue() : Queue()
{}

StudentsQueue::~StudentsQueue()
{}

void StudentsQueue::addToEnd(int value)
{
    queue.push_back(value);
}

int StudentsQueue::popFromBegin()
{
    int first = queue.at(0);
    queue.erase(queue.begin());
    return first;
}

void StudentsQueue::remove(int value)
{
    int index = 0;
    for(auto &i : queue)
    {
        index++;
        if(i == value)
        {
            queue.erase(queue.begin() + index - 1);
        }
    }
}

void StudentsQueue::print()
{
    int id = 1;
    if(queue.size() > 0){
        printf("\nCurrent queue of students:\n");
        for(auto &i : queue)
        {
            printf("queue_id #%d, student_id #%d.\n", id, i);
            id++;
        }
        printf("\n");
    }
}

