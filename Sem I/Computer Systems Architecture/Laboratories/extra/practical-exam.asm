bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fprintf, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    input_file db "input.txt", 0
    output_file db "output.txt", 0
    fd resd 1
    write_mode db "w", 0
    read_mode db "r", 0
    len equ 10000
    text times len db 0
    print_format db "%s", 13, 0
    sentence times 100 db 0

; our code starts here
segment code use32 class=code
    start:
    ; scrieti un program care citeste din fisier propozitii(siruri de caractere care se termin cu .). Scrieti intr-un alt fisier propozitiile de ordin par. numele fisierelor se dau in segmentul de date.
        push read_mode
        push input_file
        call [fopen]
        add esp, 4*2
        mov [fd], eax
        
        push dword[fd]
        push len
        push 1
        push text
        call [fread]
        add esp, 4*4
        
        push dword[fd]
        call [fclose]
        add esp, 4
        
        push write_mode
        push output_file
        call [fopen]
        add esp, 4*2
        mov [fd], eax
        
        ; mov esi, text
        ; mov edi, sentence
        ; cld
        ; mov ebx, 0
        ; mov edx, 0
        ; repeat:
            ; lodsb
            ; cmp al, 0
            ; je end
            ; inc edx
            ; cmp al, '.'
            ; je punct
        ; jmp repeat
        ; punct:
                ; inc bl
                ; push ebx
                ; and bl, 00000001b
                ; cmp bl, 0
                ; pop ebx
                ; je par
        ; par:
            ; mov ecx, text
            ; add ecx, edx
            ; mov [edi], ecx
            ; dec edi
            ; push sentence
            ; push print_format
            ; push dword[fd]
            ; call [fprintf]
            ; add esp, 4*3
        
        push text
        push print_format
            push dword[fd]
            call [fprintf]
            add esp, 4*3
        
        ; end:
        push dword[fd]
        call [fclose]
        add esp, 4
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
