bits 32
global start        

; declare extern functions used by the program
extern exit, fprintf, fread, fopen, fclose, scanf        ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import fprintf msvcrt.dll     ; tell the assembler that function printf can be found in library msvcrt.dll
import fopen msvcrt.dll      
import fclose msvcrt.dll 
import fread msvcrt.dll 
import scanf msvcrt.dll 
segment data use32 class=data
    file_name_input resb 15
    file_name_output db "output.txt", 0
    file_descriptor_input dd -1
    file_descriptor_output dd -1
    access_mode_input db "r", 0
    access_mode_output db "w", 0
    read_format db "%s %c", 0
    format_print db "%s ", 10, 0
    format_char db "%c", 0
    len equ 100
    character resb 1
    c resb 1
    w resb 30
segment code use32 class=code
    start:
        ; read a file name from keyboard 'input_test.txt' and a character c, output.txt : words that contain character c
        push dword c
        push dword file_name_input
        push dword read_format
        call [scanf]
        add esp, 12
        
        push dword access_mode_input
        push dword file_name_input
        call [fopen]
        add esp, 8
        
        mov [file_descriptor_input], eax
        
        cmp eax, 0
        je end
        
        push dword access_mode_output
        push dword file_name_output
        call [fopen]
        add esp, 8
        
        mov [file_descriptor_output], eax
        
        cmp eax, 0
        je end
        
        mov ebx, 0
        mov edx, 0 
        
        repeat:
           pushad
           ; fread() reads len times bytes
           ; we read byte by byte
           push dword [file_descriptor_input]
           push dword 1
           push dword 1
           push dword character
           call [fread]
           add esp, 4 * 4
           
           cmp al, 0
           je end_loop
        
           popad
           
           mov al, byte [character]
           cmp al, ' '
           je end_word
                  
           mov [w+ebx], al  ; form word
           inc ebx
                    
           cmp al, byte [c]
           jne not_ok
           mov edx, 1
           not_ok:
           jmp end_if
           end_word: 
               cmp edx, 1
               jne over
               
               pushad
               
               push dword w
               push dword format_print
               push dword [file_descriptor_output]
               call [fprintf]
               add esp, 4 * 3
               
               over:
               cmp eax, 0
               je end_loop
               
               popad
               
               mov ebx, 0
               mov edx, 0 
               mov dword [w], 0
               end_if:
               jmp repeat
        
        end_loop:
        
        push dword [file_descriptor_input]
        call [fclose]
        add esp, 4
        
        push dword [file_descriptor_output]
        call [fclose]
        add esp, 4
        
        end:
        push dword 0          ; push on stack the parameter for exit
        call [exit]           ; call exit to terminate the program
