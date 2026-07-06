
// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <Shlwapi.h>
#include <fstream>
#include <iostream>
#include <ios>
#include <string>
#include <stdlib.h>

using std::endl;
using std::ofstream;
using std::wofstream;
using std::wstring;
ofstream log_file("log.txt");

LPVOID real_func_address;
int len_override;
LPVOID strcmp_continue_func;

bool local_strcmp(const char* input, const char* target) {
    if (input == nullptr || target == nullptr) return false;
    while (*input != '\0' && *target != '\0') {
        if (*input != *target) return false;
        input++;
        target++;
    }
    return (*input == *target);
}

int __stdcall spoof_strcmp_logic(const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr) return 2;

    if (local_strcmp(str1, "NO SUCH CODE") || local_strcmp(str2, "NO SUCH CODE")) {
        return 1;
    }

    if (local_strcmp(str1, "ROBBER_CAPTURED") || local_strcmp(str2, "ROBBER_CAPTURED")) {
        return 0;
    }

    return 2;
}

__declspec(naked) void strcmp_Hook()
{
    __asm {
        // [esp+4] = str1, [esp+8] = str2
        mov eax, [esp + 4] 
        push eax
        mov eax, [esp + 12]
        push eax
        
        call spoof_strcmp_logic 

        cmp eax, 2
        je resume_normal_strcmp

        ret 

    resume_normal_strcmp:
        // Restore the stolen bytes from strcmp prologue
        mov edx, [esp + 4]
        mov ecx, [esp + 8]
        jmp strcmp_continue_func
    }
}

void setHook()
{

    LPVOID f;
    HMODULE h = GetModuleHandle(L"msvcrt.dll");
    CHAR JmpOpcode[7] = "\xE9\x90\x90\x90\x90\x90";
    DWORD lpProtect = 0;
    LPVOID JumpTo;

    if (h == NULL)
    {
        log_file << "couldnt get handle" << endl;
        return;
    }
    f = GetProcAddress(h, "strcmp");
    // alternatively, get the function address by offset:
    // f = (char*)h + offset_to_func
    if (f == NULL)
    {
        log_file << "couldnt get function" << endl;
        return;
    }

    // save the return address of f for jumping back
    real_func_address = f;
    len_override = 5; // nubmer of bytes to override, changes from function to function

    strcmp_continue_func = (char *)f + len_override + 3; // strcmp start with 2 cmd of 4 bytes each, so if we override first 5 we must add 3 when returning
    
    log_file << "setting hook" << endl;
    // calculate relative jump to strcmp_Hook from f, add 5 cause its from eip after the execution
    JumpTo = (LPVOID)((char *)&strcmp_Hook - ((char *)f + 5));
    memcpy(JmpOpcode + 1, &JumpTo, 0x4); // write the jump
    VirtualProtect((char *)f, 0x7, PAGE_EXECUTE_READWRITE, &lpProtect);
    memcpy((char *)f, &JmpOpcode, len_override);
    VirtualProtect((char *)f, 0x7, PAGE_EXECUTE_READ, &lpProtect);
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        setHook();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
