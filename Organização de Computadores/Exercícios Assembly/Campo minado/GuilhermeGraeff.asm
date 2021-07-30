###############################################################
#A função insere_bombas necessita os seguintes rótulos
# e espaços de memória reservados
		.data
campo:			.space		256
salva_S0:		.word		0
salva_ra:		.word		0
salva_ra1:		.word		0
strShowInterface: .string	"Interface:\n    0  1  2  3  4  5  6  7\n    _  _  _  _  _  _  _  _"
strPulaLinha:	.string	"\n"
strEspaco:	.string	" "
strGanhou:	.string	"\nParabéns, você ganhou"
strCasaComFlag:	.string	"F "
strEspacoComBarra:	.string	"  |"
strLostTheGame:	.string	"\nÉ amigão, você perdeu o jogo.\n"
strImprimeCampo:	.string	"Imprimindo Campo, mostrando a localização das bombas"
strCasaFechada:	.string	"- "
strCasaAberta:	.string	"/ "
strFlagWarning:	.string	"\nEsta casa contêm uma Flag, retire a flag para poder revelar-la\n"
strCondicionalFlagRevela:	.string	"Digite 0 para revelar o conteúdo da casa, digite 1 para colocar/retirar uma flag...:"
strPosX:	.string	"Digite a LINHA da casa que gostaria de realizar a ação(de 0 a 7)...:"
strPosY:	.string	"Digite a COLUNA da casa que gostaria de realizar a ação(de 0 a 7)...:"

#########################################################
# necessário em caso de debug da funcao
#espaco:			.asciz		" "
#nova_linha:		.asciz		"\n"
#posicao:		.asciz		"\nPosicao: "
#########################################################

	.text

########################################################
# função main somente para teste. Não deve ser copiada 
#  para o código do trabalho
main:
	la 	a0, campo
	addi	a1, zero, 8
	jal 	INSERE_BOMBA
MAINRUN:
	li	a0,0
	la 	a0, campo
	li	a1,0
	addi	a1, zero, 8
	jal	IMPRIME_VETOR
	
	
	#Este é o laço principal, ele se repete até que o jogo acabe.
	la 	a0, campo
	li	a1,0
	addi	a1, zero, 8
	jal	DISPLAYINTERFACE
	
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	
	li	a7, 4
	la	a0, strCondicionalFlagRevela
	ecall
	
	
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	
	#Seleciona se é para revelar casa ou colocar bandeira
	li	a7, 5 
	ecall	
	mv	t6, a0
	
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	
	li	a7, 4
	la	a0, strPosX
	ecall
	
	#lê a linha a fazer a operação
	li	a7, 5 
	ecall	
	mv	t3, a0
	
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	
	li	a7, 4
	la	a0, strPosY
	ecall
	
	#lê a coluna a fazer a operação
	li	a7, 5 
	ecall	
	mv	t4, a0
	
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	
	# Seleciona a opção de colocar flac ou revelar casa
	beq t6,zero, REVELACASA
	# Colocando flag
	li	a0,0
	la 	a0, campo
	li	a1,0
	addi	a1, zero, 8
	li	a2,0
	addi	a2, t3, 0
	li	a3,0
	addi	a3, t4, 0
	# Chamar a função que coloca a flag
	jal	COLOCA_FLAG
	
REVELACASA:
	
	li	a0,0
	addi	a0, t3, 0
	li	a1,0
	addi	a1, t4, 0
	# Calcula
	jal	CALCULACANTOBORDAMEIO	#retorna em a0 1 para canto superior esquerdo, 2 para canto superior direito
						#              3 para canto inferior esquerdo, 4 para inferior direito
						#retorna em a0 5 para a borda de cima, 6 para a borda de baixo
						#		 7 para a borda da esquerda, 8 para a borda da direita
						#retorna em a0 9 para as casas que ficam no meio
	mv	t5,a0
	li	a0,0
	la 	a0, campo	#endereço campo
	li	a1,0
	addi	a1, zero, 8	#tamanho do campo
	li	a2,0
	addi	a5,t5,0	#Característica da posição
	li	a3,0
	addi	a3,t3,0	#posição X
	li	a4,0
	addi	a4,t4,0	#posição Y
	jal	ATUALIZA_VETOR
	
	j	MAINRUN
