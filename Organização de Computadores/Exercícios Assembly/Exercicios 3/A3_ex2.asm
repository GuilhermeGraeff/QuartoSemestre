#for (int i = 10000; i >= 1; i--){
#    for(int j = 1; j < i; j ++){
#        if (bubble_vetor10k[j-1]>bubble_vetor10k[j]){
#            int a = bubble_vetor10k[j];
#            bubble_vetor10k[j] = bubble_vetor10k [j-1];
#            bubble_vetor10k[j-1] = a;
#        }
#    }
#}
#i = s1
	.data
vector:	.word 100,8,4,-3,2,1

tamanho:	.word 6
space:	.string		" "
	.text
main:	
	la s0, vector
	la s1, tamanho
	lw s1, 0(s1)
	addi s1, s1, -1
	jal	f_imprime
	li s8, 1
	li s9, 0
	li t6, 4
	jal	f_ordena	
	j 	fim

f_ordena:
	ble s1, s8, return
	
#---------------loop inteno
loop_interno:
	

	mul s10, s10, zero
	mul s11, s11, zero
	mul a1, a1, zero
	mul a0, a0, zero
	mul a1, a1, zero
	addi a0, s1, 0
	addi a1, s9, 0
	mul a6, a0, t6 
	add a6, a6, s0	 
	mul a7, a1, t6
	add a7, a7, s0
	lw s10, 0(a6)
	lw s11, 0(a7)
#---------------#---------------if interno
	bgt s11, s10, f_swap
else:
	j 	fimif
f_swap:		
	lw t2, 0(a6) 
	lw t3, 0(a7) 
	sw t3, 0(a6) 
	sw t2, 0(a7)
fimif:
#---------------#---------------
	addi s9, s9 , 1
	blt s9, s1, loop_interno
#---------------
	mul s9, s9, zero
	
	addi s1, s1, -1
	j	f_ordena

f_imprime:
	addi t4, s1, 0
	add a2, s0, zero
loop_interno_imp:
	blt t4, zero, return
	
	
	lw a0, (a2)
	li a7, 1
	ecall
	
	la a0, space
	li a7, 4
	ecall
	
	addi a2, a2, 4
	addi t4, t4, -1
	
	j	loop_interno_imp
	
return:
	mul a0, a0, zero
	ret		
fim:	
	nop
