bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fprintf, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll 
import fprintf msvcrt.dll 
import fclose msvcrt.dll      
; exit is a function that ends the calling process. It is defined in msvcrt.dll
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir1 resb 100
    sir2 resb 100
    read_format db "%s", 0
    
    filename db "output.txt", 0
    access_mode db "w", 0
    file_descriptor dd -1
    
    write_format db "%d", 0
    
    frecv db 0, 2, 2, 1, 1, 1, 2, 1, 2, 2, 0
    

; our code starts here
segment code use32 class=code
    start:
        push dword sir1
        push dword read_format
        call [scanf]
        add esp, 4*2
        
        push dword sir2
        push dword read_format
        call [scanf]
        add esp, 4*2
        
        push dword access_mode
        push dword filename
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je .finish
        
        mov ebx, 0
        
        .frequency1:
            mov eax, 0
            mov eax, [sir1+ebx] 
            cmp ebx, 0
            jmp .out1
            jmp .frequency1
        .out1:
        
        mov ebx, 0
        
        .frequency2:
            mov eax, 0
            mov eax, [sir2+ebx]
            cmp ebx, 0
            jmp .out2
            jmp .frequency2
        .out2:
        
        mov esi, 9
        
        .printing:
            mov ebx, 0
            mov bl, [frecv+esi]
            .digitprinting:
                pushad
                push dword esi
                push dword write_format
                push dword [file_descriptor]
                call [fprintf]
                add esp, 4*3
                popad
                
                dec ebx
                
                cmp ebx, 0
                je .digitout
                
                jmp .digitprinting
            .digitout:
            
            cmp esi, 0
            je .printingout
            
            dec esi
            
            jmp .printing
        .printingout:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
            .finish:
                push    dword 0      ; push the parameter for exit onto the stack
                call    [exit]       ; call exit to terminate the program
