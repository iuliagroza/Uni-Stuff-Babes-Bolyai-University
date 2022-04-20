bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
a1 db 0000_1100b
b1 db 0
c1 dd 0


segment code use32 class=code
start:
    ; 4. Given the byte A, obtain the integer number n represented on the bits 2-4 of A. Then obtain the byte B by rotating A n positions to the right. Compute the doubleword C as follows:
    ; the bits 8-15 of C have the value 0
    ; the bits 16-23 of C are the same as the bits of B
    ; the bits 24-31 of C are the same as the bits of A
    ; the bits 0-7 of C have the value 1
    mov ebx, 0
    mov eax, 0
    mov al, [a1]      ; n computed in AL
    ror eax, 2         ; Obtaining the number representend on the bits 2-4 of A by rotating A to the right with 4-(4-2)=2 positions
    and al, 0000_0111b ; Obtaining n by getting only 0-2 bits
    
    mov cl, al      
    mov al, [a1]     
    ror al, cl       ; Rotating A by 3 positions to the right
    mov [b1], al     ; Storing the result in B

    mov eax, 0
    and eax, 1111_1111_1111_1111_0000_0000_1111_1111b   ; bits 8-15 are set to 0
    mov ebx, 0
    mov bl, [b1]
    mov cl, 16
    rol ebx, cl                                         ; Moving bits 0-7 of b to 16-23 in EAX
    or eax, ebx                                         ; Moving bits of B on 16-23 in C
    mov ebx, 0
    mov bl, [a1]
    mov cl, 8
    ror ebx, cl                                         ; Rotating eax by 8 positions to the right (Shorter than 24 positions to the left)
    or eax, ebx                                         ; Setting the bits in C
    or eax, 0000_0000_0000_0000_0000_0000_1111_1111b    ; Bits 0-7 are set to 1
    mov [c1], eax
    
    ; A = 0000_1100
    ; n = 011 = 3
    ; B = 1000_0001
    ;       8    1
    ; C = 0000_1100_1000_0001_0000_0000_1111_1111b
    ;       0    C    8    1    0    0    F    F
 
    push dword 0
    call [exit]