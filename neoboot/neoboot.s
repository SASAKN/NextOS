	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.intel_syntax noprefix
	.globl	_PrintOK                        ## -- Begin function PrintOK
	.p2align	4, 0x90
_PrintOK:                               ## @PrintOK
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 2
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 8]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	lea	rsi, [rip + l_.str]
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 15
	call	rax
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_PrintWarn                      ## -- Begin function PrintWarn
	.p2align	4, 0x90
_PrintWarn:                             ## @PrintWarn
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 14
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 8]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	lea	rsi, [rip + l_.str.1]
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 15
	call	rax
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_PrintError                     ## -- Begin function PrintError
	.p2align	4, 0x90
_PrintError:                            ## @PrintError
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 4
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 8]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	lea	rsi, [rip + l_.str.2]
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 15
	call	rax
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_PrintGoodbye                   ## -- Begin function PrintGoodbye
	.p2align	4, 0x90
_PrintGoodbye:                          ## @PrintGoodbye
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 1
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 8]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	lea	rsi, [rip + l_.str.3]
	call	rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 64]
	mov	rax, qword ptr [rax + 40]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	mov	rdi, qword ptr [rcx + 64]
	mov	esi, 15
	call	rax
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_print_efi_configuration_table  ## -- Begin function print_efi_configuration_table
	.p2align	4, 0x90
_print_efi_configuration_table:         ## @print_efi_configuration_table
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	lea	rdi, [rip + L_.str.4]
	mov	al, 0
	call	_printf
	mov	qword ptr [rbp - 8], 0
LBB4_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB4_3 Depth 2
	mov	rax, qword ptr [rbp - 8]
	mov	rcx, qword ptr [rip + _ST@GOTPCREL]
	mov	rcx, qword ptr [rcx]
	cmp	rax, qword ptr [rcx + 104]
	jae	LBB4_8
## %bb.2:                               ##   in Loop: Header=BB4_1 Depth=1
	mov	rsi, qword ptr [rbp - 8]
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rdx, qword ptr [rax + 112]
	imul	rax, qword ptr [rbp - 8], 24
	add	rdx, rax
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 112]
	imul	rcx, qword ptr [rbp - 8], 24
	add	rax, rcx
	mov	ecx, dword ptr [rax]
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 112]
	imul	rdi, qword ptr [rbp - 8], 24
	add	rax, rdi
	movzx	r8d, word ptr [rax + 4]
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 112]
	imul	rdi, qword ptr [rbp - 8], 24
	add	rax, rdi
	movzx	r9d, word ptr [rax + 6]
	lea	rdi, [rip + L_.str.5]
	mov	al, 0
	call	_printf
	mov	byte ptr [rbp - 9], 0
LBB4_3:                                 ##   Parent Loop BB4_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movzx	eax, byte ptr [rbp - 9]
	cmp	eax, 8
	jge	LBB4_6
## %bb.4:                               ##   in Loop: Header=BB4_3 Depth=2
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 112]
	imul	rcx, qword ptr [rbp - 8], 24
	add	rax, rcx
	movzx	ecx, byte ptr [rbp - 9]
                                        ## kill: def $rcx killed $ecx
	movzx	esi, byte ptr [rax + rcx + 8]
	lea	rdi, [rip + L_.str.6]
	mov	al, 0
	call	_printf
## %bb.5:                               ##   in Loop: Header=BB4_3 Depth=2
	mov	al, byte ptr [rbp - 9]
	add	al, 1
	mov	byte ptr [rbp - 9], al
	jmp	LBB4_3
LBB4_6:                                 ##   in Loop: Header=BB4_1 Depth=1
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 112]
	imul	rcx, qword ptr [rbp - 8], 24
	add	rax, rcx
	mov	rsi, qword ptr [rax + 16]
	lea	rdi, [rip + L_.str.7]
	mov	al, 0
	call	_printf
## %bb.7:                               ##   in Loop: Header=BB4_1 Depth=1
	mov	rax, qword ptr [rbp - 8]
	add	rax, 1
	mov	qword ptr [rbp - 8], rax
	jmp	LBB4_1
LBB4_8:
	lea	rdi, [rip + L_.str.8]
	mov	al, 0
	call	_printf
	call	_PrintOK
	lea	rdi, [rip + L_.str.9]
	mov	al, 0
	call	_printf
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_get_memtype_name               ## -- Begin function get_memtype_name
	.p2align	4, 0x90
_get_memtype_name:                      ## @get_memtype_name
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	dword ptr [rbp - 12], edi
	mov	eax, dword ptr [rbp - 12]
                                        ## kill: def $rax killed $eax
	mov	qword ptr [rbp - 24], rax       ## 8-byte Spill
	sub	rax, 16
	ja	LBB5_17
## %bb.19:
	mov	rax, qword ptr [rbp - 24]       ## 8-byte Reload
	lea	rcx, [rip + LJTI5_0]
	movsxd	rax, dword ptr [rcx + 4*rax]
	add	rax, rcx
	jmp	rax
