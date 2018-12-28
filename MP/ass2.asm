%macro readwrite 3
mov rax,%1
mov rdi,1
mov rsi,%2
mov rdx,%3
syscall
%endmacro

section .data

    count db 0Ah
    msg0 db "0.Display array",10
    len0 equ $-msg0
    msg1 db "1.Non-overlapping without string instn",10
    len1 equ $-msg1
    msg2 db "2.Overlapping without string instn",10
    len2 equ $-msg2
    msg3 db "3.Non-overlapping with string instn",10
    len3 equ $-msg3
    msg4 db "4.Overlapping with string instn",10
    len4 equ $-msg4
    msg db "Enter valid option",10
    len equ $-msg
    msg5 db " - "
    len5 equ $-msg5
    msg6 db " ",10
    len6 equ $-msg6

array dq 0FFAAFFAAA2345678h,876543219ABCDEAFh,0ABCDEAF55B793888h,12312312FFEEEEFFh,0ABCDEAF512312312h,0CDEA1111D231EEEFh,45B7CDEA12315B79h,2345678923456789h,3405678903456789h,0ABCDEAFF12345678h


section .bss

    num1 resb 2
    num3 resq 1
    num4 resq 1
    num5 resq 1
    count2 resb 1


global _start
section .text
_start:

skip:

    readwrite 1,msg0,len0
    readwrite 1,msg1,len1
    readwrite 1,msg2,len2
    readwrite 1,msg3,len3
    readwrite 1,msg4,len4
    readwrite 1,msg,len


readwrite 0,num1,2
mov al,byte[num1]

cmp al,35h
jz exit


cmp al,30h
jnz p1        ;***
mov rsi,array
call printarray1


p1:

    cmp al,31h
    jnz p2        ;***
    readwrite 1,msg1,len1

    mov rsi,array
    call printarray1

    call procedure1

    readwrite 1,msg6,len6

    mov rsi,array
    add rsi,120

    call printarray1

jmp skip

p2:
    
    cmp al,32h
    jnz p3        ;***
    readwrite 1,msg2,len2

    mov rsi,array
    call printarray1

    call procedure2

    readwrite 1,msg6,len6

    mov rsi,array
    add rsi,40
    call printarray1

jmp skip

p3:
    
    cmp al,33h
    jnz p4        ;***
    readwrite 1,msg3,len3

    mov rsi,array
    call printarray1

    readwrite 1,msg6,len6
    
    call procedure3
    mov rsi,array
    add rsi,120
    call printarray1

jmp skip

p4:

    cmp al,34h
    jnz skip
    readwrite 1,msg4,len4

    mov rsi,array
    call printarray1

    readwrite 1,msg6,len6

    call procedure4
    mov rsi,array
    add rsi,60
    call printarray1

jmp skip

;exit call
exit:

    mov rax,60
    mov rdi,0
    syscall

;hex to ascii
htoa:
    xor rcx,rcx
    mov rcx,16
    mov rdi,num4
    
    up1:
        rol rax,4
        mov bl,al
        and bl,0Fh
        cmp bl,09h
        jbe up2
        add bl,07h
    
    up2:
        add bl,30h
        mov [rdi],bl
        inc rdi
        loop up1
        ret


;procedure 1 non-overlapping without string
procedure1:

    mov rsi,array
    mov rdi,array
    mov cl,byte[count]  ;**************
    ;8*10=80 + 40 extra
    add rdi,120
    x1:
    mov rax,[rsi]
    mov [rdi],rax
    add rsi,8
    add rdi,8
    dec cl
    jnz x1
    ret


;procedure 2 overlapping without string instn
procedure2:

    mov rsi,array
    mov rdi,rsi
    mov cl,byte[count]      ;**************
    ;8*10=80 40+80=120 extra
    add rdi,112
    add rsi,72
    x2:
    and qword[rdi],0
    mov rax,[rsi]
    mov [rdi],rax
    sub rsi,8
    sub rdi,8
    dec cl
    jnz x2
    ret
    

;non overlapping with string instruction

procedure3:
    mov rsi,array
    mov rdi,rsi
    add rdi,120
    ;8*10=80 + 40 extra
    cld        ;***********
    mov rcx,0Ah     ;**************
    rep movsq 

    ret


;overlapping with string instruction
procedure4:

    mov rsi,array
    mov rdi,rsi
    ;8*10=80 60+80=140 extra
    add rdi,132
    add rsi,72
    std
    mov rcx,0Ah      ;**************
    rep movsq 

    ret

printarray1:

    mov byte[count2],20
    
    rep1:
    
        mov qword[num3],rsi
        mov rax,qword[num3]  ;address shifted to rax 

        call htoa
        readwrite 1,num4,16
        readwrite 1,msg5,len5

        mov rsi,qword[num3]
        mov rax,[rsi]         ;content of rsi into rax

        mov qword[num3],rsi
        call htoa
        readwrite 1,num4,16
        readwrite 1,msg6,len6
        mov rsi,qword[num3]
        add rsi,8
        dec byte[count2]
        jnz rep1
        ret

