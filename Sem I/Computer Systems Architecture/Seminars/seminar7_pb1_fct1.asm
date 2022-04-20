bits 32

global compute

extern fopen,fread,fclose               
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll

segment data use32 class=data
    readmode db 'r',0
    buffer db 0
    descriptor dd -1
    
segment code

compute:
;esp+4 - nr
;esp+8 - filename
mov eax,[esp+8]
mov ebx,0 ;for the count of capital letters

push dword readmode 
push eax 
call [fopen]
add esp,4*2 
mov [descriptor], eax 
cmp eax, 0 
je done2

reading:
;int fread(void * str, int size, int count, FILE * stream)
push dword [descriptor]
push dword 1
push dword 1 
push dword buffer 
call [fread]
add esp, 4*4 

cmp eax, 0 
je done2 

cmp byte [buffer], 'A'
jb reading ;continue reading from the file 

cmp byte [buffer], 'Z' 
ja reading 

inc ebx 
jmp reading

done2:
mov eax, [esp+4]  ;address for the count 
mov [eax], ebx  ;set the actual count

push dword [descriptor]
call [fclose]
add esp,4

ret