fim:   
	ret



############################################################
# A função insere_bombas está implementada abaixo.
# Todo o código a seguir, mais os rotulos acima deve 
# ser colocado junto ao código do trabalho de campo minado
# entrada: a0 endereço de memoria do inicio da matriz campo
#          a1 quantidade de linhas da matriz campo
# saida: nao retorna nada
############################################################
#     Algoritmo	
#
#  Salva registradores
#  Carrega numero de sementes sorteadas = 15
#  Le semente para função de numero pseudo randomico
#  while (bombas < x) 
#     sorteia linha
#     sorteia coluna
#     le posição pos = (L * tam + C) * 4
#     if(pos != 9)
#    	  grava posicao pos = 9
#     bombas++  
#
############################################################

	#Soma 10 na posição calculada ou subtrai 10 se já for uma flag
COLOCA_FLAG:
	li	t5,0   
	addi	t5,a1,0   
	li	t4,0
INICIO_LACO_COLOCAFLAG:
	li	t3,0	 
	li	t6,0	 
	addi	t6,a1,0  
INICIO_LACO_INTERNO_COLOCAFLAG:
	bne a3,t3 ,CONTINUA_FLAG	
	bne a2,t4 ,CONTINUA_FLAG
	li t0,9
	lw t1, 0(a0)
	bgt t1,t0,SUBTRAIDEZ
	addi t1,t1,10
	sw	t1, 0(a0)
	j	CONTINUA_FLAG
SUBTRAIDEZ:
	addi	t1,t1,-10
	sw	t1, 0(a0)
CONTINUA_FLAG:
	addi	a0, a0, 4
	
	addi t3,t3,1
	blt	t3, t6, INICIO_LACO_INTERNO_COLOCAFLAG
	
	addi t4,t4,1
	blt	t4, t5, INICIO_LACO_COLOCAFLAG
	
	j	fim
	#Coloca na  posição selecionada a soma das bombas aos arredores se não tiver flag ou se não for uma bomba.
ATUALIZA_VETOR:
	li	a2,0
	addi	a2,a0,0
	li	t5,0    
	addi	t5,a1,0  
	li	t4,0
INICIO_LACO_ATUALIZA:
	li	t3,0	
	li	t6,0	 
	addi	t6,a1,0  
INICIO_LACO_INTERNO_ATUALIZA:
	bne a4,t3 ,CONTINUE	
	bne a3,t4 ,CONTINUE	
	li t0,19
	li t1, 10
	lw s10, 0(a2)
	blt s10,t1,NOFLAG
	li	a7, 4
	la	a0, strFlagWarning
	ecall
	j 	CONTINUE
NOFLAG:
	addi t1,t1,-1
	blt	s10,t1,NOLOST
	li	a7, 4
	la	a0, strLostTheGame
	ecall
	j	fimfim
NOLOST:
	li t2, 1
	bne a5,t2,NEXTTO2
	#caso 1
	li s11, 0
	lw s1, 4(a2)
	lw s2, 32(a2)
	lw s3, 36(a2)
	beq t0,s1,case11
	bne t1,s1, CASE11_HASNOBOMB
case11:
	addi s11,s11,1
CASE11_HASNOBOMB:
	beq t0,s1,case12
	bne t1,s2, CASE12_HASNOBOMB
case12:
	addi s11,s11,1
CASE12_HASNOBOMB:
	beq t0,s3,case13
	bne t1,s3, CASE13_HASNOBOMB
case13:
	addi s11,s11,1
CASE13_HASNOBOMB:	
	beq s11,zero, EZERO1
	sw	s11, 0(a2)
	j	CONTINUE
