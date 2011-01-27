.data
.text
.globl Method_Invoke
Method_Invoke:
	movq (%rdi), %rbx
	movq %rsi, %rdi
	movq %rdx, %rsi
	movq %rcx, %rdx
	movq %r8, %rdx
	movq %r9, %r8
	jmp *%rbx
