.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD   ; 

.data
	a_string BYTE "Happy"

.code
	main PROC c
		;place the first char in a_string to aex
		mov eax, 0 
		mov al, a_string

		mov ebx, 0 
		mov al, BYTE PTR [a_string]
		mov bl, BYTE PTR [a_string]
		shl ebx, 8			;ebx = 00 00 48 00 01001000

		mov bl, BYTE PTR [a_string +1]
		shl ebx, 8			; ebx = 00 00 48 61

		mov bl, BYTE PTR [a_string +2]
		shl ebx, 8			; ebx = 00 48 61 70


		mov bl, BYTE PTR [a_string +3]
		  
		
		INVOKE ExitProcess, 0
	main endp
end