LBB5_1:
	lea	rax, [rip + L_.str.10]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_2:
	lea	rax, [rip + L_.str.11]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_3:
	lea	rax, [rip + L_.str.12]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_4:
	lea	rax, [rip + L_.str.13]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_5:
	lea	rax, [rip + L_.str.14]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_6:
	lea	rax, [rip + L_.str.15]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_7:
	lea	rax, [rip + L_.str.16]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_8:
	lea	rax, [rip + L_.str.17]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_9:
	lea	rax, [rip + L_.str.18]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_10:
	lea	rax, [rip + L_.str.19]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_11:
	lea	rax, [rip + L_.str.20]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_12:
	lea	rax, [rip + L_.str.21]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_13:
	lea	rax, [rip + L_.str.22]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_14:
	lea	rax, [rip + L_.str.23]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_15:
	lea	rax, [rip + L_.str.24]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_16:
	lea	rax, [rip + L_.str.25]
	mov	qword ptr [rbp - 8], rax
	jmp	LBB5_18
LBB5_17:
	lea	rax, [rip + L_.str.26]
	mov	qword ptr [rbp - 8], rax
LBB5_18:
	mov	rax, qword ptr [rbp - 8]
	pop	rbp
	ret
	.cfi_endproc
	.p2align	2, 0x90
	.data_region jt32
.set L5_0_set_1, LBB5_1-LJTI5_0
.set L5_0_set_2, LBB5_2-LJTI5_0
.set L5_0_set_3, LBB5_3-LJTI5_0
.set L5_0_set_4, LBB5_4-LJTI5_0
.set L5_0_set_5, LBB5_5-LJTI5_0
.set L5_0_set_6, LBB5_6-LJTI5_0
.set L5_0_set_7, LBB5_7-LJTI5_0
.set L5_0_set_8, LBB5_8-LJTI5_0
.set L5_0_set_9, LBB5_9-LJTI5_0
.set L5_0_set_10, LBB5_10-LJTI5_0
.set L5_0_set_11, LBB5_11-LJTI5_0
.set L5_0_set_12, LBB5_12-LJTI5_0
.set L5_0_set_13, LBB5_13-LJTI5_0
.set L5_0_set_14, LBB5_14-LJTI5_0
.set L5_0_set_15, LBB5_15-LJTI5_0
.set L5_0_set_17, LBB5_17-LJTI5_0
.set L5_0_set_16, LBB5_16-LJTI5_0
LJTI5_0:
	.long	L5_0_set_1
	.long	L5_0_set_2
	.long	L5_0_set_3
	.long	L5_0_set_4
	.long	L5_0_set_5
	.long	L5_0_set_6
	.long	L5_0_set_7
	.long	L5_0_set_8
	.long	L5_0_set_9
	.long	L5_0_set_10
	.long	L5_0_set_11
	.long	L5_0_set_12
	.long	L5_0_set_13
	.long	L5_0_set_14
	.long	L5_0_set_15
	.long	L5_0_set_17
	.long	L5_0_set_16
	.end_data_region
                                        ## -- End function
	.globl	_get_memory_map                 ## -- Begin function get_memory_map
	.p2align	4, 0x90
_get_memory_map:                        ## @get_memory_map
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 48
	mov	rax, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 8], rax
	mov	qword ptr [rbp - 16], rdi
	mov	rax, qword ptr [rip + _BS@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 56]
	mov	rdi, qword ptr [rbp - 16]
	add	rdi, 16
	mov	rdx, qword ptr [rbp - 16]
	add	rdx, 24
	mov	rcx, qword ptr [rbp - 16]
	add	rcx, 32
	xor	esi, esi
	mov	r8d, esi
	mov	rsi, r8
	call	rax
	mov	qword ptr [rbp - 24], rax
	movabs	rax, -9223372036854775803
	cmp	qword ptr [rbp - 24], rax
	jne	LBB6_2
## %bb.1:
	mov	rax, qword ptr [rbp - 16]
	cmp	qword ptr [rax + 16], 0
	jne	LBB6_4
LBB6_2:
	call	_PrintError
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rdi, qword ptr [rax + 72]
	lea	rsi, [rip + L_.str.27]
	mov	al, 0
	call	_fprintf
LBB6_3:                                 ## =>This Inner Loop Header: Depth=1
	## InlineAsm Start
	hlt
	## InlineAsm End
	jmp	LBB6_3
LBB6_4:
	mov	rax, qword ptr [rbp - 16]
	mov	rcx, qword ptr [rax + 16]
	mov	rdx, qword ptr [rax + 32]
	lea	rcx, [rcx + 4*rdx]
	mov	qword ptr [rax + 16], rcx
	mov	rax, qword ptr [rbp - 16]
	mov	rax, qword ptr [rax + 16]
	mov	rcx, rsp
	mov	qword ptr [rbp - 32], rcx
	mov	rdx, rax
	add	rdx, 15
	and	rdx, -16
	mov	rcx, rsp
	sub	rcx, rdx
	mov	rsp, rcx
	mov	qword ptr [rbp - 40], rax
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rax + 8], rcx
	mov	rax, qword ptr [rbp - 16]
	cmp	qword ptr [rax + 16], 0
	jne	LBB6_8
