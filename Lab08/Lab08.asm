.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD; 

.data
	var DWORD 11223344h

.code

	main PROC c
		;Pointer Diretions 
		mov BYTE PTR [var], 00000055h ; same as mov var, 55h
		
		mov eax, var    ; var= 11223355

		;mov 77h to the second bytes from the left var
		mov BYTE PTR [var+2], 77h

		


	 



		
			comment !
			;ptr = &var, ebx=&var
			mov ebx, offset var ;offset is that actual address
			;var+=5
			add var, 5
			;*ebx+=10
			mov edx, 10
			add [ebx], edx ; ebx must hold a valid address
			mov ecx, var  ; ecx = 35
			!
		INVOKE ExitProcess, 0
		;move only one byte 55h at var
		
	main endp
end