EZERO1:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE
NEXTTO2:
	li t2, 2
	bne a5,t2,NEXTTO3
	#caso 2
	li s11, 0
	lw s1, -4(a2)
	lw s2, 28(a2)
	lw s3, 32(a2)
	beq t0,s1,case21
	bne t1,s1, CASE21_HASNOBOMB
case21:
	addi s11,s11,1
CASE21_HASNOBOMB:
	beq t0,s2,case22
	bne t1,s2, CASE22_HASNOBOMB
case22:
	addi s11,s11,1
CASE22_HASNOBOMB:
	beq t0,s3,case23
	bne t1,s3, CASE23_HASNOBOMB
case23:
	addi s11,s11,1
CASE23_HASNOBOMB:	
	beq s11,zero, EZERO2
	sw	s11, 0(a2)
	j	CONTINUE
EZERO2:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE	
NEXTTO3:
	li t2, 3
	bne a5,t2,NEXTTO4
	#caso 3	
	li s11, 0
	lw s1, -32(a2)
	lw s2, -28(a2)
	lw s3, 4(a2)
	beq t0,s1,case31
	bne t1,s1, CASE31_HASNOBOMB
case31:
	addi s11,s11,1
CASE31_HASNOBOMB:
	beq t0,s2,case32
	bne t1,s2, CASE32_HASNOBOMB
case32:
	addi s11,s11,1
CASE32_HASNOBOMB:
	beq t0,s3,case33
	bne t1,s3, CASE33_HASNOBOMB
case33:
	addi s11,s11,1
CASE33_HASNOBOMB:	
	beq s11,zero, EZERO3
	sw	s11, 0(a2)
	j	CONTINUE
EZERO3:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE
NEXTTO4:
	li t2, 4
	bne a5,t2,NEXTTO5
	#caso 4
	li s11, 0
	lw s1, -36(a2)
	lw s2, -32(a2)
	lw s3, -4(a2)
	beq t0,s1,case41
	bne t1,s1, CASE41_HASNOBOMB
case41:
	addi s11,s11,1
CASE41_HASNOBOMB:
	beq t0,s2,case42
	bne t1,s2, CASE42_HASNOBOMB
case42:
	addi s11,s11,1
CASE42_HASNOBOMB:
	beq t0,s3,case43
	bne t1,s3, CASE43_HASNOBOMB
case43:
	addi s11,s11,1
CASE43_HASNOBOMB:	
	beq s11,zero, EZERO4
	sw	s11, 0(a2)
	j	CONTINUE
EZERO4:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE
NEXTTO5:
	li t2, 5
	bne a5,t2,NEXTTO6
	#caso 5
	li s11, 0
	lw s1, -4(a2)
	lw s2, 4(a2)
	lw s3, 28(a2)
	lw s4, 32(a2)
	lw s5, 36(a2)
	beq t0,s1,case51
	bne t1,s1, CASE51_HASNOBOMB
case51:
	addi s11,s11,1
CASE51_HASNOBOMB:
	beq t0,s2,case52
	bne t1,s2, CASE52_HASNOBOMB
case52:
	addi s11,s11,1
CASE52_HASNOBOMB:
	beq t0,s3,case53
	bne t1,s3, CASE53_HASNOBOMB
case53:
	addi s11,s11,1
CASE53_HASNOBOMB:
	beq t0,s4,case54
	bne t1,s4, CASE54_HASNOBOMB
case54:
	addi s11,s11,1
CASE54_HASNOBOMB:
	beq t0,s5,case55
	bne t1,s5, CASE55_HASNOBOMB
case55:
	addi s11,s11,1
CASE55_HASNOBOMB:	
	beq s11,zero, EZERO5
	sw	s11, 0(a2)
	j	CONTINUE
