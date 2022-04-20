bits 32 ;asamblare și compilare pentru arhitectura de 32 biți
; definim punctul de intrare in programul principal
global start

; declaram functiile externe necesare programului nostru 
extern exit ; indicam asamblorului ca exit exista, chiar daca noi nu o vom defini
import exit msvcrt.dll  ; exit este o functie care incheie procesul, este definita in msvcrt.dll
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante

; segmentul de date in care se vor defini variabilele 
segment data use32 class=data
a resb 1
b resw 1

a1 db '4'+1, '5'+2,'5', '3'
a2 equ 00_02h
a3 db 02h
a4 db 05,08h,
a5 dw 0h12
a7 dw 0503h
a8 db 111b, 3*3h
a equ 5

; byte - 00 - 2 digits

; segmentul de cod
segment code use32 class=code
start:
; ... 
    ;mov al, 0
    ;add al, 5
    
    ;mov cx, 0
    ;add cx, [a5]
    
    ;mov dx, 0
    ;add dx, [a3]
    ;add dl, [a5]
    
    ;mov eax, 0
    ;add eax, a
    
    mul DH; AX ← AL * DH

    ; exit(0)
    push dword 0 ; se pune pe stiva parametrul functiei exit
    call [exit] ; apelul functiei exit pentru terminarea executiei programului