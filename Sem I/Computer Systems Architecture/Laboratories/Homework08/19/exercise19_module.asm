%ifndef _EXERCISE19_MODULE_ASM_
%define _EXERCISE19_MODULE_ASM_

merge:
    ; .merge() takes len, S, T and sol as a parameter and builds in sol the merged string of S and T
    mov ecx, [esp+4]            ; len
    mov eax, [esp+8]            ; S
    mov edx, [esp+12]           ; T
    mov ebx, [esp+16]           ; sol
    
    add ecx, ecx                ; sol has the sum of the lengths of S and T (2*len)
    mov esi, 0
    
    forIndex
        push ecx
        test esi, 1             ; check if the position (esi) is odd (we are checking the least significant bit of esi)
        jz isEven               ; if we are on an even position
            pushf         
            push esi
            shr esi, 1          ; getting esi as the iterator for S now
            mov ecx, [eax+esi]  ; moving characters from S
            pop esi
            mov [ebx+esi], ecx  
            popf       
        isEven:
        jnz isOdd
            pushf
            push esi            ; getting esi as the iterator for T now
            shr esi, 1
            mov ecx, [edx+esi]  ; moving characters from T
            pop esi
            mov [ebx+esi], ecx
            popf       
        isOdd:
            pop ecx
            inc esi
    loop forIndex
    
    ret 4*4                      ; returning sol
    
%endif
            