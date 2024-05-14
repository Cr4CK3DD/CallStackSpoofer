.code


Suppressor PROC
    ; Create fake stack frame

    mov r11, QWORD PTR [rsp + 28h]
    push QWORD PTR [r11 + 10h]
    push QWORD PTR [r11 + 8h]

    mov QWORD PTR [r11+18h],rcx
    mov QWORD PTR [r11+20h],rdx
    mov QWORD PTR [r11+28h],r8

    lea rcx, QWORD PTR [rsp + 28h]     
    lea rdx, QWORD PTR [rsp + 40h]
    mov r8, QWORD PTR [r11 + 30h] ; arguments size
    xor r10, r10

fix_args:
    mov rax, QWORD PTR [rdx + r10]
    mov QWORD PTR [rcx + r10], rax
    add r10, 8h
    cmp r10, r8
    jge call_api
    jmp fix_args
call_api:

    mov rcx, QWORD PTR [r11+18h]
    mov rdx, QWORD PTR [r11+20h]
    mov r8,  QWORD PTR [r11+28h]
    
    ; jump to api
    jmp QWORD PTR [r11]
    nop
    ret
Suppressor ENDP

END


