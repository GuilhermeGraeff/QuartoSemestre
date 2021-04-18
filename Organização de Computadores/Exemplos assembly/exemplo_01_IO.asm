	.data
msg_comum:	.asciz "Entre com o valor de "
msg_A:		.asciz "A: "
msg_B:		.asciz "B: "
msg_C:		.asciz "C: "	
msg_resultado:	.asciz  "\n    S = "

	.text
main: 
	la 	a0, msg_comum  # imprime mensagem
	li 	a7,4
	ecall

	la 	a0, msg_A  # imprime mensagem
	li 	a7,4
	ecall	
 
	addi 	a7, zero, 5  #lê inteiro
	ecall	
	add 	s0, zero, a0  # carrega valor lido em s0
###
	la 	a0, msg_comum  # imprime mensagem
	li 	a7, 4
	ecall

	la 	a0, msg_B  # imprime mensagem
	li 	a7, 4
	ecall	
 
	addi 	a7, zero, 5  #lê inteiro
	ecall	
	add 	s1, zero, a0  # carrega valor lido em s1
###
	la 	a0, msg_comum  # imprime mensagem
	li 	a7, 4
	ecall

	la 	a0, msg_C  # imprime mensagem
	li 	a7, 4
	ecall	
 
	addi 	a7, zero, 5  #lê inteiro
	ecall	
	add 	s2, zero, a0  # carrega valor lido em s2

# equação
    	sub 	t0, s0, s1
    	addi 	t1, s2, -5
    	add 	s3, t0, t1

#resultado
	la 	a0, msg_resultado  # imprime mensagem
	li 	a7, 4
	ecall
	
	add 	a0, zero, s3  # imprime inteiro
	li 	a7, 1
	ecall
	
	