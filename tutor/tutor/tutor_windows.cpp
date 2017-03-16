#ifdef WIN32 || WIN64
#include "tutor_windows.h"
#include<iostream>
#include <windows.h>
using namespace std;

Tutor_windows::Tutor_windows()
{
    subjects.insert("spovm");
    subjects.insert("cpp");
    subjects.insert("apc");
    subjects.insert("shem");

}

Tutor_windows::~Tutor_windows()
{
}

void Tutor_windows::checkLabs() {
    ReleaseSemaphore(hSemaphore, 1, NULL);
    cout << hSemaphore << endl;

    if (!ConnectNamedPipe(hNamedPipe, (LPOVERLAPPED)NULL))
    {
        // some errors
        cout << "some errors" << endl;
    }
    else
    {
        WaitForSingleObject(hCheckLabsEvent, INFINITE);

        cout << "I get event about labs" << endl;

        if (!readFromPipe())
        {
            cerr << "Error Read " << endl;
            return;
        }
        //write ans
        if (!writeInPipeNumber())
        {
            cerr << "Error write" << endl;
            return;
        }
        SetEvent(hAnsTutorEvent);
        Sleep(10000);
    }

}

// "\\\\.\\pipe\\demo_Pipe"
bool Tutor_windows::connectToPipe(string pipePath)
{
    char c;
    hNamedPipe = CreateNamedPipe(
        pipePath.c_str(), // èìÿ êàíàëà
        PIPE_ACCESS_DUPLEX, // ÷èòàåì èç êàíàëà
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // ñèíõðîííàÿ ïåðåäà÷à ñîîáùåíèé
        100,// ìàêñèìàëüíîå êîëè÷åñòâî ýêçåìïëÿðîâ êàíàëà
        10000, // ðàçìåð âûõîäíîãî áóôåðà ïî óìîë÷àíèþ
        10000, // ðàçìåð âõîäíîãî áóôåðà ïî óìîë÷àíèþ
        INFINITE, // êëèåíò æäåò ñâÿçü áåñêîíå÷íî äîëãî
        (LPSECURITY_ATTRIBUTES)NULL // çàùèòà ïî óìîë÷àíèþ
    );

    if (hNamedPipe == INVALID_HANDLE_VALUE)
    {
        cerr << "Creation of the named pipe failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any char to finish server: ";
        cin >> c;
        return false;
    }
    else
    {
        cout << "Pipe is sozdan" << endl;
        return true;
    }
}


void Tutor_windows::closeConnectionToPipe()
{
    CloseHandle(hNamedPipe);
    CloseHandle(hSemaphore);
}


bool Tutor_windows::setSemaphore(string name) {
    hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT(name.c_str()));
    if (hSemaphore == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}


bool Tutor_windows::setCheckLabsEvent(string name) {
    hCheckLabsEvent = OpenEvent(SEMAPHORE_ALL_ACCESS, FALSE, name.c_str());
    if (hCheckLabsEvent == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

bool Tutor_windows::setAnsTutorEvent(string name) {
    hAnsTutorEvent = OpenEvent(SEMAPHORE_ALL_ACCESS, FALSE, name.c_str());
    if (hCheckLabsEvent == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

bool Tutor_windows::readFromPipe()
{
    if (!readFromPipeNumber())
    {
        cerr << "Error read from pipe muber" << endl;
        return false;
    }
    cout << "size = " << size << endl;
    if (!readFromPipeString())
    {
        cerr << "Error read from pipe string" << endl;
        return false;
    }
    cout << "readFromPipe() is correctly" << endl;
    return true;
}


bool Tutor_windows::readFromPipeNumber()
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
    size = nData;
    cout << "input number is correctle" << endl;
    return true;
}
/*
bool Tutor_windows::readFromPipeString()
{
    string str = "";
    for (int i = 0; i < size; i++) {

        DWORD dwBytesRead;
        if (!ReadFile(
            hNamedPipe, // äåñêðèïòîð êàíàëà
            &str, // àäðåñ áóôåðà äëÿ ââîäà äàííûõ
            sizeof(str), // êîëè÷åñòâî ÷èòàåìûõ áàéòîâ
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

        cout << "sizeof(str) = " << sizeof(str) << "    dwBytes = "  << dwBytesRead << endl;
        cout << "readFromPipeString() is correctly" << size << endl;
        if (subjects.count(str) == 0) {
            cout << "this subject i ne vedu" << endl;
            return false;
        }
    }
    return true;
}
*/

bool Tutor_windows::readFromPipeString()
{

    char *data = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
    labOk = true;
    for (int i = 0; i < size; i++) {

        DWORD dwBytesRead;
        if (!ReadFile(
            hNamedPipe, // äåñêðèïòîð êàíàëà
            data, // àäðåñ áóôåðà äëÿ ââîäà äàííûõ
            sizeof(char)*MAX_STR_SIZE, // êîëè÷åñòâî ÷èòàåìûõ áàéòîâ
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

        cout << string(data) << "sizeof(str) = " << sizeof(data)*MAX_STR_SIZE << "    dwBytes = " << dwBytesRead << endl;
        cout << "readFromPipeString() is correctly" << size << endl;
        puts(data);
        if (subjects.count(string(data)) == 0) {
            cout << "this subject i ne vedu" << endl;
            labOk = false;
        }
    }
    free(data);
    return true;
}

bool Tutor_windows::writeInPipeNumber()
{
    int ansTutor;
    if (labOk)
    {
        ansTutor = 1;
    }
    else
    {
        ansTutor = 0;
    }
    DWORD dwBytesWritten;
    if (!WriteFile(
        hNamedPipe, // äåñêðèïòîð êàíàëà
        &ansTutor, // äàííûå
        sizeof(ansTutor), // ðàçìåð äàííûõ
        &dwBytesWritten, // êîëè÷åñòâî çàïèñàííûõ áàéòîâ
        NULL // ñèíõðîííàÿ çàïèñü
    ))
    {
        // îøèáêà çàïèñè
        cerr << "Writing to the named pipe failed: " << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any char to finish the client: ";
        CloseHandle(hNamedPipe);
        return false;
    }
    return true;
}
#endif
