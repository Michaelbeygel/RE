.intel_syntax noprefix
dice_hook:
    mov dword ptr [ebp+8], 7;

    // Restore the stolen bytes
    mov eax, dword ptr [ebp+8];
    cmp eax, 7;

    // placeholder for future modification
    jmp 0x01010101;