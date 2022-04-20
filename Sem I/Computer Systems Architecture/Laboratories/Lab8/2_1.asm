bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import fopen msvcrt.dll  
import fread msvcrt.dll  
import printf msvcrt.dll   
; exit is a function that ends the calling process. It is defined in msvcrt.dll
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    access_mode db "r", 0
    filename db "input.txt", 0
    file_descriptor dd -1
    
    len equ 100
    text times len db 0
    
    vowels db "aeiouAEIOU", 0
    
    format db "%d", 0
    

; our code starts here
segment code use32 class=code
    start:
        ; Opening the "input.txt" file
        push dword access_mode
        push dword filename
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je Finish
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        mov ebx, 0
        mov ecx, 2
        mov esi, text
        cld 
        
        ForLoop:
            lodsb
            
            cmp al, 0
            je Finish
            
            pushad
            mov ecx, 10
            mov edi, 0
            jecxz Stop
            VowelsLoop:
                cmp al, [vowels+edi]
                je Stop
                inc edi
            loop VowelsLoop
            jmp NotVowel
            popad
            Stop:
                inc ebx
            
            NotVowel:
                mov ecx, 2
        loop ForLoop
        
        Finish:
            push ebx
            push dword format
            call [printf]
            add esp, 4*2
            
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
