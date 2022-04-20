bits 32
global start

extern exit
import exit msvcrt.dll

; 19.  Being given two strings of bytes, compute all positions where the second string appears as a substring in the first string. 
; 0 3 8

segment data use32 class=data
    a db 1, 2, 3, 1, 2, 4, 1, 3, 1, 2, 5
    lenA equ $-a
    
    b db 1, 2
    lenB equ $-b
    
    d resb lenA

segment code use32 class=code
start:
    mov ecx, lenA ; loop lenA times
    jecxz program_end ; jump to the end if ecx is 0
    
    xor ebx, ebx ; index for the current value in d
    ; xor ebx, ebx  is faster than  mov ebx, 0
    
    mov esi, 0 ; the index for the current value in a
    mov edi, 0 ; the index used for the current value in b
    loop_string:
        mov al, [a+esi] ; move the current element from a to al
        
        check_occurence: ; check if the substring appears in the string
            mov dl, [b+edi] ; move the current element from b to dl
            cmp al, dl ; compare the two elements
            jne check_length ; if the elements are NOT equal the substring is not present
            
            inc edi ; if the elements ARE equal we increment edi (index for b) to check the next element from the substring
        je check_occurence ; we keep looping until we hit an element that is not in the substring
        
        
        check_length: ; we check if the length of the count from above is equal to the length of the substring
        cmp edi, lenB ; compare the current index for b to the length of b
        jne end_loop ; if they are NOT equal we jump to the next index of a
        mov [d+ebx], esi ; if they ARE equal we save the current index of a in d
        inc ebx ; if they ARE equal we increment the current index for d
        mov edi, 0 ; if they ARE equal we reset the count of occurences of the elements of the substring in the main string
        
        end_loop:
        inc esi ; increment esi to the next index
    loop loop_string
    
    program_end: ; program end label
    
    ; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program