## %bb.5:
	call	_PrintError
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rdi, qword ptr [rax + 72]
	lea	rsi, [rip + L_.str.28]
	mov	al, 0
	call	_fprintf
LBB6_6:                                 ## =>This Inner Loop Header: Depth=1
	jmp	LBB6_7
LBB6_7:                                 ##   in Loop: Header=BB6_6 Depth=1
	## InlineAsm Start
	hlt
	## InlineAsm End
	jmp	LBB6_6
LBB6_8:
	mov	rax, qword ptr [rip + _BS@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 56]
	mov	rdi, qword ptr [rbp - 16]
	add	rdi, 16
	mov	rcx, qword ptr [rbp - 16]
	mov	rsi, qword ptr [rcx + 8]
	mov	rdx, qword ptr [rbp - 16]
	add	rdx, 24
	mov	rcx, qword ptr [rbp - 16]
	add	rcx, 32
	xor	r8d, r8d
                                        ## kill: def $r8 killed $r8d
	call	rax
	mov	qword ptr [rbp - 24], rax
	cmp	qword ptr [rbp - 24], 0
	jge	LBB6_12
## %bb.9:
	call	_PrintError
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rdi, qword ptr [rax + 72]
	lea	rsi, [rip + L_.str.27]
	mov	al, 0
	call	_fprintf
LBB6_10:                                ## =>This Inner Loop Header: Depth=1
	jmp	LBB6_11
LBB6_11:                                ##   in Loop: Header=BB6_10 Depth=1
	## InlineAsm Start
	hlt
	## InlineAsm End
	jmp	LBB6_10
LBB6_12:
	mov	rax, qword ptr [rbp - 16]
	mov	rax, qword ptr [rax + 16]
	mov	rcx, qword ptr [rbp - 16]
	xor	edx, edx
                                        ## kill: def $rdx killed $edx
	div	qword ptr [rcx + 32]
	mov	rcx, rax
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rax + 48], rcx
	call	_PrintOK
	lea	rdi, [rip + L_.str.29]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rbp - 32]
	mov	rsp, rax
	mov	rax, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rcx, qword ptr [rbp - 8]
	cmp	rax, rcx
	jne	LBB6_14
## %bb.13:
	xor	eax, eax
                                        ## kill: def $rax killed $eax
	mov	rsp, rbp
	pop	rbp
	ret
LBB6_14:
	call	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.globl	_print_memmap                   ## -- Begin function print_memmap
	.p2align	4, 0x90
_print_memmap:                          ## @print_memmap
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	rbx
	sub	rsp, 88
	.cfi_offset rbx, -24
	mov	qword ptr [rbp - 16], rdi
	lea	rdi, [rip + L_.str.30]
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.31]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rbp - 16]
	mov	rax, qword ptr [rax + 8]
	mov	qword ptr [rbp - 40], rax
	mov	dword ptr [rbp - 28], 0
LBB7_1:                                 ## =>This Inner Loop Header: Depth=1
	mov	eax, dword ptr [rbp - 28]
                                        ## kill: def $rax killed $eax
	mov	rcx, qword ptr [rbp - 16]
	cmp	rax, qword ptr [rcx + 48]
	jae	LBB7_4
## %bb.2:                               ##   in Loop: Header=BB7_1 Depth=1
	mov	eax, dword ptr [rbp - 28]
	mov	dword ptr [rbp - 60], eax       ## 4-byte Spill
	mov	rax, qword ptr [rbp - 40]
	mov	qword ptr [rbp - 56], rax       ## 8-byte Spill
	mov	rax, qword ptr [rbp - 40]
	mov	eax, dword ptr [rax]
	mov	dword ptr [rbp - 44], eax       ## 4-byte Spill
	mov	rax, qword ptr [rbp - 40]
	mov	edi, dword ptr [rax]
	call	_get_memtype_name
	mov	esi, dword ptr [rbp - 60]       ## 4-byte Reload
	mov	rdx, qword ptr [rbp - 56]       ## 8-byte Reload
	mov	ecx, dword ptr [rbp - 44]       ## 4-byte Reload
	mov	r8, rax
	mov	rax, qword ptr [rbp - 40]
	mov	r9, qword ptr [rax + 8]
	mov	rax, qword ptr [rbp - 40]
	mov	rbx, qword ptr [rax + 16]
	mov	rax, qword ptr [rbp - 40]
	mov	r11, qword ptr [rax + 24]
	mov	rax, qword ptr [rbp - 40]
	mov	r10, qword ptr [rax + 24]
	mov	rax, qword ptr [rbp - 40]
	mov	rax, qword ptr [rax + 32]
	lea	rdi, [rip + L_.str.32]
	mov	qword ptr [rsp], rbx
	mov	qword ptr [rsp + 8], r11
	mov	qword ptr [rsp + 16], r10
	mov	qword ptr [rsp + 24], rax
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rbp - 40]
	mov	rcx, qword ptr [rbp - 16]
	add	rax, qword ptr [rcx + 32]
	mov	qword ptr [rbp - 40], rax
