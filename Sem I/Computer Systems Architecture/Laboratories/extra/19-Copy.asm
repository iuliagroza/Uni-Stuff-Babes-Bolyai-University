bits 32
global start

extern exit
import exit msvcrt.dll

; 19.  Being given two strings of bytes, compute all positions where the second string appears as a substring in the first string. 

segment data use32 class=data
    a db 1, 2, 3, 1, 2, 4, 1, 3, 1, 2, 5
       ; 0  1  2  3  4  5  6  7  8  9  10
    lenA equ $-a
    
    b db 1, 2
    lenB equ $-b
    
    d resb lenA
    ; 0, 3, 8

segment code use32 class=code
start:
    mov ecx, lenA ; load the number of elements of s into ecx
    jecxz program_end ; jump to the end if ecx is 0
    
    mov ebx, d ; load the offset of the d string into ebx
    
    mov esi, a ; load the offset of the a string into esi
    mov edi, b ; load the offset of the b string into edi
    CLD ; clear the direction flag
    loop_string:
        count_appearance: ; count the number of values from the substring that appear in the main string from index esi onwards and stop when we reach a value from a that is not in b
            cmpsb ; compare the current value from the a string to the current value of the b string
            pushf ; push the flags to the stack
            dec esi ; return esi to the previous value
            dec edi ; return edi to the previous value
            popf ; pop the flags from the stack
            jne check_length ; if the values are NOT equal we stop the loop
            
            inc edi ; if the values ARE equal we increment edi (index for b) to check the next value from the substring
        je count_appearance ; we keep looping until we reach a value from the main string that is not in the substring
        
        
        check_length: ; we check if the count from above is equal to the length of the substring
        mov eax, edi ; move the current memory address of b into eax
        sub eax, b ; substract the starting memory address of b from eax
        
        cmp eax, lenB ; compare the current index for b to the length of b
        jne end_loop ; if they are NOT equal we jump to the next index of a
        
        mov eax, esi ; if they ARE equal we compute the starting position of the subtring appearance by substracting the length of b from esi (esi=ending position from the count_appearance loop)
        inc eax
        sub eax, a ; substract the starting memory address of a from eax
        sub eax, lenB ; substract the length of b from eax
        
        xchg ebx, edi ; swap the contents of ebx and edi to prepare for storing result into d
        stosb ; store al into d
        xchg ebx, edi ; swap the contents of ebx and edi to prepare for the new loop iteration
        
        mov edi, b ; if they ARE equal we reset the current index of b
        
        end_loop:
        inc esi ; increment esi to the next index
    loop loop_string
    
    program_end: ; program end label
    
    ; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program
