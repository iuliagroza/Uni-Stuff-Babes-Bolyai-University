bits 32 

global concatenare     


segment code use32 class=code
    concatenare:
        
        mov esi,[esp+4]
        mov edi,[esp+12]
        mov ecx,[esp+20]
        cld 
        repeta:
            lodsb
            stosb
        loop repeta
        mov esi,[esp+8]
        mov ecx,[esp+16]
        repeta2:
            lodsb
            stosb
        loop repeta2
        ret