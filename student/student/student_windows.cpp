#ifdef WIN32 || WIN64
#include "student_windows.h"

Student_windows::Student_windows()
{}


Student_windows::~Student_windows()
{}

bool Student_windows::completeLab(vector<string> infoLab) {
    cout << hSemaphore << endl;
    if (WaitForSingleObject(hSemaphore, 10000) != WAIT_TIMEOUT)
    {
        if (!writeInPipe(infoLab))
        {
            cout << "Write in pipe Error!" << endl;
            cerr << "Write in pipe Error!" << endl;
            return false;
        }
        SetEvent(hCheckLabsEvent);// govorim tutory chto ny zapisali v pipe
        cout << "wait..." << endl;
        WaitForSingleObject(hAnsTutorEvent, INFINITE);
        if (!readFromPipe())
        {
            cerr << "Read ans from pipe Error!" << endl;
            return false;
        }
    }
    else
    {
        cout << "Now tutor are busy" << endl;
        return false;
    }
    return true;
}


bool Student_windows::connectToPipe(string pipePath)
{
    hNamedPipe = CreateFile(
        pipePath.c_str(),
        PIPE_ACCESS_DUPLEX,
        FILE_SHARE_READ | PIPE_WAIT | FILE_SHARE_WRITE, // ðàçðåøàåì òîëüêî çàïèñü â êàíàë
        (LPSECURITY_ATTRIBUTES)NULL, // çàùèòà ïî óìîë÷àíèþ
        OPEN_EXISTING, // îòêðûâàåì ñóùåñòâóþùèé êàíàë
        0, // àòðèáóòû ïî óìîë÷àíèþ
        (HANDLE)NULL);
    cout << "norm" << endl;
    // Åñëè âîçíèêëà îøèáêà, âûâîäèì åå êîä è
    // çàâåðøàåì ðàáîòó ïðèëîæåíèÿ
    if (hNamedPipe == INVALID_HANDLE_VALUE)
    {
        fprintf(stdout, "CreateFile: Error %ld\n",
            GetLastError());
        _getch();
        return false;
    }
    else
    {
        cout << "connect to Tutor Pipe" << endl;
        return true;
    }
    cout << "norm" << endl;
    // Âûâîäèì ñîîáùåíèå î ñîçäàíèè êàíàëà


}


void Student_windows::closeConnectionToPipe()
{}

bool Student_windows::setSemaphore(string name) {
    hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT(name.c_str()));
    if (hSemaphore == NULL)
    {
        cout << "symaphore ==null" << endl;
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}


bool Student_windows::setCheckLabsEvent(string name) {
    hCheckLabsEvent = OpenEvent(SEMAPHORE_ALL_ACCESS, FALSE, name.c_str());
    if (hCheckLabsEvent == NULL)
    {
        cout << "heckLabsEvent ==null" << endl;
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

bool Student_windows::setAnsTutorEvent(string name) {
    hAnsTutorEvent = OpenEvent(SEMAPHORE_ALL_ACCESS, FALSE, name.c_str());
    if (hAnsTutorEvent == NULL)
    {
        cout << "AnsTutorEvent ==null" << endl;
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
bool Student_windows::writeInPipe(vector<string> labs)
{
    if (!writeInPipeNumber(labs.size()))
    {
        cout << labs.size();
        cerr << "error writeInPipe(vector<string>) Number" << endl;
        return false;
    }
    for each (string lab  in labs)
    {
        if (!writeInPipeString(lab))
        {
            cerr << "error writeInPipeStringr" << endl;
            return false;
        }
    }
    cout << "writeInPipe is seccesfull" << endl;
    return true;
}

bool Student_windows::writeInPipeNumber(int number) {
    int data = number;
    DWORD dwBytesWritten;
    if (!WriteFile(
        hNamedPipe, // äåñêðèïòîð êàíàëà
        &data, // äàííûå
        sizeof(data), // ðàçìåð äàííûõ
        &dwBytesWritten, // êîëè÷åñòâî çàïèñàííûõ áàéòîâ
        NULL // ñèíõðîííàÿ çàïèñü
    ))
    {
        // îøèáêà çàïèñè
        cerr << "Writing to the named pipe failed: " << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any char to finish the client: ";
        return false;
    }
    cout << "number vvod is correctle" << endl;
    return true;
}

bool Student_windows::writeInPipeString(string str) {
    DWORD dwBytesWritten;
    const char *mas = str.c_str();
    char *arr = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
    int i = 0;
    for (; i < sizeof(mas); i++)
    {
        arr[i] = mas[i];
    }
    arr[i] = '\0';


    if (!WriteFile(
        hNamedPipe, // äåñêðèïòîð êàíàëà
        arr, // äàííûå
        sizeof(char)*MAX_STR_SIZE , // ðàçìåð äàííûõ
        &dwBytesWritten, // êîëè÷åñòâî çàïèñàííûõ áàéòîâ
        NULL // ñèíõðîííàÿ çàïèñü
    ))
    {
        // îøèáêà çàïèñè
        cerr << "Writing to the named pipe failed: " << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any char to finish the client: ";
        return false;
    }
    return true;
}

bool Student_windows::readFromPipe()
{
    int nData = 0;
    DWORD dwBytesRead;
    if (!ReadFile(
        hNamedPipe, // äåñêðèïòîð êàíàëà
        &nData, // àäðåñ áóôåðà äëÿ ââîäà äàííûõ
        sizeof(nData), // êîëè÷åñòâî ÷èòàåìûõ áàéòîâ
        &dwBytesRead, // êîëè÷åñòâî ïðî÷èòàííûõ áàéòîâ
        (LPOVERLAPPED)NULL // ïåðåäà÷à äàííûõ ñèíõðîííàÿ
    ))
    {
        cerr << "Data reading from the named pipe failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hNamedPipe);
        cout << "Press any char to finish the server: ";
        return false;
    }
    // âûâîäèì ïðî÷èòàííûå äàííûå íà êîíñîëü
    cout << "The number " << nData << " was read by the server" << endl;
    if (nData == 1) {
        cout << "God job boy!Labs is complete" << endl;
    }
    else
    {
        cout << "Bad boy!labs is not complete" << endl;
    }
    return true;
}
#endif
