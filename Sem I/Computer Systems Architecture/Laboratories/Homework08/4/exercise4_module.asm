bits 32

segment code use32 public code

global compare

compare:
    mov eax, [esp+4]
    
    cmp al, 'b'
    je found
    mov eax, 0
    ret
    
    found:
        mov eax, 1
        ret