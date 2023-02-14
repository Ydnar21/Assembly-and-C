
comment !
.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD   ; 

.data
	;variables
	value DWORD 10

.code
	main PROC c
	push ebp
	mov ebp, esp
	
	sub esp, 12
;x=10
;[ebp-4] = 10
mov [ebp-4], 10

; y =20
;add_them(x,y)

push [ebp-8]
push [ebp-4]
call add_them
add esp, 8

	

add esp, 12
pop ebp







	;Assemble Instructions here
	INVOKE ExitProcess, 0
	main endp
end

Activity 11.1

.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD   ; 

.data
	;variables
	format BYTE "z= %d", 0Ah, 0

.code

	add_them:
	push ebp
	mov ebp, esp
	sub esp, 4 ;makes space for variable int c
	;c = [ebp-4], a = [ebp +8], b = [ebp +12]
	;[ebp-4] = [ebp+8] + [ebp+12]
	mov eax, [ebp+8]
	mov eax, [ebp+12] ; eax = a+b
	mov [ebp-4], eax

	mov eax, [ebp-4]




	pop ebp
	ret



	main PROC c
	push ebp
	mov ebp, esp
	;int x,y,z
	sub esp, 12 ;add 12 bytes

	; x = 10, x is ebp-4 at the top of the stack

	mov [ebp-4], 10
	;y=20,y is at ebp-8 y= [ebp-8]
	mov [ebp-8], 20
	push [ebp-8]
	push [ebp-8]
	push [ebp-4]
	call add_them
	add esp, 8 ; deallocated the bytes that were just pushed


	;z= eax, z is at ebp-12, z= [ebp-12]
	mov [ebp-12], eax

	push [ebp-12]
	push offset format
	call printf
	add esp, 8


	pop ebp
	ret ; pop eip
	;Assemble Instructions here
	INVOKE ExitProcess, 0
	main endp
end
!

Activity 11.2
.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD   ; 

.data
	;variables

.code

	increase:
	push ebp
	mov ebp,esp
	;*a+=1, a= [ebp+8]
	mov eax, [ebp+8]; eax = &x
	mov ecx, 1
	add eax, 1;[eax]+=1

	pop ebp
	ret

	main PROC c

	push ebp
	mov ebp,esp
	sub esp, 4; int x, x =[ebp-4]
	mov eax, 15
	mov[ebp-4], 15
	;increase(&x)
	lea eax, [ebp-4]
	push eax 
	call increase
	add esp,4 


	push [ebp-4]
	push offset format
	call printf
	add esp,8
	add esp, 4
	pop ebp

	;Assemble Instructions here
	INVOKE ExitProcess, 0
	main endp
end
