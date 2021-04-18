	.data
vectorA:	.word 1,2,3,4,5,6
indiceA:	.word 2
indiceB:	.word 5

	.text
	# As descrições são em relação ao meu entendimento, podem estar equivocadas
main:
	la s0, vectorA # Passa o endereço do vectorA para s0
	la t0, indiceA # Passa o endereço do indiceA para t0
	la t1, indiceB # Passa o endereço do indiceB para t1
	lw a0, 0(t0) # Passa o valor contido em t0 para a0
	lw a1, 0(t1) # Passa o valor contido em t1 para a1

	jal swap
	
	j fim

swap:
	li  t2, 4 # Passa o valor inteiro para um registrador
	mul t4, a0, t2 # Acha a distância em bytes da posição a ser encontrada
	add t4, t4, s0 # Soma a a distância com a posição de memória do início do vetor
	mul t5, a1, t2 # Acha a distância em bytes da posição a ser encontrada 
	add t5, t5, s0 # Soma a a distância com a posição de memória do início do vetor
	lw t2, 0(t4) # Carrega o valor da posição encontrada em t2 
	lw t3, 0(t5) # Carrega o valor da posição encontrada em t3 
	sw t3, 0(t4) # Guarda a palavra de t4 em t3
	sw t2, 0(t5) # Guarda a palavra de t5 em t2
	# nessa etapa acima é que ele faz a inversão dos valores usando os endereços de memória
	ret		
fim:	
	nop
