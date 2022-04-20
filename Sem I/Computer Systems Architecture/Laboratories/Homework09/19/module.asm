bits 32

global _positive

segment data public data use32

segment code public code use32
    _positive:
        push ebp
        mov ebp, esp
        
        mov ebx, [ebp+8]        ; move the parameter into EBX
        cmp ebx, 0              ; compare EBX with 0 to see if it's positive
        
        jl .negative             ; jump if less than 0
        
        mov eax, 1              ; return 1 if [EBP+8] is positive
        
        jg .positive
        
        .negative:
        mov eax, 0              ; return 0 if [EBP+8] is negative
        
        .positive:
            mov esp, ebp
            pop ebp
        ret