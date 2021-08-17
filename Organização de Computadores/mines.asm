#####	Aluno: Alisson Luan de Lima Peloso	#####

        .data
campo:		.space		324   # esta versão suporta campo de até 9 x 9 posições de memória
salva_S0:	.word		0
salva_ra:	.word		0
salva_ra1:	.word		0

interface:	.space		324
printNColums:	.string	"    0 1 2 3 4 5 6 7\n"
printHL:	.string	"    _______________\n"
printVL:	.string "  |"
printVoidPos:	.string	"- "
printBomb:	.string "B "
printFlag:	.string	"F "
printLineBreak:	.string	"\n"
printSpace:	.string " "
printTitle:	.string	"\n***** Campo Minado *****\n\n"
printFindBomb:	.string "\nVocê pisou em uma Mina Terrestre! Fim de Jogo.\n"
printWin:	.string	"\nParabéns!!! Você sobreviveu.\n"
printMenu:	.string	"\nSelecione a opção desejada:\n1) Revelar posição no campo minado;\n2) Adicionar/Remover uma bandeira;\n"
printDesPos:	.string	"Qual a posição desejada? "
printErrorPos:	.string	"ERRO: Selecione uma posição válida!\n"
printErrorVal:	.string	"ERRO: Selecione um valor válido!\n"
printHaveFlag:	.string	"OPS, não é possível pisar aqui! Tem uma bandeirinha sua\n"
printErrorFlagP:.string	"Você ultrapassou o limite de Bandeiras!\n"
printFlags:	.string	"Bandeiras: "
printFlagsLimit:.string	"/15\n"

espaco:			.asciz		" "
nova_linha:		.asciz		"\n"
posicao:		.asciz		"\nPosicao: "

	.text
main:
	la	s0, campo			# s0 aponta para a matriz campo
	la	s1, interface			# s1 aponta para a matriz de interface
	li	s2, 8				# s2 recebe o n das matrizes
					
	mv	a0,s0				# a0 recebe endereço da matriz campo
	mv	a1,s2				# a1 recebe o tamanho das matrizes
	jal 	INSERE_BOMBA			# chama a função INSERE_BOMBA
					
	mv	a0,s0				# a0 recebe endereço da matriz campo
	mv	a1,s2				# a1 recebe o tamanho das matrizes
	jal	calcula_bombas			# chama a função calcula_bombas
					
	addi	t0, zero, 1			# op = 1
	mv	s8, zero			# countFlags = 0
					
while:
	beq	t0, zero, end_while		# while do menu
					
	addi	a7, zero, 4		
	la	a0, printTitle			# printando o título
	ecall	
	
	mv	a0, s0				# a0 recebe endereço da matriz campo
	mv	a1, s1				# a1 recebe endereço da matriz interface
	mv	a2, s2				# a2 recebe tamanho da matriz
	jal	mostra_campo			# chama função mostra_campo. a3 = return situation
	
	addi	t1, zero, 1
	addi	t2, zero, 2
	
	beq	a3, t1, find_bomb		# se situation = 1, pula para find_bomb
	beq	a3, t2, survived		# se situation = 2, pula para survived
	
	addi	a7, zero, 4
	la	a0, printMenu			# se não, printa o menu
	ecall
	
	addi	a7, zero, 5			# scan de int
	ecall
	
	mv	t0, a0
	
	beq	t0, t1, case_one		# se scan = 1, pula para o caso 1
	beq	t0, t2, case_two		# se scan = 2, pula para o caso 2
	
	addi	a7, zero, 4
	la	a0, printErrorVal		# se não, printa erro de valor
	ecall
	
	j	while
	
############################### Case 1	############################### 
case_one:
	addi	a7, zero, 4
	la	a0, printDesPos			# print da posição desejada
	ecall
	
	addi	a7, zero, 5			# scan
	ecall
	mv	t3, a0				# i = scan
	ecall
	mv	t4, a0  			# j = scan
	
	addi	t6, zero, 7
	addi	t5, zero, 4
	
	mv	a6, s2				# t4 -> N	
	mul	a6, a6, t3			# t4 -> N * i
	add	a6, a6, t4			# t4 -> N * i + j
	mul	a6, a6, t5			# distancia para o endereço inicial da matriz
	add	a6, a6, s1
	
	lw	a5, 0(a6)			# conteúdo da interface[i][j]
	
	bgt	t3, t6, invalid_pos	
	bgt	t4, t6, invalid_pos
	
	addi	t6, zero, 10
	beq	a5, t6, have_flag
	
	addi	t6, zero, 1
	sw	t6, 0(a6)
	
	j	while

