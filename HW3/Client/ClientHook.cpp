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


using std::ofstream;
using std::endl;
using std::wstring;
using std::wofstream;
ofstream log_file("log.txt");

LPVOID real_return_address;
LPVOID recv_buffer;

void __stdcall decode_string(char* buf) {
    int read_idx = 0;
    int write_idx = 0;

    bool is_high_nibble = true;
    unsigned char high_nibble = 0;

    while (buf[read_idx] != '\0') {
        unsigned char current_nibble = 0;
        char c = buf[read_idx];

        if (c == 'A') {
            current_nibble = 1;
            read_idx += 1;
        }
        else if (c == 'J') {
            current_nibble = 10;
            read_idx += 1;
        }
        else if (c == 'Q') {
            current_nibble = 11;
            read_idx += 1;
        }
        else if (c == 'K') {
            current_nibble = 12;
            read_idx += 1;
        }
        else if (c >= '0' && c <= '9') {
            if (buf[read_idx + 1] != '\0' && buf[read_idx + 2] != '\0' &&
                (buf[read_idx + 1] == '+' || buf[read_idx + 1] == '-')) {
                int val1 = c - '0';
                char op = buf[read_idx + 1];
                int val2 = buf[read_idx + 2] - '0';

                if (op == '+') {
                    current_nibble = val1 + val2;
                }
                else if (op == '-') {
                    current_nibble = val1 - val2;
                }
                read_idx += 3;
            }
            else {
                current_nibble = c - '0';
                read_idx += 1;
            }
        }
        else {
            read_idx += 1;
            continue;
        }

        if (is_high_nibble) {
            high_nibble = current_nibble;
            is_high_nibble = false;
        }
        else {
            char decoded_char = (high_nibble << 4) | current_nibble;
            buf[write_idx] = decoded_char;
            write_idx++;
            is_high_nibble = true;
        }
    }

    buf[write_idx] = '\0';
}

__declspec(naked) void after_recv_hook()
{
    __asm {
        push recv_buffer
        call decode_string // calling decode function
        jmp real_return_address // jump back to the original retune address
    }
}
__declspec(naked) void pre_recv_hook()
{
    __asm {
        push eax
        mov eax, [esp+4]
        mov real_return_address, eax 

        mov eax, OFFSET after_recv_hook
        mov [esp+4] ,eax
        mov eax, [esp+12]
        mov recv_buffer , eax
        pop eax
    }
}




void setHook() {

    LPVOID f;
    HMODULE h = GetModuleHandle(L"WS2_32.dll");
    CHAR JmpOpcode[6] = "\xE9\x90\x90\x90\x90";
    DWORD lpProtect = 0;
    LPVOID JumpTo;

    if (h == NULL) {
        log_file << "WS2_32.dll: couldnt get handle" << endl;
        return;
    }
    f = GetProcAddress(h, "recv");

    if (f == NULL) {
        log_file << "recv: couldnt get function" << endl;
        return;
    }

    log_file << "recv: setting hook" << endl;
    // calculate relative jump to DrawTextHook from f, add 5 cause its from eip after the execution
    JumpTo = (LPVOID)((char*)&pre_recv_hook - ((char*)f));
    VirtualProtect((char*)f - 5, 0x7, PAGE_EXECUTE_READWRITE, &lpProtect);
    memcpy(JmpOpcode + 1, &JumpTo, 0x4); // preparing the jmp to the hook
    memcpy((char*)f - 5, &JmpOpcode, 5);  // writing to f-5 the jmp
    *(char*)f = 0xEB; // writing to f the jmp -7
    *((char*)(f)+1) = 0xf9;
    VirtualProtect((char*)f - 5, 0x7, PAGE_EXECUTE_READ, &lpProtect);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
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