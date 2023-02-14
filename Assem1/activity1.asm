.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess POTO, dwExitCode: DWORD   ; 

.data
	value DWORD 2 ;variables int value = 10
	msg BYTE "ABC", 0Ah; char * msg = "ABC\n"; 

.code
	main PROC c
	mov eax, 10 ; eax= 10

	add eax, 15  ; eax = 25
	mul value       ; eax*=2
	mov ecx, eax

	mov <dest>, <src>; <dest> =<src>
	INVOKE ExitProcess, 0
	main endp
end


;q1: machine instruction move "mov eax, 10"
;q2 how 10 is stored in memory