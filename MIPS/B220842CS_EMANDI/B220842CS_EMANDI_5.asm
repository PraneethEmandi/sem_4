.data
	accept: .asciiz "enter a number: "
	yes: .asciiz "Yes it is perfect num\n"
	no: .asciiz "no it is not perfect num\n"

	.text
	.globl main
main:
	#ACCEPT
	li $v0,4
	la $a0,accept
	syscall
	li $v0,5
	syscall
	move $t0,$v0
	li $t1,1
	li $t3,0
	loop:
		beq $t1,$t0,exitloop
		
		div $t0,$t1
		mfhi $t2
		beq $t2,$zero,addn
			
		addi $t1,$t1,1
		j loop
	addn:
		add $t3,$t3,$t1
		addi $t1, $t1, 1
    		j loop
	exitloop:
		beq $t0,$t3,yesblock
		li $v0,4
		la $a0,no
		syscall
		j exit
	yesblock:
		li $v0,4
		la $a0,yes
		syscall
	exit:
		li $v0,10
		syscall