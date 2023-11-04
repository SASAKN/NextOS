section .text
global start

start:
    hlt

section .text
global call_kern

call_kern:
    jmp start
    jmp call_kern