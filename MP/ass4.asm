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
	msg1 db "1.Successive Addition",10
	len1 equ $-msg1
	msg2 db "2.Add and Shift",10
	len2 equ $-msg2
	msg5 db "3.EXIT",10
	len5 equ $-msg5
	msg3 db "Enter two hex numbers (00h-FFh)",10
	len3 equ $-msg3
	
	
section .bss
	
	num resb 2
	num1 resb 3
	num2 resb 3
	num5 resb 3
	num6 resb 3
	num3 resb 4
	num4 resb 4
	count resb 1
	
global _start
section .text
_start:

skip:

	readwrite 1,nxtline,len
	readwrite 1,msg1,len1
	readwrite 1,msg2,len2
	readwrite 1,msg5,len5

readwrite 0,num,2
mov al,byte[num]

cmp al,33h
jz exit


;Successive Addition
	cmp al,31h
	jnz p2
	readwrite 1,msg3,len3
	
	readwrite 0,num1,3
	mov rsi,num1
	call atoh
	
	mov byte[num1],al	

	readwrite 0,num2,3
	mov rsi,num2
	call atoh

	mov byte[num2],al
	
	call pro1
	
	mov rdi,num3
	call htoa
	
	readwrite 1,num3,4
	
	
jmp skip


;Add and shift
p2:
	cmp al,32h
	jnz skip
	readwrite 1,msg3,len3
		
	readwrite 0,num1,3
	mov rsi,num1
	call atoh
	
	mov byte[num1],al	

	readwrite 0,num2,3
	mov rsi,num2
	call atoh

	mov byte[num2],al
	
	call pro2
	
	mov rdi,num4
	call htoa
	
	readwrite 1,num4,4

jmp skip

;exit call
exit:

	mov rax,60
	mov rdi,0
	syscall

;ASCII to hex***********
atoh:

	mov rcx,2
	xor rbx,rbx
	xor rax,rax
	
	a1:
		rol al,4
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

;hex to ascii*************
htoa:
	mov rcx,4
	xor rbx,rbx

	up1:
		rol ax,4
		mov bl,al
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
	
;Successive addition
pro1:
	
	xor rdx,rdx
	xor rax,rax
	xor rcx,rcx
	mov cl,byte[num1]
	mov bl,byte[num2]
	
	s1:
		add rax,rbx
		loop s1
	
	ret

pro2:
	
	xor rbx,rbx
	xor rdx,rdx
	mov rcx,8
	mov dl,[num1]
	mov bl,[num2]
	xor rax,rax
	
	s3:
	
		shr rbx,1
		jnc s4
		add rax,rdx
		
	s4:
		shl rdx,1
		
		loop s3
	
	ret
	
	

		
	
	

