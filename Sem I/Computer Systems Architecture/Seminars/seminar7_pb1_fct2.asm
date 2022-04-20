bits 32

global printResult

extern printf              
import printf msvcrt.dll
extern fopen,fread,fclose               
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll

segment data use32 class=data
    readmode db 'r',0
    buffer times 101 db 0
    descriptor dd -1
    newLine db 10,13,0
    
segment code

printResult:
mov eax, [esp+4] ;address of filename
push dword eax
call [printf]
add esp,4 

push dword newLine
call [printf]
add esp,4

mov eax, [esp+4] ;address of filename
push dword readmode
push dword eax
call [fopen]
add esp,4*2

mov [descriptor], eax
cmp eax, 0 
je final2 

printFile: 
;int fread(void * str, int size, int count, FILE * stream)
push dword [descriptor]
push dword 100
push dword 1 
push dword buffer 
call [fread]
add esp, 4*4 

cmp eax,0 
je closeFile

mov byte [buffer+eax],0  ;e important pentru cazul in care la final citim mai putin de 100 de carac si trebuie pus 0 pt afisare  
push dword buffer 
call [printf]
add esp,4

jmp printFile
 
closeFile:
push dword [descriptor]
call [fclose]
add esp,4


final2:


ret 