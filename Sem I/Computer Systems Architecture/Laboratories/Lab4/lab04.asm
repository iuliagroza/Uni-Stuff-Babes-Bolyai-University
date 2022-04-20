bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
a dw 11001001b
b dw 11011100b

segment code use32 class=code
start:
    ; 1100_1001 AND 1101_1100
    mov eax, 0
    ; mov  ax, [a] 
    ; and  ax, [b]
    ; mov ebx, 0
    ; mov bx, [a]
    ; or bx, [b]
    ; mov ax, [a]
    ; test ax, [b]
    ; mov al, 00110011b
    ; mov cl, 2
    ; shl al, cl ; → al = 11001100b, CF = 0
    ; stc ; CF = 1 (set carry)
    ; mov al, 00110011b   
    ; mov cl, 2
    ; rcr al, cl ; → al = 11001100b, CF = 1
    
    ; Se dau cuvintele A si B. Se cere dublucuvantul C:
    ; bitii 0-3 ai lui C coincid cu bitii 5-8 ai lui B
    ; bitii 4-8 ai lui C coincid cu bitii 0-4 ai lui A
    ; bitii 9-15 ai lui C coincid cu bitii 6-12 ai lui A
    ; bitii 16-31 ai lui C coincid cu bitii lui B
    
    push dword 0
    call [exit]