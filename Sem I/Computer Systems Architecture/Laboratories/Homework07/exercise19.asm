bits 32

global start

extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    s db 'a4353t54te8f5g46z9aq', 0xa    ; String to be parsed = 20 = 15h
    len equ $-s                         ; Length of s
    sol dd '', 0                        ; Variable in which stores the sum of the digits; it finally should be equal to 56
    file_name db "portocale.txt", 0     ; File to be created
    access_mode db "w", 0               ; File access mode:
                                        ; w - opens a file for writing. The file does noot exist, so it is firstly created. 
    file_descriptor dd -1               ; variable to hold the file descriptor
    
    format db "%d", 0


segment code use32 class=code
    start:
        ; A file name and a text (which can contain any type of character) are given in data segment. Calculate the sum of digits in the text. Create a file with the given name and write the result to file.
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                    ; Clean-up the stack.

        mov [file_descriptor], eax      ; Store the file descriptor returned by fopen.

        ; Check if fopen() has successfully created the file (EAX != 0).
        cmp eax, 0
        je final
        
        mov eax, 0                      ; Store the result in EAX.
        mov ecx, 0
        mov ecx, len                    ; Move the length of s in ECX.
        mov esi, 0                      ; Initialize ESI (the iterator) with 0.
        
        jecxz endFor                    ; The loop is stopped when ECX reaches 0.
        
        forIndex                        ; Start of loop
        cmp [s+esi], byte 48            ; Check if s[esi] as a string has the ASCII code in [48, 57] range (it is a digit).
        
        jae left_range
        jb no
        left_range:
            cmp [s+esi], byte 57
            jbe right_range
            ja nono
            right_range:                ; s[esi] is a digit. (48 <= s[esi] <= 57)
                mov ebx, 0  
                mov bl, [s+esi]
                sub bl, 48              ; Convert s[esi] from char to int (by subtracting 48 from its ASCII code).
                add al, bl              ; Add the digit to the final result.
            
            nono:
        
        no:
        
        inc esi
        loop forIndex
        endFor
        
        mov [sol], eax
            
        push dword [sol]                ; Write the result into the portocale.txt file.
        push dword format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3

        push dword [file_descriptor]
        call [fclose]                   ; Close the given file.
        add esp, 4                      ; Clean-up the stack.
        
    final:
        push dword 0
        call [exit]