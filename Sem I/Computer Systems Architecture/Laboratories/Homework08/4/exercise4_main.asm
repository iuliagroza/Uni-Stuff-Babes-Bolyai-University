bits 32

global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

extern compare

segment data use32 class=data
    S db '10100111b', '01100011b', '110b', '101011b'
    len equ $-S
    format db '%c', 0
    comma db ', ', 0
    comma_format db '%s', 0
    copy1 resd 1
    copy2 resd 1

segment code use32 class=code
    start:
    ; A string containing n binary representations on 8 bits is given as a character string.
    ; Obtain the string containing the numbers corresponding to the given binary representations.
        mov ecx, len
        mov esi, S
        
        jecxz endFor
        
        forIndex:
            mov [copy1], ecx
            mov eax, 0
            lodsb
            mov [copy2], eax
            
            push eax
            push format
            call [printf]
            add esp, 4*2
            
            mov eax, [copy2]
            push eax
            call compare
            
            cmp eax, 0
            jne print
            jmp endNow
            
            print:
                cmp dword [copy1], 1
                je endNow
                push comma
                push comma_format
                call [printf]
                add esp, 4*2
                
                endNow:
                    mov ecx, [copy1]
        loop forIndex
        
        endFor:
            push dword 0
            call [exit]