comment !
.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD; 
extern printf:NEAR
extern scanf:NEAR

.data

a DWORD 10
b DWORD 20


;PART TWO
        d DWORD 7
       value DWORD 0 ;
       format BYTE "a = %d",0
       string1 BYTE "%d"
       
.code
    main PROC c
       

    
    push offset value
    push offset string1
    call scanf
    add esp, 8
    mov eax, value
   sub eax, 1
   mov ebx, d
   mov edx, 0
  div ebx
  mov ecx, 0
  mov eax, edx
  push eax
  push offset format
  call printf
  


  
 

    
       
	INVOKE ExitProcess, 0
	main endp
end









3rd PART
.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD; 
extern printf:NEAR
extern scanf:NEAR

.data
string BYTE "a = %d", 0
a DWORD 10
b DWORD 20     
.code
    main PROC c
    mov ebx, 0
    mov ebx,  a
    mov ecx, 0
    mov ecx,  b
    add ecx, ebx
    mov eax, 0
    mov eax, ebx
    push eax
    push offset string
    call printf

    
   

     
       
	INVOKE ExitProcess, 0
	main endp
end
!


;part 5
.586  ; 586 processor or higher
.model flat, stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode: DWORD; 
extern printf:NEAR



.data
    str1 BYTE "ABCDEF", 0
    str2 BYTE "XYZ123", 0
    string BYTE "str2 = %s", 0
    
    
.code
    main PROC c
    mov eax, 0
    mov al, BYTE PTR[str1]
    mov [str2] , al 
    mov al, BYTE PTR[str1+1]
    mov [str2+1], al
    mov al , BYTE PTR[str1 +2]
    mov [str2+2], al
    mov al , BYTE PTR[str1+3]
    mov [str2+3], al
    mov al , BYTE PTR[str1+4]
    mov [str2+4], al
    mov al , BYTE PTR[str1+5]
    mov [str2+5], al
    push offset str2
    push offset string
    
    call printf
    

     
       
	    INVOKE ExitProcess, 0
	main endp
end

