.data
	str: .space 33
	msg1: .asciiz "Enter the binary number: "
	msg2: .asciiz "\nThe decimal equivalent is: "
.text
main:
	li $v0, 4
	la $a0, msg1
	syscall
	
	li $v0, 8
	la $a0,str
	li $a1,33
	syscall
	
	li $t1, 0 #value
	li $t2, 0 #counter
	
convert:
	lb $t3, str($t2)
	blt $t3, 48, done
	subi $t3, $t3, '0'
	sll $t1, $t1, 1
	or $t1, $t1, $t3
	add $t2, $t2, 1
	j convert
	
done:
	li $v0, 4
	la $a0, msg2
	syscall
	move $a0, $t1
	li $v0, 1
	syscall
	li $v0, 10
	syscall
