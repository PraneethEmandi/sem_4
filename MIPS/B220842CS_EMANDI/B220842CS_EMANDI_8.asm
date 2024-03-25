.data 
	arr: .space 160
	acc_size: .asciiz "enter the size of array "
	acc_num: .asciiz "enter the num "
	search_num: .asciiz "enter the num to be searched "
	result: .asciiz "index is "
	no: .asciiz "num is not present in the array"
	yes: .asciiz "num is present, index is " 
.text
.globl main
main:
	li $v0,4
	la $a0,acc_size
	syscall
	li $v0,5
	syscall
	#s0 has the size
	move $s0,$v0
	#index of array
	li $t0,0
	loop:
		beq $t0,$s0,exitloop
		sll $t1,$t0,2
		li $v0,4
		la $a0,acc_num
		syscall
		li $v0,5
		syscall
		sw $v0,arr($t1)
		addi $t0,$t0,1
		j loop
	exitloop:
	li $v0,4
	la $a0,search_num
	syscall
	li $v0,5
	syscall
	#t2 has num to be searched
	move $t2,$v0
	li $t0,0
	search:
		 beq $t0,$s0,fail
		 sll $t1,$t0,2
		 lw $t3,arr($t1)
		 beq $t3,$t2,success
		 addi $t0,$t0,1
		 j search
	fail:
		li $v0,4
		la $a0,no
		syscall
		j exit
	success:
		li $v0,4
		la $a0,yes
		syscall
		li $v0,1
		move $a0,$t0
		syscall
	exit:
		li $v0,10
		syscall