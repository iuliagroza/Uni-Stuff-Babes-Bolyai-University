bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
; Multiplications, divisions - 4
a5 dw 309
b5 db 3
c5 db 6
d5 db 4
e5 dd 1000
x5 dq 33000

; Multiplications, divisions - 19
a6 db 7
b6 db 9
c6 db 11
e6 dd 8009
x6 dq 109054

segment code use32 class=code
start:
    ; Multiplications, divisions - 4 - (a*2+b/2+e)/(c-d)+x/a = (309*2+3/2+1000)/(6-4)+33000/309 = (618+1+1000)/2+106 = (619+1000)/2+106 =
    ;                                                        = 1619/2+106 = 809+106 = 915
    ; Unsigned
    mov eax, 0          ; EAX = 0
    mov al, 2           ; AL = 2
    mul word [a5]       ; AX = AX * a5
    mov ebx, eax        ; EBX = EAX
    mov eax, 0          ; EAX = 0
    mov al, [b5]        ; AL = b5
    mov ecx, 0          ; ECX = 0
    mov cl, 2           ; CL = 2
    div cl              ; AL = AH:AL / CL, AH = AH:AL % CL
    mov ah, 0           ; AH = 0
    add bx, ax          ; BX = BX + AX
    add ebx, [e5]       ; EBX = EBX + e5
    mov eax, ebx        ; EAX = EBX
    mov ebx, 0          ; EBX = 0
    mov bl, [c5]        ; BL = c5
    sub bl, byte [d5]   ; BL = BL - d5
    mov edx, 0          ; EDX = 0
    div ebx             ; EAX = EDX:EAX / EBX, EDX = EDX:EAX % EBX
    mov ebx, eax        ; EBX = EAX
    mov eax, [x5]       ; EAX = x5
    mov edx, 0          ; EDX = 0
    div word [a5]       ; AX = DX:AX / a5, DX = DX:AX % a5
    add eax, ebx        ; EAX = EAX + EBX
    
    ; Signed
    mov eax, 0          ; EAX = 0
    mov al, 2           ; AL = 2
    imul word [a5]      ; EAX = EAX * a5
    mov ebx, eax        ; EBX = EAX
    mov ax, 0           ; AX = 0
    mov al, [b5]        ; AL = b5
    mov ecx, 0          ; ECX = 0
    mov cl, 2           ; CL = 2
    mov edx, 0          ; EDX = 0
    idiv cl             ; AL = AH:AL / CL, AH = AH:AL % CL
    mov ah, 0           ; AH = 0
    adc bx, ax          ; BX = BX + AX + CF
    adc ebx, [e5]       ; EBX = EBX + e5 + CF
    mov eax, ebx        ; EAX = EBX
    mov ebx, 0          ; EBX = 0
    mov bl, [c5]        ; BL = c5
    sbb bl, byte [d5]   ; BL = BL - d5 - CF
    mov edx, 0          ; EDX = 0
    idiv ebx            ; EAX = EDX:EAX / EBX, EDX = EDX:EAX % EBX
    mov ebx, eax        ; EBX = EAX
    mov eax, [x5]       ; EAX = x5
    mov edx, 0          ; EDX = 0
    idiv word [a5]      ; AX = DX:AX / a5, DX = DX:AX % a5
    adc eax, ebx        ; EAX = EAX + EBX + CF
    
    ; Multiplications, divisions - 19 - (a+a+b*c*100+x)/(a+10)+e*a = (7+7+9*11*100+109054)/(7+10)+8009*7 = (14+99*100+109054)/17+56063 = 
    ;                                                              = (14+9900+109054)/17+56063 = (9914+109054)/17+56063 = 118968/17+56063 = 6998+56063 =
    ;                                                              = 63061
    ; Unsigned
    mov eax, 0      ; EAX = 0
    mov edx, 0      ; EDX = 0
    mov al, 100     ; AL = 100
    mul byte [b6]   ; AL = AL * b6
    mov ebx, 0      ; EBX = 0
    mov bl, [c6]    ; BL = c6
    mul bx          ; AX = AX * BX
    add al, [a6]    ; AL = AL + a6
    add al, [a6]    ; AL = AL + a6
    add eax, [x6]   ; EAX = EAX + x6
    mov ebx, 0      ; EBX = 0
    mov bl, 10      ; BL = 10
    add bl, [a6]    ; BL = BL + a6
    div ebx         ; EAX = EDX:EAX / EBX, EDX = EDX:EAX % EBX
    mov ebx, eax    ; EBX = EAX
    mov eax, 0      ; EAX = 0
    mov eax, [e6]   ; EAX = e6
    mov ecx, 0      ; ECX = 0
    mov cl, [a6]    ; CL = a6
    mul ecx         ; EAX = EAX * ECX
    add eax, ebx    ; EAX = EAX + EBX
    
    ; Multiplications, divisions - 19 - (a+a+b*c*100+x)/(a+10)+e*a = (7+7+9*11*100+109054)/(7+10)+8009*7 = (14+99*100+109054)/17+56063 = 
    ;                                                              = (14+9900+109054)/17+56063 = (9914+109054)/17+56063 = 118968/17+56063 = 6998+56063 =
    ;                                                              = 63061
    ; Signed
    mov eax, 0      ; EAX = 0
    mov edx, 0      ; EDX = 0
    mov al, 100     ; AL = 100
    imul byte [b6]  ; AL = AL * b6
    mov ebx, 0      ; EBX = 0
    mov bl, [c6]    ; BL = c6
    imul bx         ; AX = AX * BX
    adc al, [a6]    ; AL = AL + a6 + CF
    adc al, [a6]    ; AL = AL + a6 + CF
    adc eax, [x6]   ; EAX = EAX + x6 + CF
    mov ebx, 0      ; EBX = 0
    mov bl, 10      ; BL = 10
    adc bl, [a6]    ; BL = BL + a6 + CF
    idiv ebx        ; EAX = EDX:EAX / EBX, EDX = EDX:EAX % EBX
    mov ebx, eax    ; EBX = EAX
    mov eax, 0      ; EAX = 0
    mov eax, [e6]   ; EAX = e6
    mov ecx, 0      ; ECX = 0
    mov cl, [a6]    ; CL = a6
    imul ecx        ; EAX = EAX * ECX
    adc eax, ebx    ; EAX = EAX + EBX + CF
    
    push dword 0
    call [exit]