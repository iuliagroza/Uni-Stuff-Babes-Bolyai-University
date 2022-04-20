;se tot citesc nume de fisiere de la tastatura pana se va introduce 'end'
;fisierele pot contine oricate caractere
;sa se gaseasca fisierul cu numar maxim de litere mari si sa se afiseze pe ecran numele si continutul lui
;un modul care calc nr de litere pentru un fisier
;un modul care afiseaza pe ecran numele si continutul unui fisier 

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern scanf               
import scanf msvcrt.dll


extern compute, printResult

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    filename times 20 db 0
    nrCapitalLett dd 0 
    filenameMax times 20 db 0
    nrMax dd 0
    final db 'end',0
    format db '%s',0
 
    
; our code starts here






segment code use32 class=code
    start:
        ; ...
              
        readFileNames:
        push dword filename 
        push dword format 
        call [scanf]
        add esp,4*2
    
        mov esi, filename 
        mov edi, final 
        compare:
            cmp byte [esi],0 
            je check2 ;the first string is finished
            
            cmpsb 
        je compare
        jne processFile  ;if they are not equal, then we have another file to process
        check2: 
            cmp byte [edi],0
            je done ;it means we read 'end' and the strings are equal
        
        processFile:
            push dword filename
            push dword nrCapitalLett
            call compute
            add esp,4*2
            
            mov eax,[nrCapitalLett]
            cmp eax, [nrMax]
            jbe next 
            mov [nrMax],eax 
            
            ;we must also keep the name of the file with the max nr 
            mov esi, filename 
            mov edi, filenameMax
            copy:
                movsb
                cmp byte [esi],0
            jne copy
            ;if we get here we are done copying (we reached 0), but we have to place the 0 in the destination as well 
            mov byte [edi],0
            
            next:
            jmp readFileNames
        
        done:
        ;call the function to print filename and content 
        push dword filenameMax 
        call printResult
        add esp,4
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