invalid_pos:
	addi	a7, zero, 4
	la	a0, printErrorPos
	ecall
	
	j 	while
	
have_flag:
	addi	a7, zero, 4
	la	a0, printHaveFlag
	ecall
	
	j 	while

############################### Case 2	############################### 
case_two:
	addi	a7, zero, 4
	la	a0, printDesPos
	ecall
	
	addi	a7, zero, 5
	ecall
	mv	t3, a0				# i = scan
	ecall
	mv	t4, a0  			# j = scan
	
	addi	t6, zero, 7
	addi	t5, zero, 4
	
	mv	a6, s2				# t4 -> N	
	mul	a6, a6, t3			# t4 -> N * i
	add	a6, a6, t4			# t4 -> N * i + j
	mul	a6, a6, t5			# distancia para o endereço inicial da matriz
	add	a6, a6, s1
	
	lw	a5, 0(a6)			# conteúdo da interface[i][j]
	
	bgt	t3, t6, invalid_pos
	bgt	t4, t6, invalid_pos
	
	addi	t6, zero, 15
	
	bge	s8, t6, flag_limit
	
	addi	t6, zero, 10
	
	bge	a5, t6, the_flag
	
	addi	t6, zero, 1
	
	beq	a5, t6, invalid_pos
	
	addi	t6, zero, 10
	sw	t6, 0(a6)
	addi	s8, s8, 1
	j	print_flags
	
flag_limit:
	addi	a7, zero, 4
	la	a0, printErrorFlagP
	ecall
	j	print_flags

the_flag:
	sw	zero, 0(a6)
	addi	s8, s8, -1
	j	print_flags

print_flags:
	addi	a7, zero, 4
	la	a0, printFlags
	ecall
	addi	a7, zero, 1
	mv	a0, s8
	ecall
	addi	a7, zero, 4
	la	a0, printFlagsLimit
	ecall
	
	j	while
	
###################################################################################

find_bomb:
	mv	t0, zero
	addi	t1, zero, 64
	mv	t3, s1
	addi	t5, zero, 10
the_last_loop:
	beq	t0, t1, end_last_loop
	lw	t4, 0(t3)
	beq	t4, t5, theres_a_flag
	
	addi 	t4, zero, 1
	sw	t4, 0(t3)
	addi	t3, t3, 4
	addi	t0, t0, 1
	j	the_last_loop
	
theres_a_flag:
	addi	t3, t3, 4
	addi	t0, t0, 1
	j	the_last_loop
	
end_last_loop:
	mv	a0, s0
	mv	a1, s1
	mv	a2, s2
	jal	mostra_campo
	
	addi	a7, zero, 4
	la	a0, printFindBomb
	ecall
	j	end
	
survived:
	addi	a7, zero, 4
	la	a0, printWin
	ecall
	j	end
	
end_while:
	
	j	end
	
###################### Função que calcula as bombas ao redor ######################
calcula_bombas:					# a0 recebe endereço da matriz campo e a1 é o n (tamanho da linha/coluna)
	mv	t0, zero			# i -> linhas
	mv	t1, zero			# j -> colunas
	
loop_i:
	beq	t0, a1, endloop_i
	mv	t1, zero

loop_j:
	beq	t1, a1, endloop_j
	mv	t3, zero			# count_bombs
	li	t5, 4				# sizeof(word)
	
	mv	t4, a1				# t4 -> N	
	mul	t4, t4, t0			# t4 -> N * i
	add	t4, t4, t1			# t4 -> N * i + j
	mul	t4, t4, t5			# distancia para o endereço inicial da matriz
	mv	a0, s0
	
	add	t4, t4, a0			# endereço da posição na matriz
	lw	t6, 0(t4)			# conteúdo da posição da matriz	
	
	beq	t6, zero, row_verification
	addi	t1, t1, 1
	j	loop_j
	
