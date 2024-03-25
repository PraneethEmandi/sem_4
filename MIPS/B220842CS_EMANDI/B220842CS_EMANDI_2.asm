.data
	accept: .asciiz "enter the num u want factorial for: "
	print: .asciiz "factorial is "

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
	li $t1,2
	li $t2,1
	loop:
		mul $t2,$t2,$t1
		beq $t0,$t1,loopexit
		addi $t1,$t1,1
		j loop
	loopexit:
		li $v0,4
		la $a0,print
		syscall
		li $v0,1
		move $a0,$t2
		syscall
		li $v0,10
		syscall
		
		