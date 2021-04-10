.text
.global __cp_begin
.hidden __cp_begin
.global __cp_end
.hidden __cp_end
.global __cp_cancel
.hidden __cp_cancel
.hidden __cancel
.global __syscall_cp_asm
.hidden __syscall_cp_asm
.type   __syscall_cp_asm,@function
__syscall_cp_asm:

__cp_begin:
	mov (%rdi),%eax
	test %eax,%eax
	jnz __cp_cancel
	mov %rdi,%r11
	mov %rsi,%rax
	mov %rdx,%rdi
	mov %rcx,%rsi
	mov %r8,%rdx
	mov %r9,%r10
	mov 8(%rsp),%r8
	mov 16(%rsp),%r9
	mov %r11,8(%rsp)
	mov %cs, %rcx
	test $3, %cl
	je __kerncall
	syscall
	jmp __cp_end
__kerncall:
	callq *kerncall_gate(%rip)
	.p2align 4
	nop
	.p2align 4
__cp_end:
	ret
__cp_cancel:
	jmp __cancel
