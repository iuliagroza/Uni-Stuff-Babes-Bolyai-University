bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf, fopen, fclose, fscanf   ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll        ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    final db "end", 0
    buffer resb 100
    read_format db "%s", 0
    print_format db "%s has %d capital letters", 10, 0
    ; ...
    temp db -1
    file_desc dd -1
    mode db "r", 0
    range dw 415Ah

; our code starts here
segment code use32 class=code
    file_counter:
        mov EDX, [esp+4];file name adress
        push dword mode
        push EDX
        call [fopen]
        add esp, 4*2
        
        mov EBX, 0
        
        mov [file_desc], EAX
        
        read_loop:
            push file_desc
            push 1
            push 1
            push temp
            call [fscanf]
            add esp, 4*4
          
            
            
            cmp AL, 0
            je end_read
            mov CX, [range]
            mov DL, [temp]
            cmp ch, dl
            jb finish
                cmp cl, dl
                ja finish
                
                inc EBX  
                
            finish:
        jmp read_loop
        end_read:
        
        mov EAX, EBX
    ret 4*1
        
    start:
        ;read strings/file names from the keyboard untill end is written
        loop_start:
            push dword buffer
            push dword read_format
            call [scanf]
            add esp, 4*2    
            
            mov EAX, [final]
            cmp EAX, dword [buffer]
            je loop_end
            
            ;call function file_counter(file_name), file_counter return count in EAX
            push buffer
            call file_counter
            
            push dword buffer
            push dword EAX
            push dword print_format
            call [printf]
            add esp, 4*3
            
        jmp loop_start
        loop_end:
        
            
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program