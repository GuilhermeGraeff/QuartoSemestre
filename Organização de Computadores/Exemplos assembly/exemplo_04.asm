	.data
vetorA:    .space    40

		.text
main: 
    	la 	s0, vetorA
	li 	t0, 0     # add t0, zero, zero
	li    	t1, 10    # addi t1, zero, 10
loop:
    	beq    t0,t1, end
	lw 	s1, 0(s0)
	addi 	s1, s1,1
	sw  	s1, 0(s0)
	addi 	s0, s0, 4
	addi 	t0, t0,1
	j 	loop
end:
    	nop
