#ifndef STACK_H
#define STACK_H

#endif // STACK_H

struct Stack {
    #if defined(_WIN32) || defined(_WIN64)
        HANDLE hand;
    #else
        pid_t pid;
    #endif
        struct Stack *next;
};

int size(const struct  Stack *);
void push(struct Stack **, struct Data);
void pop(struct Stack **);