## %bb.3:                               ##   in Loop: Header=BB7_1 Depth=1
	mov	eax, dword ptr [rbp - 28]
	add	eax, 1
	mov	dword ptr [rbp - 28], eax
	jmp	LBB7_1
LBB7_4:
	lea	rdi, [rip + L_.str.8]
	mov	al, 0
	call	_printf
	call	_PrintOK
	lea	rdi, [rip + L_.str.33]
	mov	al, 0
	call	_printf
	xor	eax, eax
                                        ## kill: def $rax killed $eax
	add	rsp, 88
	pop	rbx
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_save_memmap                    ## -- Begin function save_memmap
	.p2align	4, 0x90
_save_memmap:                           ## @save_memmap
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r14
	push	rbx
	sub	rsp, 112
	.cfi_offset rbx, -32
	.cfi_offset r14, -24
	mov	qword ptr [rbp - 24], rdi
	lea	rax, [rip + L_.str.31]
	mov	qword ptr [rbp - 40], rax
	mov	rax, qword ptr [rbp - 24]
	mov	rax, qword ptr [rax + 8]
	mov	qword ptr [rbp - 56], rax
	lea	rdi, [rip + L_.str.34]
	lea	rsi, [rip + L_.str.35]
	call	_fopen
	mov	qword ptr [rbp - 32], rax
	cmp	rax, 0
	je	LBB8_6
## %bb.1:
	mov	rdi, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 40]
	lea	rsi, [rip + L_.str.36]
	mov	al, 0
	call	_fprintf
	mov	dword ptr [rbp - 60], 0
LBB8_2:                                 ## =>This Inner Loop Header: Depth=1
	mov	eax, dword ptr [rbp - 60]
                                        ## kill: def $rax killed $eax
	mov	rcx, qword ptr [rbp - 24]
	cmp	rax, qword ptr [rcx + 48]
	jae	LBB8_5
## %bb.3:                               ##   in Loop: Header=BB8_2 Depth=1
	mov	rax, qword ptr [rbp - 32]
	mov	qword ptr [rbp - 88], rax       ## 8-byte Spill
	mov	eax, dword ptr [rbp - 60]
	mov	dword ptr [rbp - 76], eax       ## 4-byte Spill
	mov	rax, qword ptr [rbp - 56]
	mov	qword ptr [rbp - 72], rax       ## 8-byte Spill
	mov	rax, qword ptr [rbp - 56]
	mov	eax, dword ptr [rax]
	mov	dword ptr [rbp - 64], eax       ## 4-byte Spill
	mov	rax, qword ptr [rbp - 56]
	mov	edi, dword ptr [rax]
	call	_get_memtype_name
	mov	rdi, qword ptr [rbp - 88]       ## 8-byte Reload
	mov	edx, dword ptr [rbp - 76]       ## 4-byte Reload
	mov	rcx, qword ptr [rbp - 72]       ## 8-byte Reload
	mov	r8d, dword ptr [rbp - 64]       ## 4-byte Reload
	mov	r9, rax
	mov	rax, qword ptr [rbp - 56]
	mov	r14, qword ptr [rax + 8]
	mov	rax, qword ptr [rbp - 56]
	mov	rbx, qword ptr [rax + 16]
	mov	rax, qword ptr [rbp - 56]
	mov	r11, qword ptr [rax + 24]
	mov	rax, qword ptr [rbp - 56]
	mov	r10, qword ptr [rax + 24]
	mov	rax, qword ptr [rbp - 56]
	mov	rax, qword ptr [rax + 32]
	lea	rsi, [rip + L_.str.32]
	mov	qword ptr [rsp], r14
	mov	qword ptr [rsp + 8], rbx
	mov	qword ptr [rsp + 16], r11
	mov	qword ptr [rsp + 24], r10
	mov	qword ptr [rsp + 32], rax
	mov	al, 0
	call	_fprintf
	mov	rax, qword ptr [rbp - 56]
	mov	rcx, qword ptr [rbp - 24]
	add	rax, qword ptr [rcx + 32]
	mov	qword ptr [rbp - 56], rax
## %bb.4:                               ##   in Loop: Header=BB8_2 Depth=1
	mov	eax, dword ptr [rbp - 60]
	add	eax, 1
	mov	dword ptr [rbp - 60], eax
	jmp	LBB8_2
LBB8_5:
	jmp	LBB8_6
