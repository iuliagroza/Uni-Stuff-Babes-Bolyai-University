bits 32 

global checkPrime

segment code use32 class=code

checkPrime:
;esp+4 - for the result
mov eax, [esp+8] ;it is actually byte 
cmp eax,2
je prime
mov bl,2 

dividing:
    div bl 
    cmp ah, 0 
    je notPrime
   
    mov eax, [esp+8] ;restore ax 

    inc bl 
    cmp bl,al
    je prime
jmp dividing

notPrime:
mov dword [esp+4],0
jmp endFct

prime:
mov dword [esp+4],1
endFct:
ret