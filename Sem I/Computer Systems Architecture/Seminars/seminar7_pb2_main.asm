;Se citeste de la tastatura numele unui fisier si apoi se citesc din fisier toate numerele existente reprezentate pe dublucuvant. Sa se afiseze pe ecran numerele ai caror octeti low din cuvintele high sunt primi.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern fopen,fclose,fscanf,printf ,scanf          
import fopen msvcrt.dll                           
import fclose msvcrt.dll                           
import fscanf msvcrt.dll                           
import printf msvcrt.dll 
import scanf msvcrt.dll
                          
extern checkPrime
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    filename times 20 db 0 
    descriptor dd -1 
    nr dd 0 
    readmode db 'r',0
    format db '%d',0
    format2 db '%d',10,13,0
    format3 db '%s',0

  
; our code starts here
segment code use32 class=code
    start:
        push dword filename
        push dword format3
        call [scanf]
        add esp,4*2
    
        push dword readmode
        push dword filename 
        call [fopen]
        add esp,4*2 
        
        mov [descriptor], eax 
        cmp eax,0
        je final 
        
        
        readFromFile:
        ;int fscanf ( FILE * stream, const char * format, ... );
        push dword nr
        push dword format 
        push dword [descriptor]
        call [fscanf]
        add esp,4*3
        cmp eax, 0 
        jle closeFile  ;we are done reading numbers
        
        mov eax, [nr] 
        shr eax,16  ;ax = high word
        mov ebx,0
        mov bl, al        ;ebx contains low byte from high word
        
        push ebx
        push dword 0    ;for the result: 0 = not prime, 1 = prime
        call checkPrime 
                
        pop eax  ;store the result of the prime function in eax
        pop ebx ; restore the number to be printed (maybe ebx was used in the fct)
        
        cmp eax, 0
        je next 
        
        ;print prime nr on the screen 
        push dword [nr] 
        push dword format2 
        call [printf]
        add esp,4*2
        
        next:
        jmp readFromFile
        
        closeFile: 
        push dword [descriptor]
        call [fclose]
        add esp,4 
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
