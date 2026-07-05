#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <Shlwapi.h>
#include <iostream>
#include <fstream>

LPSTR DLL_PATH;
// #define DLL_PATH "ColorDll.dll"
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

    // Create Process SUSPENDED
    PROCESS_INFORMATION pi;
    STARTUPINFOA Startup;
    ZeroMemory(&Startup, sizeof(Startup));
    ZeroMemory(&pi, sizeof(pi));
    // get the command line argument of the current process
    //LPSTR lpCmdLine = GetCommandLineA();
    if (argc < 2) {
        log_file <<"Usage: ./ClientInjector.exe <dll_path>" << endl;
        return 1;
    }

    char cmd_line[] = "client.exe DMSG";
    
    DLL_PATH = (LPSTR)argv[1];

    log_file << "Opening process: " << cmd_line << endl;
    
    if (CreateProcessA(NULL, cmd_line, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &Startup, &pi) == FALSE) {
        log_file << "Couldn't open process: " << cmd_line << endl;
        return 1;
    }

    if (!(dllInjector(DLL_PATH, pi.dwProcessId))) {
        log_file << "couldnt inject dll" << endl;
        return 1;
    }

    Sleep(1000); // Let the DLL finish loading
    ResumeThread(pi.hThread);
    log_file << "Injected dll successfully" << endl;
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

    remoteString = (LPVOID)VirtualAllocEx(pHandle, NULL, strlen(DLL_PATH) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(pHandle, (LPVOID)remoteString, dllpath, strlen(dllpath), NULL);
    if (NULL == CreateRemoteThread(pHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)remoteLoadLib, (LPVOID)remoteString, NULL, NULL)) {
        return false;
    }
    CloseHandle(pHandle);

    return true;
}