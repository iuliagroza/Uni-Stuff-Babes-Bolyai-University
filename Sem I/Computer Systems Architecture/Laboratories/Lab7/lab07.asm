bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data

segment code use32 class=code
    start:
        mov al, 128 
        cbw 
        mov bl,2 
        div bl 
        push dword 0
        call [exit]