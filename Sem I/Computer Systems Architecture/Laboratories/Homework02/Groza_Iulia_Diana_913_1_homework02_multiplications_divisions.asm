bits 32 ;asamblare și compilare pentru arhitectura de 32 biți
; definim punctul de intrare in programul principal
global start

; declaram functiile externe necesare programului nostru 
extern exit ; indicam asamblorului ca exit exista, chiar daca noi nu o vom defini
import exit msvcrt.dll  ; exit este o functie care incheie procesul, este definita in msvcrt.dll
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante

; segmentul de date in care se vor defini variabilele 
segment data use32 class=data
; Multiplications, divisions (d - word) - 4
a7 db 9
b7 db 13
d7 dw 109

; Multiplications, divisions (d - word) - 19
a8 db 29
b8 db 3
c8 db 19
d8 dw 500

; Multiplications, divisions (e, f, g, h - word) - 4
a9 db 3
b9 db 20
c9 db 2

; Multiplications, divisions (e, f, g, h - word) - 19
a10 db 7
b10 db 79
c10 db 21
e10 dw 311
f10 dw 299
g10 dw 700
h10 dw 100

a11 db -5

; segmentul de cod
segment code use32 class=code
start:
; ...  
    ; Multiplications, divisions (d - word) - 4: –a*a+2*(b-1)–d = -9*9+2*(13-1)-109 = -81+2*12-109 = -81+24-109 = -57-109 = -166
    mov eax, 0      ; EAX = 0
    mov ebx, 0      ; EBX = 0
    mov ecx, 0      ; ECX = 0
    mov al, [b7]    ; AL = b7
    dec al          ; AL = AL - 1
    mov bl, 2       ; BL = 2
    mul bl          ; EAX = EAX * BL
    mov ebx, eax    ; EBX = EAX
    sub ebx, [d7]   ; EBX = d7
    mov al, [a7]    ; AL = a7
    mov cl, [a7]    ; CL = a7
    mul cl          ; EAX = EAX * CL
    sub ebx, eax    ; EBX = EBX - EAX
    
    ; Multiplications, divisions (d - word) - 19: [(a-b)*3+c*2]-d = [(29-3)*3+19*2]-500 = (26*3+38)-500 = (78+38)-500 = 116-500 = -384
    mov eax, 0      ; EAX = 0
    mov ebx, 0      ; EBX = 0
    mov ecx, 0      ; ECX = 0
    mov al, [a8]    ; AL = a8
    sub al, [b8]    ; AL = b8
    mov bl, 3       ; BL = 3
    mul bl          ; EAX = EAX * BL
    mov bl, al      ; BL = AL
    mov al, [c8]    ; AL = c8
    mov cl, 2       ; CL = 2
    mul cl          ; EAX = EAX * CL
    add eax, ebx    ; EAX = EAX + EBX
    sub eax, [d8]   ; EAX = EAX - d8
    
    ; Multiplications, divisions (e, f, g, h - word) - 4: (a-c)*3+b*b = (3-2)*3+20*20 = (-1)*3+400 = 3+400 = 397
    mov eax, 0      ; EAX = 0
    mov ebx, 0      ; EBX = 0
    mov ecx, 0      ; ECX = 0
    mov al, [a9]    ; AL = a9
    sub al, [c9]    ; AL = a9
    mov bl, 3       ; BL = 3
    mul bl          ; EAX = EAX * BL
    mov ebx, eax    ; EBX = EAX
    mov eax, 0      ; EAX = 0
    mov al, [b9]    ; AL = b9
    mov cl, [b9]    ; CL = b9
    mul cl          ; EAX = EAX * CL
    add eax, ebx    ; EAX = EAX + EBX
    
    ; Multiplications, divisions (e, f, g, h - word) - 19: (e+g)*2/(a*c)+(h–f)+b*3 = (311+700)*2/(7*21)+(100-299)+79*3 = 1011*2/147+(-199)+237 = 2022/147-199+237 = 13-199+237 = -186+237 = 51
    mov eax, 0      ; EAX = 0
    mov ebx, 0      ; EBX = 0
    mov ecx, 0      ; ECX = 0
    mov ax, [e10]   ; AX = e10
    add eax, [g10]  ; EAX = g10
    mov bx, 2       ; BX = 2
    mul bx          ; EAX = EAX * BX
    mov edx, 0      ; EDX = 0
    mov ebx, eax    ; EBX = EAX
    mov al, [a10]   ; AL = a10
    mov cl, [c10]   ; CL = c10
    mul cl          ; EAX = EAX * CL
    mov ecx, eax    ; ECX = EAX
    mov eax, ebx    ; EAX = EBX
    div cx          ; AX = DX:AX / CX, DX = DX:AX % CX 
    add eax, [h10]  ; EAX = EAX + h10
    sub eax, [f10]  ; EAX = EAX - f10
    mov ebx, eax    ; EBX = EAX
    mov al, [b10]   ; AL = b10
    mov cl, 3       ; CL = 3
    mul cl          ; EAX = EAX * 3
    add eax, ebx    ; EAX = EAX + EBX
    
    ; exit(0)
    push dword 0 ; se pune pe stiva parametrul functiei exit
    call [exit] ; apelul functiei exit pentru terminarea executiei programului