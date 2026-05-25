.intel_syntax noprefix
.globl _main

_main:
        push    ebp
        mov     ebp, esp
        
############### Find LoadLibrary function ###############

        push 0x0       		# pushing null
        push 0x41797261		# pushing A,y,r,a
        push 0x7262694c		# pushing r,b,i,L
        push 0x64616f4c		# pushing d,a,o,L
        push esp            # push pointer for "LoadLibraryA"

        call FindFunction   # call FindFunction("LoadLibraryA")
        add esp, 0x14       # clear stack

############### Load msvcrt library using LoadLibraryA ###############

        push 0x00006c6c		# pushing null,l,l
        push 0x642e7472		# pushing d,#,t,r
        push 0x6376736d		# pushing c,v,s,m
        push esp

        call eax            # call LoadLibrary("msvcrt.dll")
        add esp, 0x0C       # clear stack (note arguments are cleared already)

############### Find GetProcAddress function - used to get specific function from load library ###############

        push eax            # store module handle for msvcrt
        push 0x00007373		# pushing null,s,s
        push 0x65726464		# pushing e,r,d,d
        push 0x41636f72		# pushing A,c,o,r
        push 0x50746547		# pushing P,t,e,G
        push esp            # push pointer for "GetProcAddress"

        call FindFunction   # call FindFunction("GetProcAddress")
        add esp, 0x14       # clear stack
        pop ebx             # restore module handle for msvcrt
        mov esi, eax

############### Getting printf function pointer ###############

        push 0x00006674		# pushing null,null,f,t
        push 0x6e697270		# pushing n,i,r,p
        push esp            # push pointer for "printf"
        push ebx            # push module handle for msvcrt

        call esi            # call GetProcAddress(msvcrt, "printf")
        add esp, 0x08       # clear stack (note arguments are cleared already)
        mov edi, eax        # call edi for calling printf

############### Getting scanf function pointer ###############

        push 0x00000066     # Pushing null, null, null, 'f'
        push 0x6E616373     # Pushing 'n', 'a', 'c', 's'
        push esp            # push pointer for "scanf"
        push ebx            # push module handle for msvcrt

        call esi            # call GetProcAddress(msvcrt, "scanf")
        add esp, 0x08       # clear stack (note arguments are cleared already)
        mov esi, eax        # call esi for calling scanf

###############  core logic ###############
        sub     esp, 100
        mov     DWORD PTR [ebp-12], 0
        mov     DWORD PTR [ebp-16], 0
        mov     DWORD PTR [ebp-20], 0
        mov     DWORD PTR [ebp-24], 0
        mov     DWORD PTR [ebp-28], 0
.L7:
        lea     eax, [ebp-92]
        push    0x00007325	    # pushing null,s,%
        mov     edx, esp
        push    eax             # push line
        push    edx             # push pointer for "%s"
        call    esi             # call scanf("%s, line)
        add     esp, 0x0C
        cmp     eax, 1
        sete    al
        test    al, al
        je      .L2
        movzx   eax, BYTE PTR [ebp-92]
        cmp     al, 114
        jne     .L3
        movzx   eax, BYTE PTR [ebp-91]
        cmp     al, 111
        jne     .L3
        movzx   eax, BYTE PTR [ebp-90]
        cmp     al, 97
        jne     .L3
        movzx   eax, BYTE PTR [ebp-89]
        cmp     al, 100
        jne     .L3
        movzx   eax, BYTE PTR [ebp-88]
        test    al, al
        jne     .L3
        add     DWORD PTR [ebp-12], 1
        add     DWORD PTR [ebp-16], 1
        jmp     .L4