LBB8_6:
	mov	rdi, qword ptr [rbp - 32]
	call	_fclose
	call	_PrintOK
	lea	rdi, [rip + L_.str.37]
	mov	al, 0
	call	_printf
	xor	eax, eax
                                        ## kill: def $rax killed $eax
	add	rsp, 112
	pop	rbx
	pop	r14
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_test_memmap_file               ## -- Begin function test_memmap_file
	.p2align	4, 0x90
_test_memmap_file:                      ## @test_memmap_file
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	lea	rdi, [rip + L_.str.34]
	lea	rsi, [rip + L_.str.38]
	call	_fopen
	mov	qword ptr [rbp - 16], rax
	cmp	rax, 0
	je	LBB9_6
## %bb.1:
	mov	rdi, qword ptr [rbp - 16]
	xor	eax, eax
	mov	esi, eax
	mov	edx, 2
	call	_fseek
	mov	rdi, qword ptr [rbp - 16]
	call	_ftell
	mov	qword ptr [rbp - 32], rax
	mov	rdi, qword ptr [rbp - 16]
	xor	eax, eax
	mov	esi, eax
	xor	edx, edx
	call	_fseek
	mov	rsi, qword ptr [rbp - 32]
	lea	rdi, [rip + L_.str.39]
	mov	al, 0
	call	_printf
	mov	rdi, qword ptr [rbp - 32]
	add	rdi, 1
	call	_malloc
	mov	qword ptr [rbp - 24], rax
	cmp	qword ptr [rbp - 24], 0
	jne	LBB9_3
## %bb.2:
	call	_PrintError
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rdi, qword ptr [rax + 72]
	lea	rsi, [rip + L_.str.40]
	mov	al, 0
	call	_fprintf
	mov	qword ptr [rbp - 8], 1
	jmp	LBB9_8
LBB9_3:
	mov	rdi, qword ptr [rbp - 24]
	mov	rsi, qword ptr [rbp - 32]
	mov	rcx, qword ptr [rbp - 16]
	mov	edx, 1
	call	_fread
	mov	rax, qword ptr [rbp - 24]
	mov	rcx, qword ptr [rbp - 32]
	mov	byte ptr [rax + rcx], 0
	mov	rdi, qword ptr [rbp - 16]
	call	_fclose
	cmp	qword ptr [rbp - 32], 94
	ja	LBB9_5
## %bb.4:
	call	_PrintError
	lea	rdi, [rip + L_.str.41]
	mov	al, 0
	call	_printf
LBB9_5:
	mov	rdi, qword ptr [rbp - 24]
	call	_free
	jmp	LBB9_7
LBB9_6:
	call	_PrintError
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rdi, qword ptr [rax + 72]
	lea	rsi, [rip + L_.str.42]
	mov	al, 0
	call	_fprintf
	mov	qword ptr [rbp - 8], 0
	jmp	LBB9_8
LBB9_7:
	call	_PrintOK
	lea	rdi, [rip + L_.str.43]
	mov	al, 0
	call	_printf
	mov	qword ptr [rbp - 8], 0
LBB9_8:
	mov	rax, qword ptr [rbp - 8]
	add	rsp, 32
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_open_disk                      ## -- Begin function open_disk
	.p2align	4, 0x90
_open_disk:                             ## @open_disk
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 2096
	mov	rax, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 8], rax
	lea	rdi, [rip + L_.str.44]
	mov	al, 0
	call	_printf
	mov	dword ptr [rbp - 2092], 0
LBB10_1:                                ## =>This Inner Loop Header: Depth=1
	cmp	dword ptr [rbp - 2092], 10
	jge	LBB10_7
## %bb.2:                               ##   in Loop: Header=BB10_1 Depth=1
	lea	rdi, [rbp - 2080]
	mov	edx, dword ptr [rbp - 2092]
	lea	rsi, [rip + L_.str.45]
	mov	al, 0
	call	_sprintf
	lea	rsi, [rbp - 2080]
	lea	rdi, [rip + L_.str.46]
	mov	al, 0
	call	_printf
	lea	rdi, [rbp - 2080]
	lea	rsi, [rip + L_.str.38]
	call	_fopen
	mov	qword ptr [rbp - 2088], rax
	cmp	rax, 0
	je	LBB10_4
## %bb.3:                               ##   in Loop: Header=BB10_1 Depth=1
	lea	rdi, [rbp - 2064]
	xor	esi, esi
	mov	edx, 2048
	call	_memset
	lea	rdi, [rbp - 2064]
	mov	rcx, qword ptr [rbp - 2088]
	mov	esi, 2048
	mov	edx, 1
	call	_fread
	call	_PrintOK
	lea	rsi, [rbp - 2080]
	lea	rdi, [rip + L_.str.47]
	mov	al, 0
	call	_printf
	lea	rsi, [rbp - 2064]
	lea	rdi, [rip + L_.str.48]
	mov	al, 0
	call	_printf
	mov	rdi, qword ptr [rbp - 2088]
	call	_fclose
	jmp	LBB10_5
