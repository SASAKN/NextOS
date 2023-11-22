	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.intel_syntax noprefix
	.globl	_KernelMain                     ## -- Begin function KernelMain
	.p2align	4, 0x90
_KernelMain:                            ;## @KernelMain
	.cfi_startproc
; ## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	jmp	LBB0_1
; LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	; ## InlineAsm Start
	hlt
	; ## InlineAsm End
	jmp	LBB0_1
	.cfi_endproc
                                        ; ## -- End function
.subsections_via_symbols
