bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 1, 4, 2, 5, 9, 4, 2, 4, 2, 5
    lena equ $-a
    b db 4, 2, 5
    lenb equ $-b
    sol times lena db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;19. Being given two strings of bytes, compute all positions where the second string appears as a substring in the first string.
        mov ecx, lena       ; store the length of a in ECX
        mov ebx, sol
        mov esi, a          ; move a in ED:ESI     
        mov edi, b          ; move b in ES:EDI
        cld                 ; parse s fron left to right
        
        jecxz eF
        
        fI
            solve: 
                cmpsb       ; compare the current value from a to the current value of b
                pushf       ; push the flags to the stack
                dec esi 
                dec edi 
                popf        ; pop the flags from the stack
                jne lng 
                inc edi     
            je solve 
            
            
            lng:            ; we check if the count from above is equal to the length of the substring
            mov eax, edi 
            sub eax, b      ; substract the starting memory address of b from EAX
            
            cmp eax, lenb   ; compare the current index for b to the length of b
            jne endL
            
            mov eax, esi 
            inc eax
            sub eax, a      ; substract the starting memory address of a from EAX
            sub eax, lenb   ; substract the length of b from EAX
            
            xchg ebx, edi   ; swap the contents of EBX and EDI
            stosb           ; store al into d
            xchg ebx, edi   
            
            mov edi, b ; if they are equal we reset the current index of b
            
            endL:
            inc esi 
        loop fI
        eF
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
