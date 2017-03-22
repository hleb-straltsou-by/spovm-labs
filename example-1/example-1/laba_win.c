#include "headers.h"

void CreateSignal(struct Data *data)
{
    data->count = 0;
    HANDLE Event = CreateEvent(NULL, FALSE, FALSE, "MyEvent");

    if (Event)
        SetEvent(Event);
    else
        exit(0);
}

void CreateNewProcess(char *path, struct Data *data, struct Stack **stack)
{

    char *numberCh;
    numberCh = (char*)malloc(10);
    sprintf(numberCh, "%d", size(*stack));

    char *str = NULL;
    str = (char*)malloc(sizeof(char)* 100);
    strcpy(str, path);

    strcat(str, " ");
    strcat(str, "Number_of_process:");
    strcat(str, numberCh);

    STARTUPINFO stInfo;
    PROCESS_INFORMATION prInfo;

    ZeroMemory(&stInfo, sizeof(STARTUPINFO));
    stInfo.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, str, NULL, NULL, FALSE, 0, NULL, NULL, &stInfo, &prInfo))
    {
        exit(0);
    }


    struct Data data_pr;
    data_pr.prInfo = prInfo;

    push(*&stack, data_pr);
}

void CloseProcess(struct Stack **stack, struct Data *data, int code)
{
    HANDLE Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, "MyEvent");

    if (Event == NULL)
        exit(0);

    WaitForSingleObject(Event, INFINITE);
    if (code==0){
    TerminateProcess((*stack)->hand, 0);
    pop(*&stack);

    SetEvent(Event);
    }
    else if (code==1){
        while (size(*stack) != 0)
    {
        TerminateProcess((*stack)->hand, 0);
        pop(*&stack);
    }
    system("cls");
    }
}

void PrintProcesses(char **argv, struct Data *data)
{
    HANDLE Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, "MyEvent");
    while (1)
    {
        WaitForSingleObject(Event, INFINITE);

        printf("%s\n\n", argv[1]);

        SetEvent(Event);
        Sleep(1000);
    }
}
