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
    a2 dw 0010_1110_0010_0000b
    b2 dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; 19. Given the word A, compute the doubleword B as follows:
        ; the bits 28-31 of B have the value 1;
        ; the bits 24- 25 and 26-27 of B are the same as the bits 8-9 of A
        ; the bits 20-23 of B are the invert of the bits 0-3 of A ;
        ; the bits 16-19 of B have the value 0
        ; the bits 0-15 of B are the same as the bits 16-31 of B.
        mov eax, 0
        or eax, 1111_0000_0000_0000_0000_0000_0000_0000b    ;Setting bits 28-31 from B to 1
        
        mov ebx, 0
        mov bx, [a2]                                        ; Isolating bits 8-9 of A
        and bx, 0000_0011_0000_0000b
        mov ecx, 0
        mov cl, 14
        ror ebx, cl                                         ; Rotating (8-0)+(32-26) = 14 positions to the right
        or eax, ebx
        
        ror ebx, 2                                          
        or eax, ebx                                         ; Bits 24-25
        
        mov ebx, 0
        mov bx, [a2]
        not bx                                              ; Inverting the value of A
        and bx, 0000_0000_0000_1111b                        ; Isolating bits 0-3 of AL
        mov ecx, 0
        mov cl, 12                                          ; Rotating 32-20=12 positions to the right
        ror ebx, cl
        or eax, ebx
        
        and eax, 1111_1111_1111_0000_1111_1111_1111_1111b   ; Setting bits 16-19 of B to 0
        
        mov ebx, 0
        mov ebx, eax                                        ; Isolating bits 16-31
        and ebx, 1111_1111_1111_1111_0000_0000_0000_0000b
        mov ecx, 0
        mov cl, 16
        ror ebx, cl
        or eax, ebx                                         ; Bits 0-15
        
        mov [b2], eax
        
        ; A = 0010_1110_0010_0000
        ; B = 1111_1010_1111_0000_1111_1010_1111_0000
        ;      F    A     F   0    F    A    F    0
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
