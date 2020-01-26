# WinBackdoorLib
a simple module to create "reverse shell or backdoor" simply with Windows API


## Compile Payload :
  ### g++ backdoorlib.cpp reverse_powershell.cpp -o payload.exe -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -lwininet
