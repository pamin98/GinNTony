	.text
	.file	"program"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$40, %edi
	callq	GC_malloc@PLT
	xorl	%ecx, %ecx
	.p2align	4, 0x90
.LBB0_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	leaq	1(%rcx), %rdx
	movl	%edx, %esi
	imull	%ecx, %esi
	movl	%esi, (%rax,%rcx,4)
	cmpl	$10, %edx
	movq	%rdx, %rcx
	jl	.LBB0_1
# %bb.2:                                # %after
	movl	24(%rax), %edi
	callq	writeInteger@PLT
	movl	$.L__unnamed_1, %edi
	callq	writeString@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"\"\\n\""
	.size	.L__unnamed_1, 5

	.section	".note.GNU-stack","",@progbits
