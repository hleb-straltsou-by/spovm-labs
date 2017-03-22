#include "headers.h"

char _getch()
{
    struct termios oldItem, newItem;
    char ch;
    tcgetattr(0, &oldItem);
    newItem = oldItem;
    newItem.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newItem);
    ch = getchar();

    tcsetattr(0, TCSANOW, &oldItem);
    return ch;
}
void CreateNewProcess(char *path, struct Data *data, struct Stack **stack)
{
    switch(data->pid = fork())
    {
        case -1:
            perror("fork error...");
            exit(1);
        case 0:
        {
            int i = 1, k = size(*stack) / 10;

            for(i = 1; k != 0; i++)
                k = k / 10;

            char *params;
            params = (char *)malloc((i+1) * sizeof(char));
            params[i+1] = '\0';

            for(int num = i, number = size(*stack); num > 0; num--, number /= 10)
                params[num - 1] = number % 10 + '0';

            char *cmd[3] = {"/home/Alexandr/spolab2/lab2", params, 0};
            execv("/home/Alexandr/spolab2/lab2", cmd);
        }
        default:
        {
            push(&*stack, *data);
        }
            break;
    }
}

void CloseProcess(struct Stack **stack, struct Data *data, int code)
{
                semop(data->semid, &(data->mybuff), 1);
    if (code == 0){
        kill((*stack)->pid, SIGKILL);
        pop(&*stack);
    }
    if (code == 1){
        semop(data->semid, &(data->mybuff1), 1);
        while (size(*stack) != 0)
        {
            kill((*stack)->pid, SIGKILL);
            pop(&*stack);
        }
        printf("\033[2J\033[0;0f");
        return;
    }
}


void CreateSignal(struct Data *data)
{
    data->key = ftok("/home/Alexandr/spolab2/lab2", 0);
    data->semid = semget(data->key, 1, 0666 | IPC_CREAT);
    semctl(data->semid, 0, SETVAL, (int)0);
    data->mybuff.sem_num = 0;

    data->mybuff1.sem_num = 0;
    data->mybuff1.sem_op = 1;
}

void PrintProcesses(char **argv, struct Data *data)
{
    while(1)
    {
        semop(data->semid, &(data->mybuff), 1);
        semop(data->semid, &(data->mybuff1), 1);
        usleep(100000);
        printf("Process number %s\n", argv[1]);
        data->mybuff1.sem_op = -1;
        semop(data->semid, &(data->mybuff1), 1);
        data->mybuff1.sem_op = 1;
    }
}

