part 1

%macro filerw 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

global htoa
extern pro1
extern pro2
extern pro3
global fd_in
global num1

section .data

    nxtline db "",10
    len equ $-nxtline
    msg1 db "1.No of Occurrences",10
    len1 equ $-msg1
    msg2 db "2.No. of Spaces",10
    len2 equ $-msg2
    msg4 db "4.EXIT",10
    len4 equ $-msg4
    msg3 db "3.No. of newlines",10
    len3 equ $-msg3
    msg5 db "File Not Open"
    len5 equ $-msg5
    msg6 db "File Opened",10
    len6 equ $-msg6
    file1 db "file.txt",0
    msg7 db "Enter character",10
    len7 equ $-msg7

section .bss
     
    num resb 2
    num1 resb 2
    fd_in resq 1    ;file pointer 

global _start
section .text
_start:

skip:

    filerw 1,1,nxtline,len
    filerw 1,1,msg1,len1
    filerw 1,1,msg2,len2
    filerw 1,1,msg3,len3
    filerw 1,1,msg4,len4

filerw 0,1,num,2
mov al,byte[num]

cmp al,34h
jz exit


p1:
    cmp al,31h
    jnz p2
    filerw 1,1,msg1,len1
    
    filerw 2,file1,2,0777    ;opening file
    mov [fd_in],rax
    
    bt rax,63        ;check file is open or not
    jnc o1
    filerw 1,1,msg5,len5
    jmp exit
    o1:
    filerw 1,1,msg6,len6
    
    call pro1
    
    mov rax,3        ;CLOSE
    mov rdi,[fd_in]
    syscall    
    
jmp skip


p2:
    cmp al,32h
    jnz p3
    filerw 1,1,msg2,len2
        
    filerw 2,file1,2,0777    ;opening file
    mov [fd_in],rax
    
    bt rax,63        ;check file is open or not
    jnc o2
    filerw 1,1,msg5,len5
    jmp exit
    o2:
    filerw 1,1,msg6,len6
    
    call pro2

    mov rax,3        ;CLOSE
    mov rdi,[fd_in]
    syscall    
    
jmp skip


p3:
    cmp al,33h
    jnz skip
    filerw 1,1,msg3,len3
        
    filerw 2,file1,2,0777    ;opening file
    mov [fd_in],rax
    
    bt rax,63        ;check file is open or not
    jnc o3
    filerw 1,1,msg5,len5
    jmp exit
    o3:
    filerw 1,1,msg6,len6
    
    call pro3
    
    mov rax,3        ;CLOSE
    mov rdi,[fd_in]
    syscall    
    
jmp skip


;exit call
exit:

    mov rax,60
    mov rdi,0
    syscall


;hex to ascii
htoa:
    mov rcx,03h
    mov rdi,num1
    xor rbx,rbx
    
    up1:
        rol dl,4
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
    

part 2

%macro filerw 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

extern htoa
global pro1
global pro2
global pro3
extern fd_in
extern num1

section .data

    nxtline db "",10
    len equ $-nxtline
    msg1 db "1.No of Occurrences",10
    len1 equ $-msg1
    msg2 db "2.No. of Spaces",10
    len2 equ $-msg2
    msg4 db "4.EXIT",10
    len4 equ $-msg4
    msg3 db "3.No. of newlines",10
    len3 equ $-msg3
    msg5 db "File Not Open"
    len5 equ $-msg5
    msg6 db "File Opened",10
    len6 equ $-msg6
    file1 db "file.txt",0
    msg7 db "Enter character",10
    len7 equ $-msg7

section .bss

    count resb 1    ;stores no of characters in file
    cha resb 2    ;stores the input character
    Buffer resb 100    ;stores the data in file
    space resb 1    
    entr resb 1
    no resb 1    ;stores no of occurrences

section .text

pro1:
    filerw 0,[fd_in],Buffer,100    ;read file*****
    
    mov [count],al    ;moving no. of characters to count
    filerw 1,1,msg7,len7
    filerw 0,1,cha,2    ;inputing character

    xor rax,rax
    mov al,byte[cha]

    mov rsi,Buffer
    
    repeat1:    
        cmp al,byte[rsi]
        jne c1
        inc byte[no]
    
        c1:
        dec byte[count]
        
        inc rsi
        cmp byte[count],00h
        jnz repeat1

    mov dl,byte[no]
    call htoa    
    filerw 1,1,num1,2    
    mov byte[no],0
ret


pro2:

    filerw 0,[fd_in],Buffer,100    ;read file*****
    
    mov [count],al    ;moving no. of characters to count
    
    mov rsi,Buffer
    
    repeat2:    
        mov al,byte[rsi]
        cmp al,20h
        jne c2
        inc byte[space]
    
        c2:
        dec byte[count]
        
        inc rsi
        cmp byte[count],00h
        jnz repeat2
        
    mov dl,byte[space]
    call htoa    
    filerw 1,1,num1,2
    mov byte[space],0
    ret


pro3:

    filerw 0,[fd_in],Buffer,100    ;read file*****

    mov [count],al    ;moving no. of characters to count
    
    mov rsi,Buffer
    
    repeat3:    
        mov al,byte[rsi]
        cmp al,0x0A
        jne c3
        inc byte[entr]
    
        c3:
        dec byte[count]
        
        inc rsi
        cmp byte[count],00h
        jnz repeat3
    
    mov dl,byte[entr]
    call htoa    
    filerw 1,1,num1,2
    mov byte[entr],0
    ret

