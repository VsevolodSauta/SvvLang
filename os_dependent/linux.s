.data
.text
.macro kernel A
	movq %rcx, %r10
	movq $\A, %rax
	syscall
.endm
// ; Processes handling
.globl OSexit
OSexit:
	kernel 60
	ret
// ; Files handling
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

// ; Mappings handling
.globl OSmappingMap
OSmappingMap:
	kernel 9
	ret
.globl OSmappingUnmap
OSmappingUnmap:
	kernel 11
	ret
