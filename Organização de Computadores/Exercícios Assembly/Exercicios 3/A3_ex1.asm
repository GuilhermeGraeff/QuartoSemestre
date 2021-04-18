	.data
ladoA:		.word 16
ladoB:		.word 12
ladoC:		.word 14
strA:	.string	" Digite o valor de A\n"
strB:	.string	" Digite o valor de B\n"
strC:	.string	" Digite o valor de C\n"
possible:	.string	" É possível fazer um triângulo usando A, B e C como lados!\n"
impossible:	.string	" É impossível fazer um triângulo usando A, B e C como lados!\n"

	.text
main:	
	li	a7, 4
	la	a0, strA
	ecall
	li	a7, 5 
	ecall	
	mv	t0, a0

	li	a7, 4
	la	a0, strB
	ecall
	li	a7, 5 
	ecall	
	mv	t1, a0
	
	li	a7, 4
	la	a0, strC
	ecall
	li	a7, 5 
	ecall	
	mv	t2, a0
	#Até aqui o programa fez a leitura das entradas.
	
	mv	a0, t0
	mv	a1, t1
	mv	a2, t2
	
	jal	isTriangle
	
	j	fim
isTriangle:
	bgt 	a0, a1, ifab
	bgt	a1, a2, ifbc
	addi	a3, zero, 3
comeBack:
	addi	t4, zero, 1
	addi	t5, zero, 2
	addi	t6, zero, 3
	
	beq	a3, t4, Aicbigger
	beq	a3, t5, Bicbigger
	beq	a3, t6, Cicbigger
Aicbigger:
	add	a4, a1, a2
	bgt	a0, a4, ispossible
	li	a7, 4
	la	a0, impossible
	ecall	
	mul	a0, a0, zero
	ret
Bicbigger:
	add	a4, a0, a2
	bgt	a1, a4, ispossible
	li	a7, 4
	la	a0, impossible
	ecall	
	mul	a0, a0, zero
	ret
Cicbigger:
	add	a4, a0, a1
	bgt	a2, a4, ispossible
	li	a7, 4
	la	a0, impossible
	ecall	
	mul	a0, a0, zero
	ret
ispossible:
	li	a7, 4
	la	a0, possible
	ecall	
	mul	a0, a0, zero
	addi	a0, zero, 1
	j	fim
ifab:
	bgt	a0, a2, ifac
	addi	a3, zero, 3
	j	comeBack
ifac:	
	addi	a3, zero, 1
	j	comeBack	
ifbc:
	addi	a3, zero, 2
	j	comeBack
fim:	
	nop
