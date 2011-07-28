.data
one:
.quad 1
zero:
.quad 0
minusOne:
.quad -1
.text
.globl mostSignificantOnePosition
mostSignificantOnePosition:
	bsrq %rdi, %rax
	cmovzq minusOne, %rax
	ret

.globl leastSignificantOnePosition
leastSignificantOnePosition:
	bsfq %rdi, %rax
	cmovzq minusOne, %rax
	ret

.globl mostSignificantZeroPosition
mostSignificantZeroPosition:
	neg %rdi
	dec %rdi
	call mostSignificantOnePosition
	ret

.globl leastSignificantZeroPosition
leastSignificantZeroPosition:
	neg %rdi
	dec %rdi
	call leastSignificantOnePosition
	ret

.globl isNot2Power
isNot2Power:
	movq %rdi, %rax
	subq $1, %rdi
	andq %rdi, %rax
	ret

.globl copyMemory
copyMemory:
	pushq %rcx
	movq %rdx, %rcx
	shrq $3, %rcx
	rep
	movsq
	movq %rdx, %rcx
	andq $7, %rcx
	rep
	movsb
	popq %rcx
	ret
