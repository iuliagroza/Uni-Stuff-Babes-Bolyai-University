bits 32                         
segment code use32 public code
global factorial

factorial:
	mov eax, 1
	mov ecx, [esp + 4]
	
	repeat: 
		mul ecx
	loop repeat
	ret 4 ; in this case, 4 represents the number of bytes that need to be cleared from the stack (the parameter of the function)