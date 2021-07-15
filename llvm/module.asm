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
	subq	$88, %rsp
	.cfi_def_cfa_offset 112
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	leaq	46(%rsp), %r14
	movl	$.L__unnamed_1, %edi
	movq	%r14, %rsi
	callq	swapString@PLT
	movl	$.L__unnamed_2, %edi
	callq	writeString@PLT
	movl	$.L__unnamed_3, %edi
	callq	writeString@PLT
	movq	%r14, %rdi
	callq	writeString@PLT
	movl	$.L__unnamed_4, %edi
	callq	writeString@PLT
	leaq	4(%rsp), %rbx
	movq	%r14, %rdi
	movq	%rbx, %rsi
	callq	swapString@PLT
	movl	$.L__unnamed_5, %edi
	callq	writeString@PLT
	movq	%rbx, %rdi
	callq	writeString@PLT
	movl	$.L__unnamed_6, %edi
	callq	writeString@PLT
	addq	$88, %rsp
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
	.globl	swapString                      # -- Begin function swapString
	.p2align	4, 0x90
	.type	swapString,@function
swapString:                             # @swapString
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movq	%rdi, 16(%rsp)
	movq	%rsi, 8(%rsp)
	movl	$0, 4(%rsp)
	callq	length@PLT
	testl	%eax, %eax
	js	.LBB1_2
	.p2align	4, 0x90
.LBB1_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	movslq	4(%rsp), %rax
	movq	16(%rsp), %rcx
	movzbl	(%rcx,%rax), %ecx
	movq	8(%rsp), %rdx
	movb	%cl, (%rdx,%rax)
	movl	4(%rsp), %ebx
	incl	%ebx
	movl	%ebx, 4(%rsp)
	movq	16(%rsp), %rdi
	callq	length@PLT
	cmpl	%eax, %ebx
	jle	.LBB1_1
.LBB1_2:                                # %after
	movl	$0, 4(%rsp)
	movq	8(%rsp), %rdi
	callq	length@PLT
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	testl	%ecx, %ecx
	jle	.LBB1_4
	.p2align	4, 0x90
.LBB1_3:                                # %loop5
                                        # =>This Inner Loop Header: Depth=1
	movslq	4(%rsp), %rbx
	movq	8(%rsp), %rdi
	movq	%rbx, %r14
	addq	%rdi, %r14
	callq	length@PLT
	notl	%ebx
	addl	%eax, %ebx
	movslq	%ebx, %rsi
	addq	8(%rsp), %rsi
	movq	%r14, %rdi
	callq	swap@PLT
	movl	4(%rsp), %ebx
	incl	%ebx
	movl	%ebx, 4(%rsp)
	movq	8(%rsp), %rdi
	callq	length@PLT
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	cmpl	%ecx, %ebx
	jl	.LBB1_3
.LBB1_4:                                # %after12
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	swapString, .Lfunc_end1-swapString
	.cfi_endproc
                                        # -- End function
	.globl	length                          # -- Begin function length
	.p2align	4, 0x90
	.type	length,@function
length:                                 # @length
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -8(%rsp)
	movl	$0, -12(%rsp)
	cmpb	$39, (%rdi)
	je	.LBB2_2
	.p2align	4, 0x90
.LBB2_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	movl	-12(%rsp), %eax
	incl	%eax
	movl	%eax, -12(%rsp)
	cltq
	movq	-8(%rsp), %rcx
	cmpb	$39, (%rcx,%rax)
	jne	.LBB2_1
.LBB2_2:                                # %after
	movl	-12(%rsp), %eax
	retq
.Lfunc_end2:
	.size	length, .Lfunc_end2-length
	.cfi_endproc
                                        # -- End function
	.globl	swap                            # -- Begin function swap
	.p2align	4, 0x90
	.type	swap,@function
swap:                                   # @swap
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	movb	(%rdi), %al
	movb	%al, -17(%rsp)
	movb	(%rsi), %al
	movb	%al, (%rdi)
	movb	-17(%rsp), %al
	movq	-16(%rsp), %rcx
	movb	%al, (%rcx)
	retq
.Lfunc_end3:
	.size	swap, .Lfunc_end3-swap
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"\"Hello world!\""
	.size	.L__unnamed_1, 15

	.type	.L__unnamed_2,@object           # @1
.L__unnamed_2:
	.asciz	"\"Original String    : Hello world!\\n\""
	.size	.L__unnamed_2, 38

	.type	.L__unnamed_3,@object           # @2
.L__unnamed_3:
	.asciz	"\"Reverse String     : \""
	.size	.L__unnamed_3, 24

	.type	.L__unnamed_4,@object           # @3
.L__unnamed_4:
	.asciz	"\"\\n\""
	.size	.L__unnamed_4, 5

	.type	.L__unnamed_5,@object           # @4
.L__unnamed_5:
	.asciz	"\"Back from the dead : \""
	.size	.L__unnamed_5, 24

	.type	.L__unnamed_6,@object           # @5
.L__unnamed_6:
	.asciz	"\"\\n\""
	.size	.L__unnamed_6, 5

	.section	".note.GNU-stack","",@progbits
