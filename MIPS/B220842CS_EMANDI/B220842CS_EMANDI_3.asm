.data 
	accept: .asciiz "enter the num to be checked: "
	yes: .asciiz "Yes, it is palindrome"
	no: .asciiz "No, it is not palindrome"
	
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
	move $t4,$t0
	
	li $t1,10
	li $t2,0
	
	loop:
		beq $t0,$zero,exitloop
		div $t0,$t1
		mflo $t0
		mfhi $t3
		mul $t2,$t2,$t1
		
		add $t2,$t2,$t3
		j loop
	exitloop:
		
		beq $t4,$t2,yesblock
		#else
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