.L3:
        movzx   eax, BYTE PTR [ebp-92]
        cmp     al, 115
        jne     .L5
        movzx   eax, BYTE PTR [ebp-91]
        cmp     al, 101
        jne     .L5
        movzx   eax, BYTE PTR [ebp-90]
        cmp     al, 116
        jne     .L5
        movzx   eax, BYTE PTR [ebp-89]
        cmp     al, 116
        jne     .L5
        movzx   eax, BYTE PTR [ebp-88]
        cmp     al, 108
        jne     .L5
        movzx   eax, BYTE PTR [ebp-87]
        cmp     al, 101
        jne     .L5
        movzx   eax, BYTE PTR [ebp-86]
        cmp     al, 109
        jne     .L5
        movzx   eax, BYTE PTR [ebp-85]
        cmp     al, 101
        jne     .L5
        movzx   eax, BYTE PTR [ebp-84]
        cmp     al, 110
        jne     .L5
        movzx   eax, BYTE PTR [ebp-83]
        cmp     al, 116
        jne     .L5
        movzx   eax, BYTE PTR [ebp-82]
        test    al, al
        jne     .L5
        add     DWORD PTR [ebp-12], 1
        add     DWORD PTR [ebp-16], 1
        add     DWORD PTR [ebp-20], 1
        add     DWORD PTR [ebp-24], 1
        jmp     .L4
.L5:
        movzx   eax, BYTE PTR [ebp-92]
        cmp     al, 99
        jne     .L6
        movzx   eax, BYTE PTR [ebp-91]
        cmp     al, 105
        jne     .L6
        movzx   eax, BYTE PTR [ebp-90]
        cmp     al, 116
        jne     .L6
        movzx   eax, BYTE PTR [ebp-89]
        cmp     al, 121
        jne     .L6
        movzx   eax, BYTE PTR [ebp-88]
        test    al, al
        jne     .L6
        add     DWORD PTR [ebp-24], 2
        add     DWORD PTR [ebp-28], 3
        jmp     .L4
.L6:
        movzx   eax, BYTE PTR [ebp-92]
        cmp     al, 100
        jne     .L7
        movzx   eax, BYTE PTR [ebp-91]
        cmp     al, 101
        jne     .L7
        movzx   eax, BYTE PTR [ebp-90]
        cmp     al, 118
        jne     .L7
        movzx   eax, BYTE PTR [ebp-89]
        cmp     al, 101
        jne     .L7
        movzx   eax, BYTE PTR [ebp-88]
        cmp     al, 108
        jne     .L7
        movzx   eax, BYTE PTR [ebp-87]
        cmp     al, 111
        jne     .L7
        movzx   eax, BYTE PTR [ebp-86]
        cmp     al, 112
        jne     .L7
        movzx   eax, BYTE PTR [ebp-85]
        cmp     al, 109
        jne     .L7
        movzx   eax, BYTE PTR [ebp-84]
        cmp     al, 101
        jne     .L7
        movzx   eax, BYTE PTR [ebp-83]
        cmp     al, 110
        jne     .L7
        movzx   eax, BYTE PTR [ebp-82]
        cmp     al, 116
        jne     .L7
        movzx   eax, BYTE PTR [ebp-81]
        test    al, al
        jne     .L7
        add     DWORD PTR [ebp-24], 1
        add     DWORD PTR [ebp-28], 1
        add     DWORD PTR [ebp-20], 1
.L4:
        jmp     .L7
.L2:
        push    0x0000000A     # pushing null,null,null,\n
        push    0x64323025	    # pushing d,2,0,%
        push    0x20643230	    # pushing  ,d,2,0
        push    0x25206432	    # pushing %, ,d,2
        push    0x30252064	    # pushing 0,%, ,d
        push    0x32302520	    # pushing 2,0,%, 
        push    0x64323025		# pushing d,2,0,%
        mov     edx, esp

        push    DWORD PTR [ebp-28]      # push ore
        push    DWORD PTR [ebp-24]      # push grain
        push    DWORD PTR [ebp-20]      # push wool
        push    DWORD PTR [ebp-16]      # push brick
        push    DWORD PTR [ebp-12]      # push wood
        push    edx                     # push pointer for "%02d %02d %02d %02d %02d\n"
        call    edi                     # call printf("%02d %02d %02d %02d %02d\n", wood, brick, wool, grain, ore)
        add     esp, 0x34
        mov     eax, 0
        leave
        ret

FindFunction:       # placeholder for search_kernel32
