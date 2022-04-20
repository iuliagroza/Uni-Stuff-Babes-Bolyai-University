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
    ; Additions, subtractions (byte) - 4
    a3 db 3
    b3 db 2
    c3 db 4
    d3 db 7

    ; Additions, subtractions (byte) - 19
    a4 db 10
    b4 db 23
    c4 db 11
    d4 db 17

    ; Additions, subtractions (word) - 4
    a5 dw 122
    b5 dw 101
    c5 dw 209
    d5 dw 110

    ; Additions, subtractions (word) - 19
    a6 dw 500
    b6 dw 309
    c6 dw 100
    d6 dw 699

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; Additions, subtractions (byte) - 4: (a-b)+(c-b-d)+d = (3-2)+(4-2-7)+7 = 1-5+7 = 3
        mov eax, 0      ; EAX = 0
        mov ecx, 0      ; ECX = 0
        mov al, [a3]    ; AL = a3
        sub al, [b3]    ; AL = AL - b3
        mov cl, [c3]    ; CL = c3
        sub cl, [b3]    ; CL = CL - b3
        sub cl, [d3]    ; CL = CL - d3
        add ax, cx      ; AX = AX + CX
        add ax, [d3]    ; AX = AX + d3
        
        ; Additions, subtractions (byte) - 19: d-(a+b)-c = 17-(10+23)-11 = 17-33-11 = -16-11 = -27
        mov eax, 0      ; EAX = 0
        mov ebx, 0      ; EBX = 0
        mov al, [d4]    ; AL = d4
        mov bl, [a4]    ; BL = a4
        add bx, [b4]    ; BX = BX + b4
        sub ax, bx      ; AX = AX - BX
        sub ax, [c4]    ; AX = AX - c4
        
        ; Additions, subtractions (word) - 4: (b+b)-c-(a+d) = (101+101)-209-(122+110) = 202-209-232 = -7-232 = -239
        mov eax, 0      ; EAX = 0
        mov ebx, 0      ; EBX = 0
        mov ax, [b5]    ; AX = b5
        add eax, [b5]   ; EAX = EAX + b5
        sub eax, [c5]   ; EAX = EAX - c5
        mov bx, [a5]    ; BX = a5
        add ebx, [d5]   ; EBX = EBX + d5
        sub eax, ebx    ; EAX = EAX - EBX
        
        ; Additions, subtractions (word) - 19: b+a-(4-d+2)+c+(a-b) = 309+500-(4-699+2)+100+(500-309) = 809-(-695+2)+100+191 = 809-(-693)+100+191 = 1502+100+191 = 1602+191 = 1793
        mov eax, 0      ; EAX = 0
        mov ebx, 0      ; EBX = 0
        mov ax, [b6]    ; AX = b6
        add eax, [a6]   ; EAX = EAX + a6
        mov bx, 4       ; BX = 4
        sub ebx, [d6]   ; EBX = EBX - d6
        add ebx, 2      ; EBX = EBX + 2
        sub eax, ebx    ; EAX = EAX - EBX
        add eax, [c6]   ; EAX = EAX + c6
        mov bx, [a6]    ; BX = a6
        sub ebx, [b6]   ; EBX = EBX - b6
        add eax, ebx    ; EAX = EAX + EBX 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