LBB10_4:                                ##   in Loop: Header=BB10_1 Depth=1
	lea	rdi, [rip + L_.str.49]
	mov	al, 0
	call	_printf
LBB10_5:                                ##   in Loop: Header=BB10_1 Depth=1
	jmp	LBB10_6
LBB10_6:                                ##   in Loop: Header=BB10_1 Depth=1
	mov	eax, dword ptr [rbp - 2092]
	add	eax, 1
	mov	dword ptr [rbp - 2092], eax
	jmp	LBB10_1
LBB10_7:
	lea	rdi, [rip + L_.str.8]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rcx, qword ptr [rbp - 8]
	cmp	rax, rcx
	jne	LBB10_9
## %bb.8:
	xor	eax, eax
                                        ## kill: def $rax killed $eax
	add	rsp, 2096
	pop	rbp
	ret
LBB10_9:
	call	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.globl	_load_kernel                    ## -- Begin function load_kernel
	.p2align	4, 0x90
_load_kernel:                           ## @load_kernel
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 48
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	qword ptr [rbp - 24], rdx
	call	_PrintOK
	lea	rdi, [rip + L_.str.50]
	mov	al, 0
	call	_printf
	mov	rdi, qword ptr [rbp - 8]
	xor	eax, eax
	mov	esi, eax
	mov	edx, 2
	call	_fseek
	mov	rdi, qword ptr [rbp - 8]
	call	_ftell
	mov	qword ptr [rbp - 24], rax
	mov	rdi, qword ptr [rbp - 8]
	xor	eax, eax
	mov	esi, eax
	xor	edx, edx
	call	_fseek
	mov	qword ptr [rbp - 32], 65536
	mov	rax, qword ptr [rip + _BS@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 40]
	mov	qword ptr [rbp - 40], rax       ## 8-byte Spill
	mov	rax, qword ptr [rbp - 24]
	add	rax, 4095
	mov	ecx, 4096
	cqo
	idiv	rcx
	mov	rdx, rax
	mov	rax, qword ptr [rbp - 40]       ## 8-byte Reload
	mov	esi, 2
	lea	rcx, [rbp - 32]
	mov	edi, esi
	call	rax
	cmp	qword ptr [rbp - 16], 0
	jne	LBB11_2
## %bb.1:
	call	_PrintError
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rdi, qword ptr [rax + 72]
	lea	rsi, [rip + L_.str.51]
	mov	al, 0
	call	_fprintf
LBB11_2:
	cmp	qword ptr [rbp - 24], 0
	jne	LBB11_4
## %bb.3:
	call	_PrintError
	lea	rdi, [rip + L_.str.52]
	mov	al, 0
	call	_printf
	call	_PrintError
	lea	rdi, [rip + L_.str.53]
	mov	al, 0
	call	_printf
	call	_PrintGoodbye
	lea	rdi, [rip + L_.str.54]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rip + _RT@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	edi, 2
	xor	ecx, ecx
                                        ## kill: def $rcx killed $ecx
	mov	rsi, rcx
	mov	rdx, rcx
	call	qword ptr [rax + 104]
	jmp	LBB11_5
LBB11_4:
	lea	rdi, [rip + L_.str.55]
	mov	al, 0
	call	_printf
	mov	rsi, qword ptr [rbp - 24]
	lea	rdi, [rip + L_.str.56]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rbp - 16]
	movzx	esi, word ptr [rax + 16]
	lea	rdi, [rip + L_.str.57]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rbp - 16]
	mov	rsi, qword ptr [rax + 24]
	lea	rdi, [rip + L_.str.58]
	mov	al, 0
	call	_printf
LBB11_5:
	mov	rdi, qword ptr [rbp - 16]
	mov	rsi, qword ptr [rbp - 24]
	mov	rcx, qword ptr [rbp - 8]
	mov	edx, 1
	call	_fread
	mov	rdi, qword ptr [rbp - 8]
	call	_fclose
	xor	eax, eax
                                        ## kill: def $rax killed $eax
	add	rsp, 48
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_open_root_dir                  ## -- Begin function open_root_dir
	.p2align	4, 0x90
_open_root_dir:                         ## @open_root_dir
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	qword ptr [rbp - 24], rdx
	mov	qword ptr [rbp - 32], rcx
	lea	rdi, [rip + L_.str.59]
	call	_opendir
	mov	qword ptr [rbp - 32], rax
	cmp	rax, 0
	je	LBB12_5
## %bb.1:
	call	_PrintOK
	lea	rdi, [rip + L_.str.60]
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.61]
	lea	rsi, [rip + L_.str.38]
	call	_fopen
	mov	qword ptr [rbp - 24], rax
	cmp	rax, 0
	je	LBB12_3
## %bb.2:
	mov	rdi, qword ptr [rbp - 24]
	mov	rsi, qword ptr [rbp - 8]
	mov	rdx, qword ptr [rbp - 16]
	call	_load_kernel
	jmp	LBB12_4