EZERO5:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE	
NEXTTO6:
	li t2, 6
	bne a5,t2,NEXTTO7
	#caso 6
	li s11, 0
	lw s1, -36(a2)
	lw s2, -32(a2)
	lw s3, -28(a2)
	lw s4, -4(a2)
	lw s5, 4(a2)
	beq t0,s1,case61
	bne t1,s1, CASE61_HASNOBOMB
case61:
	addi s11,s11,1
CASE61_HASNOBOMB:
	beq t0,s2,case62
	bne t1,s2, CASE62_HASNOBOMB
case62:
	addi s11,s11,1
CASE62_HASNOBOMB:
	beq t0,s3,case63
	bne t1,s3, CASE63_HASNOBOMB
case63:
	addi s11,s11,1
CASE63_HASNOBOMB:
	beq t0,s4,case64
	bne t1,s4, CASE64_HASNOBOMB
case64:
	addi s11,s11,1
CASE64_HASNOBOMB:
	beq t0,s5,case65
	bne t1,s5, CASE65_HASNOBOMB
case65:
	addi s11,s11,1
CASE65_HASNOBOMB:	
	beq s11,zero, EZERO6
	sw	s11, 0(a2)
	j	CONTINUE
EZERO6:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE	
NEXTTO7:
	li t2, 7
	bne a5,t2,NEXTTO8
	#caso 7
	li s11, 0
	lw s1, -32(a2)
	lw s2, -28(a2)
	lw s3, 4(a2)
	lw s4, 32(a2)
	lw s5, 36(a2)
	beq t0,s1,case71
	bne t1,s1, CASE71_HASNOBOMB
case71:
	addi s11,s11,1
CASE71_HASNOBOMB:
	beq t0,s2,case72
	bne t1,s2, CASE72_HASNOBOMB
case72:
	addi s11,s11,1
CASE72_HASNOBOMB:
	beq t0,s3,case73
	bne t1,s3, CASE73_HASNOBOMB
case73:
	addi s11,s11,1
CASE73_HASNOBOMB:
	beq t0,s4,case74
	bne t1,s4, CASE74_HASNOBOMB
case74:
	addi s11,s11,1
CASE74_HASNOBOMB:
	beq t0,s5,case75
	bne t1,s5, CASE75_HASNOBOMB
case75:
	addi s11,s11,1
CASE75_HASNOBOMB:	
	beq s11,zero, EZERO7
	sw	s11, 0(a2)
	j	CONTINUE
EZERO7:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE
NEXTTO8:
	li t2, 8
	bne a5,t2,NEXTTO9
	#caso 8
	li s11, 0
	lw s1, -36(a2)
	lw s2, -32(a2)
	lw s3, -4(a2)
	lw s4, 28(a2)
	lw s5, 32(a2)
	beq t0,s1,case81
	bne t1,s1, CASE81_HASNOBOMB
case81:
	addi s11,s11,1
CASE81_HASNOBOMB:
	beq t0,s2,case82
	bne t1,s2, CASE82_HASNOBOMB
case82:
	addi s11,s11,1
CASE82_HASNOBOMB:
	beq t0,s3,case83
	bne t1,s3, CASE83_HASNOBOMB
case83:
	addi s11,s11,1
CASE83_HASNOBOMB:
	beq t0,s4,case84
	bne t1,s4, CASE84_HASNOBOMB
case84:
	addi s11,s11,1
CASE84_HASNOBOMB:
	beq t0,s5,case85
	bne t1,s5, CASE85_HASNOBOMB
case85:
	addi s11,s11,1
CASE85_HASNOBOMB:	
	beq s11,zero, EZERO8
	sw	s11, 0(a2)
	j	CONTINUE
EZERO8:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE
NEXTTO9:
	#caso 9
	li s11, 0
	lw s1, -36(a2)
	lw s2, -32(a2)
	lw s3, -28(a2)
	lw s4, -4(a2)
	lw s5, 4(a2)
	lw s6, 28(a2)
	lw s7, 32(a2)
	lw s8, 36(a2)
	beq t0,s1,case91
	bne t1,s1, CASE91_HASNOBOMB
