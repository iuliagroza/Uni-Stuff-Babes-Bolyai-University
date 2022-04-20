bits 32

global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll        

segment data use32 class=data
    a dd -9
    b dd 6
    format db "%d * %d = %d", 0

segment code use32 class=code
    start:
        ;Two natural numbers a and b (a, b: dword, defined in the data segment) are given. Calculate their product and display the result in the following format: "<a> * <b> = <result>". Example: "2 * 4 = 8". The values will be displayed in decimal format (base 10) with sign.
        mov edx, 0
        mov eax, 0
        mov eax, [a]
        imul dword [b]      ; Compute the signed multiplication on EDX:EAX
        
        push dword eax      ; Push the parameters in reversed order; Push the low part
        cmp edx, dword -1   ; If the high part exists
        je no
        push dword edx      ; Push the high part of the result
        no:
        push dword [b]
        push dword [a]
        push dword format
        call [printf]
        add esp, 4*5        ; Free parameters on the stack (5 dwords)
        
        push dword 0
        call [exit]