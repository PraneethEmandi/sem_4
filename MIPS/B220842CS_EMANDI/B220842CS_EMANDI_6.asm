.data
	accept: .asciiz "enter the num: "
	yes: .asciiz "yes"
	no: .asciiz "no"
.text
.globl main
main:
	#accept
	li $v0,4
	la $a0,accept
	syscall
	li $v0,5
	syscall
	move $t0,$v0
	move $t1,$t0
	li $t4,0
	li $t5,10
	loop:
		beqz $t0,exitloop
		div $t0,$t5
		mflo $t0
		mfhi $t2
		li $t3,1
		mul $t3,$t2,$t2
		mul $t3,$t3,$t2
		add $t4,$t4,$t3
		j loop
	exitloop:
		beq $t1,$t4,yesblock
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