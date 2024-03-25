.data 
	arr: .space 160
	accept: .asciiz "enter the max num: "
	count: .asciiz "num of prime nums are: "
	nextline: .asciiz "\nprime nums are\n"
#	prnt: .asciiz "prime nums are\n"
	chki: .asciiz "i\n"
	chkj: .asciiz "j\n"
	y: .asciiz "yes\n"
.text
.globl main

main:
	li $v0,4
	la $a0,accept
	syscall
	li $v0,5
	syscall
	#t0 has max num
	move $t0,$v0
	
	#t2 is i
	li $t2,2
	#t1 is index
	li $t1,0
	#count of prime num
	li $t5,0
	loop_i:
		#t3 is j
		li $t3,2
		#li $v0,4
		#la $a0,chki
		#syscall
		loop_j:
			beq $t3,$t2,prime
			#li $v0,4
			#la $a0,chkj
			#syscall
			div $t2,$t3
			mfhi $t4
			#lw $a0,0($t4)
			#li $v0,1
			#syscall
			beq $t4,$zero,exit_loop_j
			addi $t3,$t3,1
			j loop_j
		prime:
		#li $v0,4
		#la $a0,y
		#syscall
		sw $t2,arr($t1)
		#sll $t1,$t1,2
		addi $t1,$t1,4
		addi $t5,$t5,1
		exit_loop_j:
		beq $t2,$t0,exit_i
		addi $t2,$t2,1
		j loop_i
	exit_i:
		li $v0,4
		la $a0,count
		syscall
		move $a0,$t5
		li $v0,1
		syscall
		li $v0,4
		la $a0,nextline
		syscall
		li $t6,0
		print:
			beq $t6,$t1,exit
			lw $t7,arr($t6)
			li $v0,1
			move $a0,$t7
			syscall
			li $v0,11
			li $a0,32
			syscall
			addi $t6,$t6,4
			j print
		exit:
		li $v0,10
		syscall
		