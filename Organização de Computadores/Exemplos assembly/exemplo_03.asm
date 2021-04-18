	.data
vetorA:    .word    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5
vetorB:    .word    11, 12, 13, 14, 15, 16, 17, 18, 19, 20
vetorC:    .space    40

	.text
main: 
    	la 	s0, vetorA
    	la 	s1, vetorB
    	la 	s2, vetorC
    	lw 	t0, 12(s0)
    	lw 	t1, 28(s1)
    	blt 	t0, t1, if
else:
	sw  	t1, 20 (s2)
	j 	fim
if:
	sw  	t0, 20 (s2)
fim:  	nop
