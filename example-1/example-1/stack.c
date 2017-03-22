#include "headers.h"

int size(const struct Stack *head) {

    int size = 0;
    while (head) {
        size++;
        head = head->next;
    }

    return size;
}

void push(struct Stack **head, struct Data data) {

    struct Stack *tmp = (struct Stack *)malloc(sizeof(struct Stack));
    if (tmp == NULL)
        exit(1);
    tmp->next = *head;

    #if defined(_WIN32) || defined(_WIN64)
    tmp->hand = data.prInfo.hProcess;

    #else
    tmp->pid = data.pid;

    #endif
    *head = tmp;
}

void pop(struct Stack **head) {

    struct Stack *out;

    if (*head == NULL)
        exit(1);

    out = *head;
    *head = (*head)->next;

    free(out);
}