case91:
	addi s11,s11,1
CASE91_HASNOBOMB:
	beq t0,s2,case92
	bne t1,s2, CASE92_HASNOBOMB
case92:
	addi s11,s11,1
CASE92_HASNOBOMB:
	beq t0,s3,case93
	bne t1,s3, CASE93_HASNOBOMB
case93:
	addi s11,s11,1
CASE93_HASNOBOMB:
	beq t0,s4,case94
	bne t1,s4, CASE94_HASNOBOMB
case94:
	addi s11,s11,1
CASE94_HASNOBOMB:
	beq t0,s5,case95
	bne t1,s5, CASE95_HASNOBOMB
case95:
	addi s11,s11,1
CASE95_HASNOBOMB:
	beq t0,s6,case96
	bne t1,s6, CASE96_HASNOBOMB
case96:
	addi s11,s11,1
CASE96_HASNOBOMB:	
	beq t0,s7,case97
	bne t1,s7, CASE97_HASNOBOMB
case97:
	addi s11,s11,1
CASE97_HASNOBOMB:	
	beq t0,s8,case98
	bne t1,s8, CASE98_HASNOBOMB
case98:
	addi s11,s11,1
CASE98_HASNOBOMB:
	beq s11,zero, EZERO9
	sw	s11, 0(a2)
	j	CONTINUE
EZERO9:
	li s11, -1
	sw  s11, 0(a2)
	j	CONTINUE
CONTINUE:
	addi	a2, a2, 4
	addi t3,t3,1
	blt	t3, t6, INICIO_LACO_INTERNO_ATUALIZA
	addi t4,t4,1
	blt	t4, t5, INICIO_LACO_ATUALIZA
	j	fim
	#Essa função devolve qual canto que é se for um canto, qual borda que é se for uma borda ou se é uma casa que fica no meio.
CALCULACANTOBORDAMEIO:
	li	t0, 1
	li	t1, 6
	blt	a0, t0,TANABORDADECIMA
	bgt	a0, t1,TANABORDADEBAIXO
	blt	a1, t0,TANABORDAESQUERDA
	bgt	a1, t1,TANABORDADIREITA
	li	a0, 9
	ret
TANABORDADECIMA:
	li	t0, 1
	li	t1, 6
	blt	a1, t0,TANOCANTOSUPERIORESQUERDO
	bgt	a1, t1,TANOCANTOSUPERIORDIREITO
	li 	a0, 5
	ret
TANABORDADEBAIXO:
	li	t0, 1
	li	t1, 6
	blt	a1, t0,TANOCANTOINFERIORESQUERDO
	bgt	a1, t1,TANOCANTOINFERIORDIREITO
	li 	a0, 6
	ret
TANABORDAESQUERDA:
	li	t0, 1
	li	t1, 6
	blt	a0, t0,TANOCANTOSUPERIORESQUERDO
	bgt	a0, t1,TANOCANTOINFERIORESQUERDO
	li 	a0, 7
	ret
	ret
TANABORDADIREITA:
	li	t0, 1
	li	t1, 6
	blt	a0, t0,TANOCANTOSUPERIORDIREITO
	bgt	a0, t1,TANOCANTOINFERIORDIREITO
	li 	a0, 8
	ret
TANOCANTOSUPERIORESQUERDO:
	li 	a0, 1
	ret
TANOCANTOSUPERIORDIREITO:
	li 	a0, 2
	ret
TANOCANTOINFERIORESQUERDO:
	li 	a0, 3
	ret
TANOCANTOINFERIORDIREITO:
	li 	a0, 4
	ret
	#Essa função pega a matriz e interpreta, se tem bomba ou 0 printa '-', 
	#					      se tem um número > 0 e < 9 printa o número,
	#					      se tem -1(nenhuma bomba ao redor) printa '/'
	#					      se o número for > 10 printa 'F' de flag
