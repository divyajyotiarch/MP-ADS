%macro filerw 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

section .data

    nxtline db "",10
    len equ $-nxtline
    msg1 db "1.Ascending Order ",10
    len1 equ $-msg1
    msg2 db "2.Descending Order ",10
    len2 equ $-msg2
    msg3 db "3.EXIT",10
    len3 equ $-msg3
    file1 db "file7.txt",0
    msg5 db "File Not Open"
    len5 equ $-msg5
    msg6 db "File Opened",10
    len6 equ $-msg6
    flag db 0
    
section .bss
    
    Buffer resb 20    ;stores the data in file
    temp resb 1     ;storing temporary in swapping
    fd_in resq 1    ;file pointer 
    count resb 1
    num resb 2
    
global _start
section .text
_start:

skip:

    filerw 1,1,nxtline,len
    filerw 1,1,msg1,len1
    filerw 1,1,msg2,len2
    filerw 1,1,msg3,len3

filerw 0,1,num,2
mov al,byte[num]

cmp al,33h
jz exit

p1:

    cmp al,31h
    jnz p2

    mov byte[flag],0    
    
    filerw 2,file1,2,0777    ;opening file
    mov [fd_in],rax
    
    bt rax,63        ;check file is open or not
    jnc o1
    filerw 1,1,msg5,len5
    jmp exit
    o1:
    filerw 1,1,msg6,len6
    
    call sort
    
    mov rax,3        ;CLOSE
    mov rdi,[fd_in]
    syscall    
    
jmp skip
    
p2:
    
    cmp al,32h
    jnz skip
    
    mov byte[flag],1
    
    filerw 2,file1,2,0777    ;opening file
    mov [fd_in],rax
    
    bt rax,63        ;check file is open or not
    jnc o2
    filerw 1,1,msg5,len5
    jmp exit
    o2:
    filerw 1,1,msg6,len6
    
    call sort
    
    mov rax,3        ;CLOSE
    mov rdi,[fd_in]
    syscall    
    
jmp skip
    
;exit call
exit:

    mov rax,60
    mov rdi,0
    syscall
    
sort:
    
    filerw 0,[fd_in],Buffer,20    ;read file*****
    mov cl,9    ;no. of elements
    
    
    pass:
    
        mov rsi,Buffer
        mov byte[count],9
        
        repeat:
            xor rax,rax
            xor rbx,rbx
    
            mov bl,byte[rsi]
            mov al,byte[rsi+2]
    
            cmp byte[flag],01h
            je de
            
            cmp bl,al
            jb a1
            mov byte[rsi],al
            mov byte[rsi+2],bl
            jmp a1
            
            de:
            cmp bl,al
            ja a1
            mov byte[rsi],al
            mov byte[rsi+2],bl
    
            a1:
            add rsi,2
            dec byte[count]
    
        cmp byte[count],00h
        jnz repeat
    
    loop pass
    
    filerw 1,[fd_in],Buffer,20
    
    ret

