bits 32 ;asamblare și compilare pentru arhitectura de 32 biți
; definim punctul de intrare in programul principal
global start

; declaram functiile externe necesare programului nostru 
extern exit ; indicam asamblorului ca exit exista, chiar daca noi nu o vom defini
import exit msvcrt.dll  ; exit este o functie care incheie procesul, este definita in msvcrt.dll
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante

; segmentul de date in care se vor defini variabilele 
segment data use32 class=data

; First exercise
a10 db 11111001b
b10 db 10001001b

c10 db 25h
d10 db 7Bh

; Second exercise
; a0 db 10b;
; a1 dw 0h12;
; a2 db 123456h;
; a3 db 1111_0011_1111_0000b;
; _a4 dw 124h;
; a5# db 33h;
; ?a6 dw 233h;
; a7~ db 1233h;

; segmentul de cod
segment code use32 class=code
start:
; ... 
    
    ; First exercise
    mov eax, 0      ; EAX = 0
    mov al, [a10]   ; AL = aa
    add ax, [b10]   ; AX = AX + bb
    
    ;mov eax, 0      ; EAX = 0
    ;mov al, [c10]   ; AL = cc
    ;add ax, [d10]   ; AX = AX + dc

    ; exit(0)
    push dword 0 ; se pune pe stiva parametrul functiei exit
    call [exit] ; apelul functiei exit pentru terminarea executiei programului