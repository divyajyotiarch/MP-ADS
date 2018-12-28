section .data

    p db 0
    n db 0
    msg1 db "No. of positive no.s"
    len1 equ $-msg1
    msg2 db "No. of negative no.s"
    len2 equ $-msg2
    msg3 db " ",10
    len3 equ $-msg3

    array dq 123456788D79BBCCh,1BCDEF8812345678h,0FFFF88889ABCDEAFh,987654325B793888h,0FFAAFFAAA2345678h,876543219ABCDEAFh,0ABCDEAF55B793888h,12312312FFEEEEFFh,0ABCDEAF512312312h,0CDEA1111D231EEEFh,45B7CDEA12315B79h,2345678923456789h,3456789034567890h,0ABCDEAFF12345678h,0AFFAA12345676543h,1A1A2A2A34344545h,4D4D1F1F2E2E3333h,0BBCC112233441122h,9988776655443322h,0CBCBACAC99887766h


section .bss
cnt resb 2

global _start
section .text
_start:

    mov cl,20
    mov rsi,array

skip:
    bt qword[rsi],63

    jnc a1
    inc byte[n]

jmp a2

a1:
    inc byte[p]

a2:
    add rsi,8
    dec cl
    jnz skip

;hex to ascii for no. of positives
    mov rdi,cnt
    mov dl,[p]
    mov al,dl
    and al,0Fh
    cmp al,09h
    jbe a3
    add al,07h

a3:
    add al,30h
    mov [rdi],al

;write call
    mov rax,1
    mov rdi,1
    mov rsi,msg1
    mov rdx,len1
    syscall

    mov rax,1
    mov rdi,1
    mov rsi,cnt
    mov rdx,1
    syscall

;hex to ascii for no. of negatives
    mov rdi,cnt
    mov dl,[n]
    mov al,dl
    and al,0Fh
    cmp al,09h
    jbe a4
    add al,07h

a4:
    add al,30h
    mov [rdi],al

;write call
    mov rax,1
    mov rdi,1
    mov rsi,msg3
    mov rdx,len3
    syscall    
    
    mov rax,1
    mov rdi,1
    mov rsi,msg2
    mov rdx,len2
    syscall    
    
    mov rax,1
    mov rdi,1
    mov rsi,cnt
    mov rdx,1
    syscall

    mov rax,1
    mov rdi,1
    mov rsi,msg3
    mov rdx,len3
    syscall    

;exit call
    mov rax,60
    mov rdi,0
    syscall