row_verification: 				#a3 = starti - #a4 = endi - #a5 = startj - #a6 = endj
	addi	t2, a1, -1
	beq	t0, zero, i_in_init
	beq	t0, t2, i_in_end
	
	addi	a3, t0, -1 			#else: starti = i-1; endi = i+1;
	addi	a4, t0, 1
	j column_verification
	
i_in_end: 					# if (i == size-1) endi = size-1; starti = i-1;
	addi	a3, t0, -1
	addi	a4, a1, -1
	j column_verification
	
i_in_init: 					# if (i == 0) starti = 0; endi = i+1
	mv	a3, zero
	addi	a4, t0, 1
	j column_verification

column_verification:
	addi	t2, a1, -1
	beq	t1, zero, j_in_init
	beq	t1, t2, j_in_end

	addi	a5, t1, -1			#else: startj = j-1; endj = j+1;
	addi	a6, t1, 1
	j	padding
	
j_in_end: 					# if (j == size-1) endj = size-1; startj = j-1;
	addi	a5, t1, -1
	addi	a6, a1, -1
	j 	padding
	
j_in_init: 					# if (j == 0) startj = 0; endj = j+1
	mv	a5, zero
	addi	a6, zero, 1
	j 	padding
	
padding:
	mv	t2, a3 				# k-> starti
	
loop_k:
	mv	t5, a5				# l-> startj
	bgt	t2, a4, endloop_k
loop_l:
	bgt	t5,a6, endloop_l
	addi	t6,zero,9
	
	li	s11, 4				# sizeof(word)
	
	mv	s10, a1				# s10-> N	
	mul	s10, s10, t2			# s10 -> N * k
	add	s10, s10, t5			# s10 -> N * k + l
	mul	s10, s10, s11			# distancia para o endereço inicial da matriz
	
	add	s10, s10, a0			# endereço da posição na matriz
	lw	s9, 0(s10)			# conteúdo da posição da matriz
	
	bne	s9,t6, not_bomb
	addi	t3, t3, 1
not_bomb:
	addi	t5, t5, 1
	j	loop_l
	
endloop_l:
	addi	t2, t2, 1
	j	loop_k
	
endloop_k:
	sw	t3, 0(t4)
	addi	t1, t1, 1
	j	loop_j

endloop_j:
	addi	t0, t0, 1
	j	loop_i

endloop_i:
	ret

###################### Função que insere as bombas no Campo ######################
INSERE_BOMBA:
		la	t0, salva_S0
		sw  	s0, 0 (t0)		# salva conteudo de s0 na memoria
		la	t0, salva_ra
		sw  	ra, 0 (t0)		# salva conteudo de ra na memoria
		
		add 	t0, zero, a0		# salva a0 em t0 - endereço da matriz campo
		add 	t1, zero, a1		# salva a1 em t1 - quantidade de linhas 

QTD_BOMBAS:
		addi 	t2, zero, 15 		# seta para 15 bombas	
		add 	t3, zero, zero 		# inicia contador de bombas com 0
		addi 	a7, zero, 30 		# ecall 30 pega o tempo do sistema em milisegundos (usado como semente
		ecall 				
		add 	a1, zero, a0		# coloca a semente em a1
INICIO_LACO:
		beq 	t2, t3, FIM_LACO
		add 	a0, zero, t1 		# carrega limite para %	(resto da divisão)
		jal 	PSEUDO_RAND
		add 	t4, zero, a0		# pega linha sorteada e coloca em t4
		add 	a0, zero, t1 		# carrega limite para % (resto da divisão)
   		jal 	PSEUDO_RAND
		add 	t5, zero, a0		# pega coluna sorteada e coloca em t5

LE_POSICAO:	
		mul  	t4, t4, t1
		add  	t4, t4, t5  		# calcula (L * tam) + C
		add  	t4, t4, t4  		# multiplica por 2
		add  	t4, t4, t4  		# multiplica por 4
		add  	t4, t4, t0  		# calcula Base + deslocamento
		lw   	t5, 0(t4)   		# Le posicao de memoria LxC
VERIFICA_BOMBA:		
		addi 	t6, zero, 9		# se posição sorteada já possui bomba
		beq  	t5, t6, PULA_ATRIB	# pula atribuição 
		sw   	t6, 0(t4)		# senão coloca 9 (bomba) na posição
		addi 	t3, t3, 1		# incrementa quantidade de bombas sorteadas
