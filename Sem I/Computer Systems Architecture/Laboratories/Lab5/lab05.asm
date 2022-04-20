bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
s db 1, 2, 3, 4 ; declare the string of bytes
l equ $-s ; compute the length of the string in l
d times l-1 db 0 ; reserve l bytes for the destination string and initialize it

segment code use32 class=code
start:
    mov ecx, l ; we put the length l in ECX in order to make the loop
    mov eax, 0
	mov esi, 0     
	jecxz Sfarsit      
	Repeta:
		mov al, [s+esi]
        mul byte [s+esi+1]          
		mov [d+esi], al    
		inc esi
	loop Repeta
	Sfarsit:;end of the program
    ;mov eax, 0
    ;mov eax, [d]
    push dword 0
    call [exit]