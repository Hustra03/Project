  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #

.global delay
.global time2string
.global hexasc
.global enable_interrupt
.data
.align 2
mytime:	.word 0x5957
timstr:	.ascii ""
.text

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg, 0($sp)
.endm

.macro	POP reg
	lw	\reg, 0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

  	
main:
# print timstr
la $a0,timstr
li $v0,4
syscall
nop
# wait a little
li $a0,60
jal delay
nop
# call tick
la $a0,mytime
jal tick
nop
# call your function time2string
la $a0,timstr
la $t0,mytime
lw $a1,0($t0)
jal time2string
nop
# print a newline
li $a0,10
li $v0,11
syscall
nop
# go back and do it all again
j main
nop
# tick: update time pointed to by $a0
tick: lw $t0,0($a0) # get time
addiu $t0,$t0,1 # increase
andi $t1,$t0,0xf # check lowest digit
sltiu $t2,$t1,0xa # if digit < a, okay
bnez $t2,tiend
nop
addiu $t0,$t0,0x6 # adjust lowest digit
andi $t1,$t0,0xf0 # check next digit
sltiu $t2,$t1,0x60 # if digit < 6, okay
bnez $t2,tiend
nop
addiu $t0,$t0,0xa0 # adjust digit
andi $t1,$t0,0xf00 # check minute digit
sltiu $t2,$t1,0xa00 # if digit < a, okay
bnez $t2,tiend
nop
addiu $t0,$t0,0x600 # adjust digit
andi $t1,$t0,0xf000 # check last digit
sltiu $t2,$t1,0x6000 # if digit < 6, okay
bnez $t2,tiend
nop
addiu $t0,$t0,0xa000 # adjust last digit
tiend: sw $t0,0($a0) # save updated result
jr $ra # return
nop
delay:
	PUSH $ra
	whileloop:
	slt  $t0,$zero,$a0  # a0 register is the argument for delay . if ms > 0   then t0 = 1 which mean
	bne  $t0,1,done # if t0=! 1 which means ms<=0 leave the loop
	nop
	addi $a0,$a0,-1
	la $t1, ($zero)
	la $t2,($zero)
	forloop:
		#do nothing
		nop
		addi $t1,$t1,1 # i++
		slti $t2,$t1,5500# i<4711 ms change dealy in ms
		bne  $t2, $zero, forloop # if t2=!0 then
	nop
j whileloop
nop
done:
POP $ra
jr $ra
nop
time2string:
PUSH $ra # push the return reg
PUSH $s0
PUSH $s1
move $s0,$a1 # move the value of a1 to t1  a1= mytime
move $s1,$a0
add $t0,$zero,$zero
loopit:
and $a0,$s0,0xF000
srl $a0,$a0,12 # shift the number to the first byte
sll $s0,$s0,4 # shift 1 byte to left to get the next from the last number in time
jal  hexasc # convert the number to hex
nop
sb  $v0,0($s1) # store the number in reg
addi $s1,$s1,0x1 # next address to save the number in

addi $t0,$t0,1 # the loop counter
beq  $t0, 2, colon # if we printed the second number we jump to the colon
nop
bne  $t0, 4, loopit
nop

beq  $v0,0x32,two
nop



end:
li  $t1,0x00
sb  $t1,0($s1)
move $t1,$zero
POP $s1
POP $s0
POP $ra
move $t0,$zero
jr $ra
nop

enable_interrupt:
ei
jr $ra
nop


colon:
li $t1,0x3A
sb  $t1,0($s1)
addi $s1,$s1,0x1
move $t1,$zero
j loopit
nop
two:
sub $s1,$s1,1
li $t1,0x54
sb  $t1,0($s1)
addi $s1,$s1,0x1
li $t1,0x57
sb  $t1,0($s1)
addi $s1,$s1,0x1
li $t1,0x4F
sb  $t1,0($s1)
addi $s1,$s1,0x1
move $t1,$zero
j end
nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc:
andi $a0,$a0,0xF
addi $v0,$a0,0x30
blt $a0, 10, finish
nop
addi $v0, $v0, 0x7 #jump to A to F in ASCII
finish:
jr $ra
nop