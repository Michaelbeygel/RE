#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <Shlwapi.h>
#include <iostream>
#include <fstream>
#include <string>

#define DLL_PATH "Client.dll" 
#define true 1
#define false 0

using std::ofstream;
using std::endl;
using std::wstring;
using std::wofstream;
ofstream log_file("Injector_log.txt");

BOOL dllInjector(const char* dllpath, DWORD pID);

int main(int argc, char** argv)
{
    PROCESS_INFORMATION pi;
    STARTUPINFOA Startup;
    ZeroMemory(&Startup, sizeof(Startup));
    ZeroMemory(&pi, sizeof(pi));
    Startup.cb = sizeof(Startup);

    if (argc < 2) {
        log_file << "Usage: ./ClientInjector.exe <path_to_client.exe>" << endl;
        return 1;
    }

    std::string clientPath = argv[1];
    
    std::string cmd_line_str = clientPath + " DMSG";
    log_file << "Opening process: " << cmd_line_str << endl;

    char* cmd_line = new char[cmd_line_str.length() + 1];
    strcpy(cmd_line, cmd_line_str.c_str());

    if (CreateProcessA(NULL, cmd_line, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &Startup, &pi) == FALSE) {
        log_file << "Couldn't open process: " << cmd_line << endl;
        delete[] cmd_line;
        return 1;
    }

    if (!(dllInjector(DLL_PATH, pi.dwProcessId))) {
        log_file << "couldnt inject dll" << endl;
        TerminateProcess(pi.hProcess, 1);
        delete[] cmd_line;
        return 1;
    }

    Sleep(1000);
    ResumeThread(pi.hThread);
    log_file << "Injected dll successfully" << endl;
    
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    delete[] cmd_line;
    
    return 0;
}

BOOL dllInjector(const char* dllpath, DWORD pID)
{
    HANDLE pHandle;
    LPVOID remoteString;
    LPVOID remoteLoadLib;

    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

    if (!pHandle) {
        log_file << "couldnt open proccess with perms" << endl;
        return false;
    }

    remoteLoadLib = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    remoteString = (LPVOID)VirtualAllocEx(pHandle, NULL, strlen(dllpath) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(pHandle, (LPVOID)remoteString, dllpath, strlen(dllpath), NULL);
    if (NULL == CreateRemoteThread(pHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)remoteLoadLib, (LPVOID)remoteString, NULL, NULL)) {
        CloseHandle(pHandle);
        return false;
    }
    CloseHandle(pHandle);

    return true;
}