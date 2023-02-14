.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD   ; 

.data
	;variables
	value DWORD 5

.code
	main PROC c
	;compute value!
	comment !
	ecx = 1
	eax = 1

	while ecx <= value
		eax *= ecx
		ecx += 1
	!

	mov ecx, 1
	mov eax, 1
	
	whilebegin:
	cmp ecx, value

	jg whileend
	;while loop body

	mul ecx
	add ecx, 1
	jmp whilebegin
	whileend:
	INVOKE ExitProcess, 0
	main endp
end