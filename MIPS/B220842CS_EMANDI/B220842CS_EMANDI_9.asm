.data 
	say: .asciiz "enter the index of fibonacci u want "
	num: .asciiz "nth number is "
.text
.globl main
main:
	li $v0,4
	la $a0,say
	syscall
	li $v0,5
	syscall
	move $t4,$v0
	li $t0,0
	li $t1,1
	beq $t4,1,first
	beq $t4,2,sec
	li $t3,2
	loop:
		add $t2,$t1,$t0
		addi $t3,$t3,1
		beq $t3,$t4,exitloop
		move $t0,$t1
		move $t1,$t2
		j loop
	first:
		li $v0,4
		la $a0,num
		syscall
		li $v0,1
		move $a0,$t0
		syscall
		j exit
	sec:
		li $v0,4
		la $a0,num
		syscall
		li $v0,1
		move $a0,$t1
		syscall
		j exit
	exitloop:
		li $v0,4
		la $a0,num
		syscall
		li $v0,1
		move $a0,$t2
		syscall
	exit:
		li $v0,10
		syscall