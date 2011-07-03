.data
.text
.macro kernel A
	movq %rcx, %r10
	movq $\A, %rax
	syscall
.endm

// Processes handling
.globl OSclone
OSclone:
	pushq %rdi
	pushq %rsi
	pushq %rdx
	movq _allocatorForStack, %rdi
	call AllocatorForStack_New
	movq %rax, %rsi
	popq %rcx
	popq %rdx
	popq %rdi
	kernel 56
	test %rax, %rax
	jnz 0f
	pushq %rdx
	pushq %r10
	movq _threadManager, %rdi
	call ThreadManager_RegisterCurrentThread
	popq %rdi
	popq %rax
	call *%rax
	xorq %rdi, %rdi
	jmp OSexit
0:
	ret

.globl OSgetpid
OSgetpid:
	kernel 39
	ret

.globl OSexit
OSexit:
	kernel 60
	ret

.globl OSwait4
OSwait4:
	kernel 61
	ret

// Signals
.globl OSkill
OSkill:
	kernel 62
	ret

// Files handling
.globl OSfileOpen
OSfileOpen:
	kernel 2
	ret
.globl OSfileClose
OSfileClose:
	kernel 3
	ret
.globl OSfileRead
OSfileRead:
	kernel 0
	ret
.globl OSfileWrite
OSfileWrite:
	kernel 1
	ret
.globl OSfileSeek
OSfileSeek:
	kernel 8
	ret
.globl OSfileTruncate
OSfileTruncate:
	kernel 77
	ret

// Mappings handling
.globl OSmappingMap
OSmappingMap:
	kernel 9
	ret
.globl OSmappingUnmap
OSmappingUnmap:
	kernel 11
	ret
