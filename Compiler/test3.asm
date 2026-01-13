extern printf, scanf, exit
section .text
global main

main:
push a
push format_in
call scanf
add esp, 8
push 2
push 2
pop ebx
pop eax
imul eax, ebx
push eax
push 2
pop ebx
pop eax
imul eax, ebx
push eax
push dword [a]
pop ebx
pop eax
add eax, ebx
push eax
push dword [a]
push dword [a]
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
push 5
pop ebx
pop eax
add eax, ebx
push eax
pop eax
mov [rezultat], eax
push dword [rezultat]
pop eax
push eax
push format_out
call printf
add esp, 8
push 0
call exit

section .data
format_in: db "%d", 0
format_out: db "%d", 10, 0
a: dd 0
rezultat: dd 0
