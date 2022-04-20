bits 32

extern _printf
global _convertor

segment data public data use32
    format1 db "%x ", 0
    format2 db "%d%d%d%d%d%d%d%d ", 0

segment code public code use32
    _convertor:
        push ebp
        mov ebp, esp
        
        pushad                  ; saving the values of all the registers so they won't be modified
        cmp dword [ebp+12], 2   ; checking if the base parameter is 2 or 16     
        jne base16
        
        mov ecx, [ebp+8]
        jecxz endFor
                        
        forIndex:               ; performing the conversion in base 2
            mov eax, ecx
            mov edx, 0
            mov ebx, 2
            div ebx
            push dword [edx]
            mov ecx, eax
        loop forIndex
            
        endFor:
            push dword format2
            call _printf
            add esp, 4*9
        
        base16:
            push dword [ebp+8]      ; converting in base 16 is simply made by displaying the number in another format (%x)
            push dword format1
            call _printf
            add esp, 4*2            ; adding the size of the parameters in ESP
            
        cmp dword [ebp+12], 2     
        je base2
        popa
        
        base2:
            pop ebp
        ret