%macro readwrite 3
mov rax,%1
mov rdi,1
mov rsi,%2
mov rdx,%3
syscall
%endmacro

section .data

    colon db " : "
    msg equ $-colon
    nxtline db "",10
    len equ $-nxtline
    msg1 db "Display GDTR    "
    len1 equ $-msg1
    msg2 db "Display IDTR    "
    len2 equ $-msg2
    msg3 db "Display LDTR    "
    len3 equ $-msg3
    msg4 db "Display TR    "
    len4 equ $-msg4
    msg5 db "Display MSW    "
    len5 equ $-msg5
    msg6 db "Protection is Enabled    "
    len6 equ $-msg6
    msg7 db "NOT  "
    len7 equ $-msg7
    
section .bss
    
    num resb 2
    num1 resb 12
    temp1 resb 4
    ldt resb 4
    tr resb 4
    msw resb 4
    numb resb 8
    numo resb 4
    

global _start
section .text
_start:

p1:    ;display GDTR*****

    readwrite 1,msg1,len1
    
    sgdt [num1]
    mov rsi,num1
    
    mov eax,dword[rsi]

    mov rdi,numb
    call htoa1
    
    readwrite 1,numb,8
    readwrite 1,colon,msg
    
    xor rax,rax
    mov rsi,num1
    add rsi,4
    
    mov ax, word[rsi]

    mov rdi,numo
    call htoa2
    readwrite 1,numo,4
    


p2:    ;display IDTR*****
    readwrite 1,nxtline,len
    readwrite 1,msg2,len2
    
    sidt [num1]
    mov rsi,num1
    
    mov eax,dword[rsi]

    mov rdi,numb
    call htoa1
    
    readwrite 1,numb,8
    readwrite 1,colon,msg
    
    xor rax,rax
    mov rsi,num1
    add rsi,4
    
    mov ax, word[rsi]

    mov rdi,numo
    call htoa2
    readwrite 1,numo,4


p3:    ;Display LDTR*******

    readwrite 1,nxtline,len
    readwrite 1,msg3,len3
    
    xor rax,rax
    
    sldt ax

    mov rdi,ldt

    call htoa2
    readwrite 1,ldt,4


p4:    ;display TR*****

    readwrite 1,nxtline,len
    readwrite 1,msg4,len4

    xor rax,rax
    
    str ax 
    
    mov rdi,tr
    
    call htoa2
    readwrite 1,tr,4
    
p5:     ;Display MSW*********

    readwrite 1,nxtline,len
    readwrite 1,msg5,len5

    xor rax,rax
    
    smsw ax
    
    bt ax,0
    jc c1
    readwrite 1,msg7,len7
    c1:
    readwrite 1,msg6,len6
    
    mov rdi,msw
    call htoa2

    readwrite 1,msw,4    
    readwrite 1,nxtline,len
    
    
;exit call
exit:

    mov rax,60
    mov rdi,0
    syscall


;hex to ascii *********
htoa1:
    
    xor rbx,rbx
    mov rcx,8
    up11:
        rol eax,4
        mov bl,al
        and bl,0Fh
        cmp bl,09h
        jbe up21
        add bl,07h
    
    up21:
        add bl,30h

        mov byte[rdi],bl
        inc rdi
        loop up11
    ret

htoa2:
    mov rcx,4
    xor rbx,rbx

    up12:
        rol ax,4
        mov bl,al
        and bl,0Fh
        cmp bl,09h
        jbe up22
        add bl,07h
    
    up22:
        add bl,30h

        mov byte[rdi],bl
        inc rdi
        loop up12
    ret








