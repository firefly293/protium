# Instruction set for the Protium CPU

## Notes
* All values within instructions are stored in little-endian format, meaning their least significant byte goes first.
  * For example, the number `0x503A` would be written in an instruction as `0x3A50`, or `0x3A, 0x50`.
* To specify a register, you use its corresponding identification number:
  * 0 : _ -> zero register
  * 1 : A -> 16bit signed general-purpose
  * 2 : B -> 16bit signed general-purpose
  * 3 : C -> 16bit signed general-purpose
  * 4 : SRC -> 16bit unsigned address
  * 5 : DST -> 16bit unsigned address
  * 6 : PC -> 16bit unsigned address
  * 7 : SP -> 16bit unsigned address
  * 8 : BP -> 16bit unsigned address
* The flags are set based on the result of arithmetic operations.
  * If the result is 0, the zero flag (ZF) is set.
  * If the sign bit is set, the sign flag (SF) is set.
  * If the result has a signed overflow, the overflow flag (OF) is set.
  * If the result has a carry out, the carry flag (CF) is set.

## Instructions:

### CPU FUNCTIONS
```php
0x00 : hlt // stops the cycles by setting HF flag

0x01 : nop // skips a cycle
```
### FLAG FUNCTIONS
```php
0x02 : clrf // clears all the flags

0x03 : setzf // sets ZF

0x04 : setsf // sets SF

0x05 : setcf // sets CF

0x06 : setof // sets OF

0x07 : unszf // unsets ZF

0x08 : unssf // unsets SF

0x09 : unscf // unsets CF

0x0A : unsof // unsets OF
```
### MEMORY FUNCTIONS
```php
0x10 : clr [amountbyte1] [amountbyte2] // clears amount bytes from dst in memory

0x11 : cp [amountbyte1] [amountbyte2] // copies amount bytes from src to dst in memory

0x12 : lda // loads from src into reg A

0x13 : ldb // loads from src into reg B

0x14 : ldc // loads from src into reg C

0x15 : stoa // stores from reg A to dst

0x16 : stob // stores from reg B to dst

0x17 : stoc // stores from reg C to dst
```
### GENERAL REGISTER FUNCTIONS
```php
0x20 : mov [dstreg] [srcreg] // copies the value from srcreg to dstreg

0x21 : clra // clears register A

0x22 : clrb // clears register B

0x23 : clrc // clears register C

0x24 : seta [valuebyte1] [valuebyte2]  // sets register A to value

0x25 : setb [valuebyte1] [valuebyte2] // sets register B to value

0x26 : setc [valuebyte1] [valuebyte2] // sets register C to value

0x27 : offst [forwards] [reg] [basereg] [valuebyte1] [valuebyte2] // sets reg to basereg +- value (if forward, then +, else minus

0x28 : swap [reg1] [reg2] // swaps the values of reg1 and reg2
```
### ADDRESS SPECIFIC REGISTER FUNCTIONS
```php
0x29 : ldsrc [addressbyte1] [addressbyte2] // loads src with the value at address

0x2A : lddst [addressbyte1] [addressbyte2] // loads dst with the value at address

0x2B : stosrc [addressbyte1] [addressbyte2] // stores value of src into address

0x2C : stodst [addressbyte1] [addressbyte2] // stores value of dst into address

0x2D : setsrc [valuebyte1] [valuebyte2] // sets src to value

0x2E : setdst [valuebyte1] [valuebyte2] // sets dst to value
```
### CONTROL FUNCTIONS
```php
0x30 : cmp [reg1] [reg2] // subtracts reg2 from reg1 and sets the flags accordingly

0x31 : jmp // jumps unconditionally to dst

0x32 : jiz // jumps to dst if zero flag is set

0x33 : jnz // jumps to dst if zero flag is not set

0x34 : jis // jumps to dst if sign flag is set

0x35 : jns // jumps to dst if sign flag is not set

0x36 : jic // jumps to dst if carry flag is set

0x37 : jnc // jumps to dst if carry flag is not set

0x38 : jio // jumps to dst if overflow flag is set

0x39 : jno // jumps to dst if overflow flag is not set

0x3A : jmpr [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps unconditionally by either forward or backward relative to current PC, either forward or backward has to be 0

0x3B : jizr [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if zero flag is set by either forward or backward relative to current PC, either forward or backward has to be 0

0x3C : jnzr [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if zero flag is not set by either forward or backward relative to current PC, either forward or backward has to be 0

0x3D : jisr [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if sign flag is set by either forward or backward relative to current PC, either forward or backward has to be 0

0x3E : jnsr [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if sign flag is not set by either forward or backward relative to current PC, either forward or backward has to be 0

0x3F : jicr [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if carry flag is set by either forward or backward relative to current PC, either forward or backward has to be 0

0x40 : jncr [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if carry flag is not set by either forward or backward relative to current PC, either forward or backward has to be 0

0x41 : jior [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if overflow flag is set by either forward or backward relative to current PC, either forward or backward has to be 0

0x42 : jnor [forwardbyte1] [forwardbyte2] [backwardbyte1] [backwardbyte2] // jumps if overflow flag is not set by either forward or backward relative to current PC, either forward or backward has to be 0
```
### SUBROUTINE FUNCTIONS
```php
0x43 : call // 1) pushes PC to the stack, 2) push current BP, 3) update BP, 4) jump to subroutine

0x44 : ret // 1) deallocate local variables by setting SP to BP 2) pop to BP 3) pop to PC
```
### STACK FUNCTIONS
```php
0x45 : push [reg] // pushes reg to the stack and decrements stack pointer by 2

0x46 : pop [reg] // pops next 2 from stack and puts it in the register, increments stack pointer by 2

0x47 : top [reg] // puts 2 bytes from top of stack into reg
```
### HEAP FUNCTIONS
```php
0x48 : alloc [reg] // allocates the amount by incrementing allocation pointer by amount, if there isn't enough space puts nullptr in dst, else puts allocation pointer in dst

0x49 : dealloc [reg] // deallocates the amount by decrementing allocation pointer by amount, if not enough is already allocated, deallocates everything
```
### ARITHMETIC FUNCTIONS
```php
0x50 : add [dstreg] [reg1] [reg2] // adds reg1 and reg2 and puts the result in dstreg

0x51 : sub [dstreg] [reg1] [reg2] // subtracts reg1 and reg2 and puts the result in dstreg

0x52 : mul [dstreg] [reg1] [reg2] // multiplies reg1 and reg2 and puts the result in dstreg

0x53 : div [dstreg] [reg1] [reg2] // divides reg1 and reg2 and puts the result in dstreg

0x54 : mod [dstreg] [reg1] [reg2] // mods reg1 and reg2 and puts the result in dstreg

0x55 : inc [reg] // increments the value in reg

0x56 : dec [reg] // decrements the value in reg

0x57 : shl [dstreg] [reg1] [reg2] // left shifts reg1 by reg2 and puts the result in dstreg

0x58 : shr [dstreg] [reg1] [reg2] // right shifts reg1 by reg2 and puts the result in dstreg

0x59 : and [dstreg] [reg1] [reg2] // bitwise ands reg1 and reg2 and puts result in dstreg

0x5A : or [dstreg] [reg1] [reg2] // bitwise ors reg1 and reg2 and puts result in dstreg

0x5B : xor [dstreg] [reg1] [reg2] // bitwise xors reg1 and reg2 and puts result in dstreg

0x5C : not [dstreg] [reg] // bitwise nots reg1 and puts result in dstreg

0x5D : band [dstreg] [reg1] [reg2] // boolean ands reg1 and reg2 and puts result in dstreg

0x5E : bor [dstreg] [reg1] [reg2] // boolean ors reg1 and reg2 and puts result in dstreg

0x5F : neq [dstreg] [reg1] [reg2] // boolean not equals reg1 and reg2 and puts result in dstreg

0x60 : bnot [dstreg] [reg] // boolean nots reg1 and puts result in dstreg
```
### INPUT/OUTPUT
```php
0x61 : inint [reg] // gets next integer value from input stream and puts it in reg

0x62 : inch [reg] // gets next character from input stream and puts it in reg

0x63 : inmem [amount] // gets next amount bytes from input stream and puts it to dst address

0x64 : outint [reg] // outputs the register as an int

0x65 : outints [reg] // outputs the register as a signed int

0x66 : outch [reg] // outputs the register as a character

0x67 : outim [char] // outputs the character

0x68 : outmem [amount] // outputs amount characters from src
```
### DEBUGGING FUNCTIONS
```php
0x70 : rdump // prints all registers

0x71 : sdump // prints contents of stack bottom to top

0x72 : fdump // prints all flags
```
