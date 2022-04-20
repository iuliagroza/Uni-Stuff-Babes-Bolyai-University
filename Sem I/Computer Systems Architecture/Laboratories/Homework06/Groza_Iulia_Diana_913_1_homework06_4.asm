bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s db 5, 25, 55, 127
    len equ $-s
    d times len db 0 ; 101, 11001, 110111, 1111111 -> 2, 3, 5, 7
    

segment code use32 class=code
    start:
        ;4. A byte string s is given. Build the byte string d such that every byte d[i] is equal to the count of ones in the corresponding byte s[i] of s.
        mov esi, s                  ; move s into DS:ESI
        mov edi, d                  ; move d into ES:EDI
        cld                         ; parse s fron left to right
        mov ecx, len                ; move the length of s in ECX
        
        jecxz endFor                ; the loop is stopped when ecx reaches 0
        
        forIndex
            lodsb
            mov ebx, 0              ; this is where we store the number of set bits
            mov edx, 0              ; compare register
            
            compute:
                cmp al, 0
                je done
                mov edx, eax            
                shr al, 1           ; we push all the bits one place to the right, bits at position 1 will be "pushed out of the byte"
                and edx, 1          ; bitmaking 
                cmp edx, 0
                jz compute          ;if the found value is a zero we can skip the inc of the count register
                inc bl
                jmp compute
            done:
            
            mov al, bl
            stosb                   ; move the result to d[i]
        loop forIndex
        endFor
        
        push dword 0
        call [exit]