	.text
	.file	"program"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movq	(%rsp), %r14
	movl	$12, %edi
	callq	GC_malloc@PLT
	movq	%rax, %rbx
	movl	$6, 8(%rax)
	movq	%r14, (%rax)
	movq	%rax, (%rsp)
	movl	$12, %edi
	callq	GC_malloc@PLT
	movq	%rax, %r14
	movl	$5, 8(%rax)
	movq	%rbx, (%rax)
	movq	%rax, (%rsp)
	movl	$12, %edi
	callq	GC_malloc@PLT
	movq	%rax, %rbx
	movl	$4, 8(%rax)
	movq	%r14, (%rax)
	movq	%rax, (%rsp)
	movl	$12, %edi
	callq	GC_malloc@PLT
	movq	%rax, %r14
	movl	$3, 8(%rax)
	movq	%rbx, (%rax)
	movq	%rax, (%rsp)
	movl	$12, %edi
	callq	GC_malloc@PLT
	movq	%rax, %rbx
	movl	$2, 8(%rax)
	movq	%r14, (%rax)
	movq	%rax, (%rsp)
	movl	$12, %edi
	callq	GC_malloc@PLT
	movl	$1, 8(%rax)
	movq	%rbx, (%rax)
	movq	%rax, (%rsp)
	movl	(%rax), %edi
	callq	writeInteger@PLT
	movq	(%rsp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rsp)
	movl	8(%rax), %edi
	callq	writeInteger@PLT
	movq	(%rsp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rsp)
	movl	8(%rax), %edi
	callq	writeInteger@PLT
	movq	(%rsp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rsp)
	movl	8(%rax), %edi
	callq	writeInteger@PLT
	movq	(%rsp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rsp)
	movl	8(%rax), %edi
	callq	writeInteger@PLT
	movq	(%rsp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rsp)
	movl	8(%rax), %edi
	callq	writeInteger@PLT
	addq	$8, (%rsp)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
