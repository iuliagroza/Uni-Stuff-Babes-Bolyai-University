bits 32

global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

%include "exercise19_module.asm"

segment data use32 class=data
    S db "acegik", 0        ; first string
    T db "bdfhjl", 0        ; second string
    len equ $-T             ; length of the strings (they are of equal length)
    sol resb 100            ; solution string
    format db "%s  ", 0     ; format used to display the solution (notice that we have whitespaces so we can take into consideration the edge case of
                            ; empty strings


segment code use32 class=code
    start:
        ; Two strings of characters of equal length are given. Calculate and display the results of the interleaving of the letters, for the two possible interlaces (the letters of the first string in an even position, respectively the letters from the first string in an odd positions). Where no character exist in the source string, the ‘ ’ character will replace it in the destination string.
        
        ; preparing the parameters to call .merge(len, T, S, sol)
        push dword sol
        push dword S
        push dword T
        push dword len
        call merge
        
        ; printing the first merged string (first string being placed on even positions)
        push sol
        push format
        call [printf]
        add esp, 4*2
        
        ; preparing the parameters to call .merge(len, S, T, sol)
        push dword sol
        push dword T
        push dword S
        push dword len
        call merge
        
        ; printing the second merged string (first string being placed on odd positions)
        push sol
        push format
        call [printf]
        add esp, 4*2
        
        push dword 0
        call [exit]

