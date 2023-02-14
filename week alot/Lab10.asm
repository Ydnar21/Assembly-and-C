comment !
.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD   ; 
extern printf: NEAR
extern scanf: NEAR

.data
	input1 DWORD 20 DUP (?)
	input2 DWORD 20 DUP (?)
	input3 DWORD 20 DUP (?)
	format BYTE "%d", 0
	format1 BYTE "The greatest value is:  %d", 0
	


.code
	main PROC c
	push offset input1
	push offset format
	call scanf
	add esp, 8
	push offset input2
	push offset format
	call scanf
	add esp, 8
	push offset input3
	push offset format
	call scanf
	add esp,8
	mov eax, input1
	mov ebx, input2
	mov ecx, input3
	cmp eax, ebx

	jg A
	jl B
	A:
	cmp eax, ecx
	jg AA
	jl CC
	B:
	cmp ebx, ecx
	jg BB
	AA:
	push eax
	push offset format1
	call printf
	jmp finish
	BB:
	push ebx
	push offset format1
	call printf
	jmp finish 
	CC:
	push ecx
	push offset format1
	call printf
	finish:
	INVOKE ExitProcess, 0
	main endp
end



.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD 
extern printf: NEAR
extern gets: NEAR
.data
	question BYTE "Enter your string: ",0
	string BYTE "Hello World!", 0
	input BYTE 20 DUP (?)
	same BYTE "%s and %s are the same", 0
	diff BYTE "%s and %s are not the same", 0
	sform BYTE "%s", 0
	
.code
	main PROC c
	push offset question
	call printf
	push offset input
	call gets
	add esp, 8

	
	
	
	


	mov eax,0;count=0
	beginwhile:
	mov ecx, 0
	mov ebx, 0
	mov cl, BYTE PTR[input + eax]
	mov bl, BYTE PTR[string + eax]
	movzx ecx, cl
	movzx ebx , bl
	cmp ecx, ebx
	jne endwhile
	add eax,1
	cmp eax , 12
	je done
	jmp beginwhile
	endwhile:
	push offset string
	push offset input
	push offset diff
	call printf
	
	jmp ender
	done:
	push offset string 
	push offset input
	push offset same 
	call printf
	ender:
	

	

	INVOKE ExitProcess, 0
	main endp
end
!