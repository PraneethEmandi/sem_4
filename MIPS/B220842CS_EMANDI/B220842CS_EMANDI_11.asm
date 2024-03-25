.data
	msg1: .asciiz "Enter an alphabet either upper case or lower case: "
	msg2: .asciiz "\nThe resultant character is: "
	
.text
main:
	la $a0, msg1
	li $v0, 4
	syscall
	
	li $v0, 12
	syscall
	move $t1, $v0
	
	blt $t1, 91, change_to_lower
	blt $t1, 123, change_to_upper
	
change_to_lower:
	addi $t1, $t1, 32
	j print
	
change_to_upper:
	sub $t1, $t1, 32
	j print

print:
	la $a0, msg2
	li $v0, 4
	syscall
	move $a0, $t1
	li $v0, 11
	syscall
	
	li $v0, 10
	syscall
