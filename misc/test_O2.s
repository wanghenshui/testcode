	.file	"test_O2.cpp"
	.section	.text.unlikely,"x"
LCOLDB0:
	.text
LHOTB0:
	.p2align 4,,15
	.globl	__Z2f1i
	.def	__Z2f1i;	.scl	2;	.type	32;	.endef
__Z2f1i:
LFB7:
	.cfi_startproc
	rep ret
	.cfi_endproc
LFE7:
	.section	.text.unlikely,"x"
LCOLDE0:
	.text
LHOTE0:
	.section	.text.unlikely,"x"
LCOLDB1:
	.text
LHOTB1:
	.p2align 4,,15
	.globl	__Z2f2i
	.def	__Z2f2i;	.scl	2;	.type	32;	.endef
__Z2f2i:
LFB2:
	.cfi_startproc
	rep ret
	.cfi_endproc
LFE2:
	.section	.text.unlikely,"x"
LCOLDE1:
	.text
LHOTE1:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section	.text.unlikely,"x"
LCOLDB2:
	.section	.text.startup,"x"
LHOTB2:
	.p2align 4,,15
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	call	___main
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE3:
	.section	.text.unlikely,"x"
LCOLDE2:
	.section	.text.startup,"x"
LHOTE2:
	.ident	"GCC: (GNU) 5.4.0"