DISPLAYINTERFACE:
	li a6, 0
	li	a2,0
	addi	a2,a0,0
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	li	a7, 4
	la	a0, strShowInterface
	ecall
	li	t5,0      
	addi	t5,a1,0   
	li	t4,0
INICIO_LACO_DISPLAY:
	li	t3,0
	li	t6,0	 
	addi	t6,a1,0  
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	li a0,0
	li	a7, 1
	addi	a0, t4,0
	ecall
	li	a7, 4
	la	a0, strEspacoComBarra
	ecall
INICIO_LACO_INTERNO_DISPLAY:
	#para cada casa verifica squal é o valor que está ali
	lw s11, 0(a2)
	li s0,0
	li s1,1
	li s2,2
	li s3,3
	li s4,4
	li s5,5
	li s6,6
	li s7,7
	li s8,8
	li s9,9
	li s10,19
	li t0,-1
	li t1,1
	bne s11, s0, NAOEZERO
	li	a7, 4
	la	a0, strCasaFechada
	ecall
NAOEZERO:
	bne s11, s1, NAOEUM
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOEUM:
	bne s11, s2, NAOEDOIS
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOEDOIS:	
	bne s11, s3, NAOETRES
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOETRES:
	bne s11, s4, NAOEQUATRO
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOEQUATRO:
	bne s11, s5, NAOECINCO
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOECINCO:
	bne s11, s6, NAOESEIS
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOESEIS:
	bne s11, s7, NAOESETE
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOESETE:
	bne s11, s8, NAOEOITO
	li a0,0
	li	a7, 1
	addi	a0, s11,0
	ecall
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi	a6, a6,1
NAOEOITO:
	bne s11, s9, NAOENOVE
	li	a7, 4
	la	a0, strCasaFechada
	ecall
NAOENOVE:
	bne s11, s10, NAOEDEZENOVE
	li	a7, 4
	la	a0, strCasaComFlag
	ecall
NAOEDEZENOVE:
	bne t0, s11, NAOEMENOSUM
	li	a7, 4
	la	a0, strCasaAberta
	ecall
	addi	a6, a6,1
NAOEMENOSUM:
	bne t1, s11, CONTINUARINTERFACE
	li	a7, 4
	la	a0, strCasaComFlag
	ecall
CONTINUARINTERFACE:
	addi	a2, a2, 4	
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi t3,t3,1
	blt	t3, t6, INICIO_LACO_INTERNO_DISPLAY
	addi t4,t4,1
	blt	t4, t5, INICIO_LACO_DISPLAY
	li s0,56
	bne a6, s0, NAOGANHOU
	li	a7, 4
	la	a0, strGanhou
	ecall
	j	fimfim
NAOGANHOU:
	j	fim
	# Imprime a matriz com seus números normais, para questões de debug e para quando perde.
IMPRIME_VETOR:
	li	a2,0
	addi	a2,a0,0
	li	a7, 4
	la	a0, strPulaLinha
	ecall
	li	a7, 4			
	la	a0, strImprimeCampo	
	ecall
	li	t5,0      
	addi	t5,a1,0   
	li	t4,0
INICIO_LACO_IMPRIME:
	li	t3,0	
	li	t6,0	 
	addi	t6,a1,0  
	
	li	a7, 4
	la	a0, strPulaLinha
	ecall
INICIO_LACO_INTERNO_IMPRIME:
	li	a7, 1
	lw	a0, 0(a2)
	ecall
	addi	a2, a2, 4
	li	a7, 4
	la	a0, strEspaco
	ecall
	addi t3,t3,1
	blt	t3, t6, INICIO_LACO_INTERNO_IMPRIME
	addi t4,t4,1
	blt	t4, t5, INICIO_LACO_IMPRIME
	j	fim
	
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

fimfim:
	#valor final
	li	a0,0
	la 	a0, campo
	li	a1,0
	addi	a1, zero, 8
	jal	IMPRIME_VETOR
	nop
