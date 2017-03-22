#include "headers.h"

int main(int argc, char *argv[])
{
    struct Stack *stack = NULL;
    struct Data data;

    if (argc == 1)
    {
        CreateSignal(&data);

        while (1)
        {
            switch (_getch())
            {
            case '+':
                CreateNewProcess(argv[0], &data, &stack);
                break;
            case '-':
                if (size(stack) != 0)
                    CloseProcess(&stack, &data,0);
                break;
            case 'q':
                    CloseProcess(&stack, &data,1);
                return 0;
                break;
            }
        }
    }
    else
        PrintProcesses(argv, &data);

    return 0;
}

