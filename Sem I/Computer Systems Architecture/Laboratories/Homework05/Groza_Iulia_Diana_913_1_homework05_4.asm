bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    S1 db 1, 2, 3, 4
    len equ $-S1
    S2 db 5, 6, 7, 8
    D times len db 0 ; 6, -4, 10, -4
    

segment code use32 class=code
    start:
        ; 4. Two byte strings S1 and S2 are given, having the same length. Obtain the string D in the following way: each element found on the even positions of D is the sum of the corresponding elements from S1 and S2, and each element found on the odd positions of D is the difference of the corresponding elements from S1 and S2.
        mov ecx, 0
        mov ecx, len      ; move the length of D in ecx
        mov esi, 0        ; initialize ESI (the iterator) with 0
        
        jecxz endFor      ; the loop is stopped when ecx reaches 0
        
        forIndex
        test esi, 01h     ; check if we are on an even position
        jz even_number
        
        mov bl, [S1+esi]  ; case of odd position
        sub bl, [S2+esi]
        mov [D+esi], bl
        inc esi           ; increment esi
        jmp odd_number    
        
        even_number:      ; case of even position
        mov bl, [S1+esi]
        add bl, [S2+esi]
        mov [D+esi], bl
        inc esi
        
        odd_number:
        
        loop forIndex
        endFor
        
        push dword 0
        call [exit]