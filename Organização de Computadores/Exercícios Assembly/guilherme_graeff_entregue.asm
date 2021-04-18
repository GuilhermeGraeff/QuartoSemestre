#Implementar um programa usando o assembry do RISC-V que determina o maior entre 3 
#valores presentes na memória. Ao final o maior valor deve estar armazenado no registrador a0.

#P.S. o arquivo entregue deve ser nomeado com o seu nome no formato <nome_sobrenome>.asm
# A soma dos dois menores tem que ser maior que o maior
	.data
ladoA:		.word 6
ladoB:		.word 12
ladoC:		.word 24


	.text
main:
	lw	t0, ladoA
	lw	t1, ladoB
	lw	t2, ladoC
	bgt 	t0, t1, ifab
	bgt	t1, t2, ifbc
	addi	a0, t2, 0
	
	j	fim
ifab:
	bgt	t0,t2, ifac
	addi	a0, t2, 0
	j	fim
ifac:	
	addi	a0, t0, 0
	j	fim	
ifbc:
	addi	a0, t1, 0
	j	fim
fim:	
	nop