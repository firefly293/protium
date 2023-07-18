# Parts of the CPU Explained
This is a brief explanation of the major parts of this CPU and how they function.
## 1. Registers
Registers are slots within the CPU that hold temporary values. They can be used for a variety of functions including calculations, memory addressing, storing values, and so on.
This CPU has 9 accesible registers:<br>
* * 0. _ : Zero Register. This register always holds the value 0, and whenever it is written to, that value always overrides to 0. This is useful in cases where you need a zero for calculation purposes, or you want to waste the result of an operation. For example, lets say you wanted to add two numbers but you don't care about the result, you just want to use the flags. In this case, you can essentially discard the result by setting the destination register as the zero register. This is also useful in functions like the `pop` instruction. In cases where you want to pop from the stack but don't care what was popped, you can set the parameter to the `pop` function as the zero register to discard the value being popped.
1. A : A Register: This register is a 16 bit general purpose register. You can use it for calculations, storing temporary values, etc.
2. B : B Register: This register is a duplicate of the A register.
3. C : C Register: This register is a duplicate of the A register.
4. SRC : SRC Register: This register holds the address that instructions read from. For example, the instruction `lda` will take the value at address SRC and put it in register A. There are many other functions which use this register. To set it to whatever you want, you can use the `setsrc` instruction.
5. DST : DST Register: This register is very similar to SRC, but it instead holds the address that instructions write to. For example, the instruction `stoa` will write a to the address DST. This register is also used for a destination to jump to in the instructions `jmp`, `call`, etc.
6. PC : Program Counter: The PC register holds the address of the next instruction to be executed. During instrucutes like `jmp` and `call`, the PC is updated in order to jump to the target location.
7. SP : Stack Pointer: The SP register holds the address of the last thing pushed onto the stack. When something is pushed onto the stack, the stack pointer is decremented and the value is put at SP. When a value is popped from the stack, the stack pointer is incremented.
8. BP : Base Pointer: This register holds the address of the current stack frame. It is used to refer to parameters and local variables in a subroutine.