PULA_ATRIB:
		j	INICIO_LACO

FIM_LACO:					# recupera registradores salvos
		la	t0, salva_S0
		lw  	s0, 0(t0)		# recupera conteudo de s0 da memória
		la	t0, salva_ra
		lw  	ra, 0(t0)		# recupera conteudo de ra da memória		
		jr 	ra			# retorna para funcao que fez a chamada


###################### Função que retorna número "aleatório" ######################
PSEUDO_RAND:
		addi t6, zero, 125  		# carrega constante t6 = 125
		lui  t5, 682			# carrega constante t5 = 2796203
		addi t5, t5, 1697 		# 
		addi t5, t5, 1034 		# 	
		mul  a1, a1, t6			# a = a * 125
		rem  a1, a1, t5			# a = a % 2796203
		rem  a0, a1, a0			# a % lim
		bge  a0, zero, EH_POSITIVO  	# testa se valor eh positivo
		addi t4, zero, -1           	# caso não 
		mul  a0, a0, t4		    	# transforma em positivo
EH_POSITIVO:	
		ret				# retorna em a0 o valor obtido


###################### Função mostra o campo ######################
mostra_campo:					# a0 recebe endereço da matriz campo, a1 recebe endereço da matriz interface e a2 é o n (tamanho da linha/coluna)
	mv	t0, zero  			# Situation
	mv	t1, zero  			# count
	mv	t3, a0
	
	addi	a7,zero,4
	la	a0, printNColums
	ecall
	la	a0, printHL
	ecall
	
	mv	t4,zero				# i = 0
m_loopi:
	beq	t4, a2, m_endloopi
	
	addi	a7, zero,1
	mv	a0, t4
	ecall
	addi	a7, zero, 4
	la	a0, printVL
	ecall
	
	mv	t5,zero				# j= 0
m_loopj:
	beq	t5, a2, m_endloopj
	addi	t6, zero, 4
	
	mv	a6, a2				# t4 -> N
	mul	a6, a6, t4			# t4 -> N * i
	add	a6, a6, t5			# t4 -> N * i + j				
	mul	a6, a6, t6			# distancia para o endereço inicial da matriz
	
	add	a6, a6, a1			# endereço da posição i j na matriz interface
	lw	a5, 0(a6)			# conteúdo da posição i j na matriz interface
	
	addi	t2, zero, 1
	
	beq	a5, zero, equalzero
	beq	a5, t2, equalone
	
	addi	a7, zero, 4
	la	a0, printFlag
	ecall
	j	out_ifs
	
equalzero:
	addi	a7, zero, 4
	la	a0, printVoidPos
	ecall
	j	out_ifs

equalone:
	addi	t1, t1, 1
	
	addi	t6, zero, 4
	
	mv	a6, a2				# t4 -> N
	mul	a6, a6, t4			# t4 -> N * i
	add	a6, a6, t5			# t4 -> N * i + j				
	mul	a6, a6, t6			# distancia para o endereço inicial da matriz
	
	add	a6, a6, t3			# endereço da posição i j na matriz campo
	lw	a5, 0(a6)			# conteúdo da posição i j na matriz campo
	
	addi	t2, zero, 9
	
	beq	a5, t2, theBomb
	
	addi	a7, zero, 1
	mv	a0, a5
	ecall
	
	addi	a7, zero, 4
	la	a0, printSpace
	ecall
	j	out_ifs
	
theBomb:
	addi	a7, zero, 4
	la	a0, printBomb
	ecall
	
	addi	t0, zero, 1
	j	out_ifs

out_ifs:
	addi	t5, t5, 1
	j	m_loopj
	
m_endloopj:
	addi	t4,t4,1
	
	addi	a7, zero, 4
	la	a0, printLineBreak
	ecall
	
	j	m_loopi
	
m_endloopi:
	addi	t2, zero, 49			# Liberou todos os campos menos a bomba
	
	beq	t0, zero, situationZero
	
	j	return_mostra_campo
	
situationZero:
	beq	t1, t2, win
	
	j	return_mostra_campo
	
win:
	addi	t0, zero, 2

return_mostra_campo:
	mv	a3, t0
	ret
	

end:
	nop
