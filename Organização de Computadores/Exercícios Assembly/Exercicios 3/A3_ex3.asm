	.data
matriz:		.word 12,-1,51,-1,-1,84,84,54,-1,52,-1,42,1,-1,48,-95
linhas:		.word 4
colunas:	.word 4

	.text
main:
	la a0, matriz
	la a1, linhas
	lw a1, 0(a1)
	la a2, colunas
	lw a2, 0(a2)
	
	jal	f_conta_matriz
	
	j	fim
f_conta_matriz:
	mul t0, a1,a2
	addi t2, zero, -1
loop_interno_imp:
	ble t0, zero, return
	lw t1, (a0)
	
	beq t1, t2, if
retif:
	addi a0, a0, 4
	addi t0, t0, -1
	j	loop_interno_imp
return:
	mul a0, a0, zero
	mv a0,t3
	ret
if:	
	addi t3, t3, 1
	j	retif
fim:
	nop