LBB12_3:
	call	_PrintError
	lea	rdi, [rip + L_.str.53]
	mov	al, 0
	call	_printf
	call	_PrintGoodbye
	lea	rdi, [rip + L_.str.54]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rip + _RT@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	edi, 2
	xor	ecx, ecx
                                        ## kill: def $rcx killed $ecx
	mov	rsi, rcx
	mov	rdx, rcx
	call	qword ptr [rax + 104]
LBB12_4:
	jmp	LBB12_6
LBB12_5:
	call	_PrintError
	lea	rdi, [rip + L_.str.62]
	mov	al, 0
	call	_printf
	call	_PrintGoodbye
	lea	rdi, [rip + L_.str.54]
	mov	al, 0
	call	_printf
	mov	rax, qword ptr [rip + _RT@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	edi, 2
	xor	ecx, ecx
                                        ## kill: def $rcx killed $ecx
	mov	rsi, rcx
	mov	rdx, rcx
	call	qword ptr [rax + 104]
LBB12_6:
	xor	eax, eax
                                        ## kill: def $rax killed $eax
	add	rsp, 32
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 192
	mov	dword ptr [rbp - 4], 0
	mov	dword ptr [rbp - 8], edi
	mov	qword ptr [rbp - 16], rsi
	mov	rax, qword ptr [rip + _ST@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax + 96]
	xor	ecx, ecx
                                        ## kill: def $rcx killed $ecx
	mov	rdi, rcx
	mov	rsi, rcx
	mov	rdx, rcx
	call	qword ptr [rax + 256]
	call	_PrintOK
	lea	rdi, [rip + L_.str.63]
	mov	al, 0
	call	_printf
	call	_print_efi_configuration_table
	mov	qword ptr [rbp - 64], 0
	mov	qword ptr [rbp - 56], 0
	mov	qword ptr [rbp - 48], 0
	lea	rdi, [rbp - 80]
	call	_get_memory_map
	lea	rdi, [rbp - 80]
	call	_print_memmap
	lea	rdi, [rbp - 80]
	call	_save_memmap
	call	_test_memmap_file
	call	_open_disk
	mov	rdi, qword ptr [rbp - 112]
	mov	rsi, qword ptr [rbp - 104]
	mov	rdx, qword ptr [rbp - 88]
	mov	rcx, qword ptr [rbp - 96]
	call	_open_root_dir
LBB13_1:                                ## =>This Inner Loop Header: Depth=1
	## InlineAsm Start
	hlt
	## InlineAsm End
	jmp	LBB13_1
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__const
	.p2align	2, 0x0                          ## @.str
l_.str:
	.long	91                              ## 0x5b
	.long	32                              ## 0x20
	.long	79                              ## 0x4f
	.long	75                              ## 0x4b
	.long	32                              ## 0x20
	.long	93                              ## 0x5d
	.long	0                               ## 0x0

	.p2align	2, 0x0                          ## @.str.1
l_.str.1:
	.long	91                              ## 0x5b
	.long	32                              ## 0x20
	.long	87                              ## 0x57
	.long	97                              ## 0x61
	.long	114                             ## 0x72
	.long	110                             ## 0x6e
	.long	32                              ## 0x20
	.long	93                              ## 0x5d
	.long	0                               ## 0x0

	.p2align	2, 0x0                          ## @.str.2
l_.str.2:
	.long	91                              ## 0x5b
	.long	32                              ## 0x20
	.long	69                              ## 0x45
	.long	114                             ## 0x72
	.long	114                             ## 0x72
	.long	111                             ## 0x6f
	.long	114                             ## 0x72
	.long	32                              ## 0x20
	.long	33                              ## 0x21
	.long	32                              ## 0x20
	.long	93                              ## 0x5d
	.long	0                               ## 0x0

	.p2align	2, 0x0                          ## @.str.3
l_.str.3:
	.long	91                              ## 0x5b
	.long	32                              ## 0x20
	.long	71                              ## 0x47
	.long	111                             ## 0x6f
	.long	111                             ## 0x6f
	.long	100                             ## 0x64
	.long	66                              ## 0x42
	.long	121                             ## 0x79
	.long	101                             ## 0x65
	.long	32                              ## 0x20
	.long	33                              ## 0x21
	.long	32                              ## 0x20
	.long	93                              ## 0x5d
	.long	0                               ## 0x0

	.section	__TEXT,__cstring,cstring_literals
L_.str.4:                               ## @.str.4
	.asciz	"\n[ INFO ] EfiConfigurationTable\n"

L_.str.5:                               ## @.str.5
	.asciz	"%02d : %016x : %08x, %04x, %04x\n"

L_.str.6:                               ## @.str.6
	.asciz	"%02x"

L_.str.7:                               ## @.str.7
	.asciz	"%016x\n"

L_.str.8:                               ## @.str.8
	.asciz	"\n"

L_.str.9:                               ## @.str.9
	.asciz	"VendorTable\n"

L_.str.10:                              ## @.str.10
	.asciz	"EfiReservedMemoryType"

L_.str.11:                              ## @.str.11
	.asciz	"EfiLoaderCode"

L_.str.12:                              ## @.str.12
	.asciz	"EfiLoaderData"

L_.str.13:                              ## @.str.13
	.asciz	"EfiBootServicesCode"

L_.str.14:                              ## @.str.14
	.asciz	"EfiBootServicesData"

L_.str.15:                              ## @.str.15
	.asciz	"EfiRuntimeServicesCode"

L_.str.16:                              ## @.str.16
	.asciz	"EfiRuntimeServicesData"

L_.str.17:                              ## @.str.17
	.asciz	"EfiConventionalMemory"

L_.str.18:                              ## @.str.18
	.asciz	"EfiUnusableMemory"

L_.str.19:                              ## @.str.19
	.asciz	"EfiACPIReclaimMemory"

L_.str.20:                              ## @.str.20
	.asciz	"EfiACPIMemoryNVS"

L_.str.21:                              ## @.str.21
	.asciz	"EfiMemoryMappedIO"

L_.str.22:                              ## @.str.22
	.asciz	"EfiMemoryMappedIOPortSpace"

L_.str.23:                              ## @.str.23
	.asciz	"EfiPalCode"

L_.str.24:                              ## @.str.24
	.asciz	"EfiPersistentMemory"

L_.str.25:                              ## @.str.25
	.asciz	"EfiMaxMemoryType"

L_.str.26:                              ## @.str.26
	.asciz	"InvalidMemoryType"

L_.str.27:                              ## @.str.27
	.asciz	"Unable to Get Memory Map !\n"

L_.str.28:                              ## @.str.28
	.asciz	"unable to allocate memory. \n"

L_.str.29:                              ## @.str.29
	.asciz	"Get Memory Map\n"

L_.str.30:                              ## @.str.30
	.asciz	"\n[ INFO ] MemoryMap\n"

L_.str.31:                              ## @.str.31
	.asciz	"Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Size,  Attribute\n"

L_.str.32:                              ## @.str.32
	.asciz	"%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x \n"

L_.str.33:                              ## @.str.33
	.asciz	"Print Memory Map\n"

L_.str.34:                              ## @.str.34
	.asciz	"\\memmap"

L_.str.35:                              ## @.str.35
	.asciz	"a"

L_.str.36:                              ## @.str.36
	.asciz	"%s"

L_.str.37:                              ## @.str.37
	.asciz	"Save Memory Map\n"

L_.str.38:                              ## @.str.38
	.asciz	"r"

L_.str.39:                              ## @.str.39
	.asciz	"[ INFO ] Memory Map File Size : %d bytes.\n"

L_.str.40:                              ## @.str.40
	.asciz	"unable to allocate memory.\n"

L_.str.41:                              ## @.str.41
	.asciz	"Save File\n"

L_.str.42:                              ## @.str.42
	.asciz	"unable to open file\n"

L_.str.43:                              ## @.str.43
	.asciz	"Read Memory Map file\n"

L_.str.44:                              ## @.str.44
	.asciz	"\n[ INFO ] Block Device \n"

L_.str.45:                              ## @.str.45
	.asciz	"/dev/disk%d"

L_.str.46:                              ## @.str.46
	.asciz	"trying to open '%s' "

L_.str.47:                              ## @.str.47
	.asciz	"open '%s'\n"

L_.str.48:                              ## @.str.48
	.asciz	"%1D"

L_.str.49:                              ## @.str.49
	.asciz	"nothing\n"

L_.str.50:                              ## @.str.50
	.asciz	"Exists a kernel file \n"

L_.str.51:                              ## @.str.51
	.asciz	"Failed to allocate memory\n"

L_.str.52:                              ## @.str.52
	.asciz	"Kernel File Size : 0 byte\n"

L_.str.53:                              ## @.str.53
	.asciz	"Open Kernel File \n"

L_.str.54:                              ## @.str.54
	.asciz	"Your computer is shutting down ...\n"

L_.str.55:                              ## @.str.55
	.asciz	"[ INFO ] Kernel File Info\n"

L_.str.56:                              ## @.str.56
	.asciz	"  File Size : %ld bytes\n"

L_.str.57:                              ## @.str.57
	.asciz	"  ELF Type : %ld\n"

L_.str.58:                              ## @.str.58
	.asciz	"  ELF Entry Address : 0x%x\n"

L_.str.59:                              ## @.str.59
	.asciz	"\\neos"

L_.str.60:                              ## @.str.60
	.asciz	"Exists a root directory\n"

L_.str.61:                              ## @.str.61
	.asciz	"\\neos\\kernel\\kernel.elf"

L_.str.62:                              ## @.str.62
	.asciz	"Open root directory \n"

L_.str.63:                              ## @.str.63
	.asciz	"Welcome to Neo Boot !\n"

.subsections_via_symbols
