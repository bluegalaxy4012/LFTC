./compiler test3.cpp > test3.asm && nasm -f elf32 test3.asm -o test3.o && gcc -m32 test3.o -o test3 && ./test3
