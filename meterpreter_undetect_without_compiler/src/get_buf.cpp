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