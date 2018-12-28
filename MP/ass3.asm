%macro readwrite 3
mov rax,%1
mov rdi,1
mov rsi,%2
mov rdx,%3
syscall
%endmacro

section .data

    nxtline db "",10
    len equ $-nxtline
    msg1 db "1.HEX to BCD",10
    len1 equ $-msg1
    msg2 db "2.BCD to HEX",10
    len2 equ $-msg2
    msg5 db "3.EXIT",10
    len5 equ $-msg5
    msg3 db "Enter number (0000-FFFF)",10
    len3 equ $-msg3
    msg6 db "Enter number (00000-65535)",10
    len6 equ $-msg6

section .bss

    count resb 1
    num1 resb 5
    num2 resb 6
    num3 resb 5
    num4 resb 6
    counth resb 1
    countb resb 1
    

global _start
section .text
_start:

skip:

    readwrite 1,nxtline,len
    readwrite 1,msg1,len1
    readwrite 1,msg2,len2
    readwrite 1,msg5,len5

readwrite 0,num1,2
mov al,byte[num1]

cmp al,33h
jz exit


;HEX to BCD
    cmp al,31h
    jnz p2
    readwrite 1,msg3,len3
    
    readwrite 0,num1,5
    
    mov rsi,num1   
    
    xor rcx,rcx    ;****
    xor rax,rax    ;****
    
    call atoh

    call procedure1
    
    mov rdi,num3
    
    
jmp skip


;BCD to HEX
p2:
    cmp al,32h
    jnz skip
    readwrite 1,msg6,len6
        
    readwrite 0,num2,6
        
    xor rdx,rdx        ;***
    xor rax,rax        ;***
    
    call procedure2

    call htoa
    
    readwrite 1,num4,6

jmp skip

;exit call
exit:

    mov rax,60
    mov rdi,0
    syscall

;hex to ascii
htoa:
    mov rcx,04h
    mov rdi,num4
    xor rbx,rbx
    
    up1:
        rol dx,4
        mov bl,dl
        and bl,0Fh
        cmp bl,09h
        jbe up2
        add bl,07h
    
    up2:
        add bl,30h

        mov byte[rdi],bl
        inc rdi
        loop up1
    ret
    
;ASCII to hex***********
atoh:

    mov cl,4
    xor rbx,rbx
    
    a1:
    
    shl ax,4
    mov bl,byte[rsi]
    cmp bl,39h
    jbe a2
    sub bl,07h
    
    a2:
    
    sub bl,30h
    add al,bl
    inc rsi
    loop a1
    
    ret
        

procedure1:                 ;hex to BCD

    mov cx,0Ah        ;load 10 in cx
    mov byte[count],0

    s1:
        xor rdx,rdx
        div cx
        push dx
        inc byte[count]
        cmp rax,00h
        jne s1    
        
    s2:
        pop dx
        add dx,30h
        mov word[num3],dx
        readwrite 1,num3,5
        dec byte[count]
        cmp byte[count],00h
        jne s2
    ret
    

procedure2:            ;BCD to hex

    mov bl,0Ah
    mov rsi,num2
    mov byte[countb],5
    
    s3:
        mul rbx
        mov dl,byte[rsi]
        sub dl,30h
        add rax,rdx
        inc rsi
        dec byte[countb]
        cmp byte[countb],00h
        jne s3

    mov rdx,rax
    
    ret
        
    
