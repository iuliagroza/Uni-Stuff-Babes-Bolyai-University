;Problem. A string of quadwords is given. Compute the number of multiples of 8 from
;the string of the low bytes of the high word of the high doubleword from the elements of the quadword string 
;and find the sum of the digits (in base 10) of this number.


;Solution: We first parse the quadword string and obtain the number of multiples of 8
;from the string of the low bytes of the high word of the high doubleword from the elements of the quadword string.
;Then we obtain the digits of this number by successive divisions to 10 and then compute the sum of these digits.


bits 32 
global start
extern exit; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll; exit is a function that ends the calling process. It is defined in msvcrt.dll


; our data is declared here (the variables needed by our program)
segment data use32 class=data
	sir  dq  123110110abcb0h,1116adcb5a051ad2h,4120ca11d730cbb0h
	len equ ($-sir)/8;the length of the string (in quadwords)
	opt db 8;variabile used for testing divisibility to 8
	zece dd 10;variabile used for determining the digits in base 10 of a number by successive divisions to 10
	suma dd  0;variabile used for holding the sum of the digits 
    
    
; our code starts here
segment code use32 class=code
    start:
	mov esi, sir;in eds:esi we will store the FAR address of the string "sir"
	cld;parse the string from left to right(DF=0).    
	mov ecx, len;we will parse the elements of the string in a loop with len iterations.
	mov ebx, 0;in ebx we will hold the number of multiples of 8.
	repeta:
		lodsd;in eax we will have the low doubleword (least significant) of the current quadword from the string
		lodsd;in eax we will have the high doubleword (least significant) of the current quadword from the string
		shr eax, 16
		mov ah, 0;we are interested in the low byte (least significant) of this word (AL)
      
		div byte[opt];check whether al is divisible to 8
		cmp ah, 0;if the remainder is 0, resume the loop "repeta". 
				;else increment the number of multiples of 8 from EBX. 
		jnz nonmultiplu
		inc ebx

		nonmultiplu:
	loop repeta;if there are more elements (ecx>0) resume the loop.

	;next, we obtain the 10-th base digits of the number EBX by successive divisions to 10 and then compute the sum of these digits

	mov eax, ebx
	mov edx, 0
    
	transf:
		div dword[zece];divide the number by 10 in order to obtain the last digit; this digit will be in EDX
		add dword[suma], edx;add the digit to the sum.
		cmp eax, 0
	jz sfarsit;if the quotient (from al) is 0 it means we obtained all the digits and we can leave the loop "transf"
				;else prepare the quotient for a new iteration 
	mov edx, 0				
	jmp transf;resume the loop in order to obtain a new digit.

sfarsit:;end the program
           
        push dword 0; push the parameter for exit onto the stack
        call [exit]; call exit to terminate the program