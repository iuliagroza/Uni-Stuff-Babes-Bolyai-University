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
    ; Additions, subtractions - Unsigned representation - 4
    a1 db 70
    b1 dw 290
    c1 dd 68001
    d1 dq 17034200

    ; Additions, subtractions - Unsigned representation - 19
    a2 db 2
    b2 dw 300
    c2 dd 70002
    d2 dq 18000500

    ; Additions, subtractions - Signed representation - 4
    a3 db 5
    b3 dw 275
    c3 dd 100640
    d3 dq 17100000

    ; Additions, subtractions - Signed representation - 19
    a4 db 3
    b4 dw 257
    c4 dd 69000
    d4 dq 3020

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; Additions, subtractions - Unsigned representation - 4 - (a-b)+(c-b-d)+d = (70-290)+(68001-290-17034200)+17034200 = -220+(67711-17034200)+17034200 = -220-16966489+17034200 = -16,966,709+17034200 = 67491
        mov eax, 0      ; EAX = 0
        mov al, [a1]    ; AL = a1
        mov ebx, 0      ; EBX = 0
        mov bx, [b1]    ; BX = b1
        sub eax, ebx    ; EAX = EAX - EBX
        mov ebx, 0      ; EBX = 0
        mov ebx, [c1]   ; EBX = c1
        sub bx, [b1]    ; BX = BX - b1
        sub ebx, [d1]   ; EBX = EBX - d1
        add eax, ebx    ; EAX = EAX - EBX
        add eax, [d1]   ; EAX = EAX + d1
        
        ; Additions, subtractions - Unsigned representation - 19 - (d+d)-(a+a)-(b+b)-(c+c) = (18000500+18000500)-(2+2)-(300+300)-(70002+70002) = 
        ;                                                                                  = 36001000-4-600-140004 = 36000996-600-140004 =
        ;                                                                                  = 36000396-140004 = 35860392
        mov eax, 0      ; EAX = 0
        mov eax, [d2]   ; EAX = d2
        add eax, [d2]   ; EAX = EAX + d2
        mov ebx, 0      ; EBX = 0
        mov bl, [a2]    ; BL = a2
        add bl, [a2]    ; BL = BL + a2
        sub eax, ebx    ; EAX = EAX - EBX
        mov bl, 0       ; BL = 0
        mov bx, [b2]    ; BX = b2
        add bx, [b2]    ; BX = BX + b2
        sub eax, ebx    ; EAX = EAX - EBX
        mov bx, 0       ; BX = 0
        mov ebx, [c2]   ; EBX = c2
        add ebx, [c2]   ; EBX = EBX + c2
        sub eax, ebx    ; EAX = EAX - EBX
        
        ; Additions, subtractions - Signed representation - 4 - (b+b)-c-(a+d) = (275+275)-100640-(5+17100000) = 550-100640-17100005 = -100090-17100005 =
        ;                                                                     = -17200095
        mov eax, 0      ; EAX = 0
        mov ax, [b3]    ; AX = b3
        adc ax, [b3]    ; AX = AX + b3 + CF
        mov ebx, 0      ; EBX = 0
        mov bl, [a3]    ; BL = a3
        adc ebx, [d3]   ; EBX = EBX + d3 + CF
        sbb eax, [c3]   ; EAX = EAX - c3 - CF
        sub eax, ebx    ; EAX = EAX - EBX
        
        ; Additions, subtractions - Signed representation - 19 - (d+a)-(c-b)-(b-a)+(c+d) = (3020+3)-(69000-257)-(257-3)+(69000+3020) = 3023-68743-254+
        ;                                                                                +72020 = -65720-254+72020 = -65974+72020 = 6046
        mov eax, 0      ; EAX = 0
        mov eax, [d4]   ; EAX = d4
        adc al, [a4]    ; AL = AL + a4 + CF
        mov ebx, 0      ; EBX = 0
        mov ebx, [c4]   ; EBX = c4
        sbb bx, [b4]    ; BX = BX - b4 - CF
        sbb eax, ebx    ; EAX = EAX - EBX - CF
        mov ebx, 0      ; EBX = 0
        mov bx, [b4]    ; BX = b4
        mov ecx, 0      ; ECX = 0
        mov cl, [a4]    ; CL = a4
        sub bx, cx      ; BX = BX - CX
        sbb eax, ebx    ; EAX = EAX - EBX - CF
        mov bx, 0       ; BX = 0
        mov ebx, [c4]   ; EBX = c4
        adc ebx, [d4]   ; EBX = EBX + d4 + CF
        adc eax, ebx    ; EAX = EAX + EBX + CF
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
