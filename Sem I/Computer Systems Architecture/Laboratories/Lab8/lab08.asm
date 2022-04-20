; The code below will print the message „Ana has 17 apples”
bits 32
global start        

; declare extern functions used by the program
extern exit, printf         ; add printf as extern function            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf can be found in library msvcrt.dll
                          
segment data use32 class=data
; char arrays are of type byte
format db "Ana has %d apples", 0  ; %d will be replaced with a number
				; char strings for C functions must terminate with 0
segment  code use32 class=code
    start:
        mov eax, 17
        
        ; will call printf(format, 17) => will print: „Ana has 17 apples”
        ; place parameters on the stack from right to left
        push dword eax
        push dword format ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing 
        add esp, 4 * 2     ; free parameters on the stack; 4 = size of dword; 2 = number of parameters

        ; exit(0)
        push dword 0      ; push on stack the parameter for exit
        call [exit]       ; call exit to terminate the programme
