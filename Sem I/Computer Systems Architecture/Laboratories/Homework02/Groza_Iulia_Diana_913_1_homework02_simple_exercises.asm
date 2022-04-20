bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Simple exercises - 4 
    a1 db 5
    b1 db 6

    ; Simple exercises - 19
    a2 dw 12
    b2 dw 4

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; Simple exercises - 4: 5-6
        mov eax, 0      ; EAX = 0
        mov al, [a1]    ; AL = a1
        sub al, [b1]    ; AL = AL - b1
        
        ; Simple exercises - 19: 12/4
        mov eax, 0      ; EAX = 0
        mov ecx, 0      ; ECX = 0
        mov edx, 0      ; EDX = 0
        mov ax, [a2]    ; AX = a2
        mov cx, [b2]    ; CX = b2
        div cx          ; AX = DX:AX / CX, DX = DX:AX % CX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
