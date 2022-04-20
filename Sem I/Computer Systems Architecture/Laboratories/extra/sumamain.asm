bits 32 

global start        


extern exit,printf,scanf
import exit msvcrt.dll  
import printf msvcrt.dll  
import scanf msvcrt.dll  

extern CalculSuma  
     
segment data use32 class=data
    format db '%d',0
    formatafisare db 'suma = %d',0
    a dd 0
    b dd 0
    c dd 0


segment code use32 class=code
    start:
    
        push dword a
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword b
        push dword format
        call [scanf]
        add esp, 4*2
    
        push dword c
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword [c]
        push dword [b]
        push dword [a]
        call CalculSuma
        add esp,4*3
        push dword ebx
        push dword formatafisare
        call[printf]
        add esp, 4*2
    
        
        push    dword 0     
        call    [exit]       
