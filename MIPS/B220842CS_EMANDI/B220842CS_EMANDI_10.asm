.data
	msg1: .asciiz "Enter the value of A: "
	msg2: .asciiz "The resultant by adding A with its complement is: "

.text
	li $v0, 4
	la $a0, msg1
	syscall
	
	li $v0, 5
	syscall
	move $s0, $v0
	
	nor $s1, $s0, $s0
	addi $s1, $s1, 1
	
	li $v0, 4
	la $a0, msg2
	syscall
	
	add $a0, $s1, $s0
	li $v0, 1
	syscall