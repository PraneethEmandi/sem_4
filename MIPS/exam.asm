.data 
	msg: .asciiz "enter the num"
	
.text
.globl main
main:
	li $v0,4
	la $a0,msg
	syscall
	
	li $v0,5
	syscall
	move $t1,$v0
	srl $t2,$t1,6
	sll $t2,$t2,6
	li $v0,1
	move $a0,$t2	
	syscall
	
	li $v0,10
	syscall