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
    A db 2, 1, 3, -3, -4, 2, -6
    B db 4, 5, -5, 7, -6, -2, 1
    len2 equ $-A
    R times len2 dw 0 ; -4, -6, -6, -2

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; 19. Two byte strings A and B are given. Obtain the string R that contains only the even negative elements of the two strings.
        mov ecx, 0
        mov ecx, len2               ; move the length of R in ECX
        mov esi, 0                  ; initialize ESI (iterator of A and B) with 0
        mov edi, 0                  ; initialize EDI (iterator of R) with 0
        
        jecxz eF                    ; stop the loop if ECX reaches 0
        
        fI
        cmp [A+esi], byte 0         
        jl cont                     ; if element is negative
        inc esi
        jmp ex
        
        cont:
        test [A+esi], byte 01h      
        jnz eN                      ; if element is odd
        
        mov bl, [A+esi]
        mov [R+edi], bl
        inc edi                     ; a new element was added
        inc esi
        jmp ex
        
        eN:
        inc esi
        
        ex:
        
        loop fI 
        eF
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
