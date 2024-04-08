#pragma once
#include <iostream>
#include <iterator>
#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet")

#define DEFAULT_BUFLEN 4096

using namespace std;

void get_buf(const char* url, char (&copied_buf)[DEFAULT_BUFLEN]);
