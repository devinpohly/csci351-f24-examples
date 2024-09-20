	.file	"swap.c"
	.text
	.globl	swap
	.type	swap, @function
swap:
.LFB0:
	.cfi_startproc
	movq	(%rdi), %rax
	movq	(%rsi), %rdx
	movq	%rdx, (%rdi)
	movq	%rax, (%rsi)
	sall	$3, %eax
	addl	(%rdi), %eax
	addl	$19, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	swap, .-swap
	.globl	math
	.type	math, @function
math:
.LFB1:
	.cfi_startproc
	imulq	%rdi, %rdx
	salq	$2, %rdx
	subq	%rsi, %rdx
	leaq	(%rdx,%rdi,2), %rax
	ret
	.cfi_endproc
.LFE1:
	.size	math, .-math
	.ident	"GCC: (GNU) 14.2.1 20240805"
	.section	.note.GNU-stack,"",@progbits
