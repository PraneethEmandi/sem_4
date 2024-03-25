.data
	accept: .asciiz "enter a number: "
	evetell: .asciiz "Num is even"
	oddtell: .asciiz "Num is odd"
.text
.globl main

main:
	#print prompt
	li $v0,4
	la $a0,accept
	syscall
	
	#Read num
	li $v0,5
	syscall
	move $t0,$v0
	#check for odd and even
	andi $t1,$t0,1
	beq $t1,$zero,even
	#else
	li $v0,4
	la $a0,oddtell
	syscall
	j exit
	
	even:
		#num is even
		li $v0,4
		la $a0,evetell
		syscall
	
	exit:
		li $v0,10
		syscall
		