extern printf, scanf, exit
section .text
global main

main:
; Citire x
push x
push format_in
call scanf
add esp, 8
push dword [x]
push 5
pop ebx
pop eax
sub eax, ebx
push eax
; Atribuire x = ...
pop eax
mov [x], eax
push dword [x]
push 2
push dword [x]
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
add eax, ebx
push eax
; Scriere
pop eax
push eax
push format_out
call printf
add esp, 8
; Exit
push 0
call exit

; --- DATA SECTION ---
section .data
format_in: db "%d", 0
format_out: db "%d", 10, 0
x: dd 0
