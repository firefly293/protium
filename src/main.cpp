#include <iostream>
#include <iomanip>
#include "protium.h"
using namespace std;

int main() {
	CPU protium;

	// does factorial
	BYTE factorialProgram[] = {
		// main
		CPU::op::ININT, CPU::regID::A, // input number to A
		CPU::op::SETDST, 0x09, 0x50, // setdst to factorial subroutine at 0x5009
		CPU::op::CALL, // call the factorial
		CPU::op::OUTINT, CPU::regID::A,
		CPU::op::HLT, // stop at the end of main
		// start of factorial subroutine
		CPU::op::MOV, CPU::regID::B, CPU::regID::A, // copy a into b
		CPU::op::DEC, CPU::regID::B, // b will be what a is multiplyed by each loop
		CPU::op::SETC, 0x02, 0x00, // c is now 1
		// start of loop
		CPU::op::CMP, CPU::regID::B, CPU::regID::C, // compare B with 1
		CPU::op::JISR, 0x10, 0x00, 0x00, 0x00, // jump out of loop if B < 2
		CPU::op::MUL, CPU::regID::A, CPU::regID::A, CPU::regID::B, // a = a * b
		CPU::op::DEC, CPU::regID::B, // decrement B
		CPU::op::JMPR, 0x00, 0x00, 0x0E, 0x00, // jump 14 bytes backwards
		CPU::op::RET // returns from subroutine, answer is stored in A
	};

	// test overflow flag
	BYTE testOverflowProgram[] = {
		CPU::op::SETA, 0x40, 0x9C, // set a to 40,000
		CPU::op::MOV, CPU::regID::B, CPU::regID::A, // set b to 40,000
		CPU::op::ADD, CPU::regID::C, CPU::regID::A, CPU::regID::B, // C = a + b
		CPU::op::OUTINT, CPU::regID::C, // output result
		CPU::op::OUTIM, '\n',
		CPU::op::JNOR, 0x0B, 0x00, 0x00, 0x00, // if not overflow, jump to not overflow print
		// is overflow
		CPU::op::SETC, 0x01, 0x00, // if overflow, set C to 1
		CPU::op::OUTINT, CPU::regID::C, // output C
		CPU::op::HLT, // halt after outputting C
		// not overflow
		CPU::op::CLRC, // set c to 0
		CPU::op::OUTINT, CPU::regID::C, // output C
		CPU::op::HLT // halt
	};

	BYTE guessingGameProgram[] = {
		CPU::op::SETSRC, 0x1C, 0xF0, // set src to address of system random
		CPU::op::LDA, // set a to the random value
		CPU::op::SETB, 0x64, 0x00, // set B to 100
		CPU::op::MOD, CPU::regID::A, CPU::regID::A, CPU::regID::B, // make random number 0 to 100
		// start loop
		CPU::op::ININT, CPU::regID::B, // b now has the guess
		CPU::op::CMP, CPU::regID::A, CPU::regID::B, // compare A and B
		CPU::op::JIZR, 0x21, 0x00, 0x00, 0x00, // jump out of loop (33 bytes forward) if equal
		CPU::op::JISR, 0x0A, 0x00, 0x00, 0x00, // if sign, then b > a so jump 10 bytes forward
		CPU::op::JNSR, 0x0E, 0x00, 0x00, 0x00, // if not sign, b < a so jump 14 bytes foward
		// case b > a (JISR)
		CPU::op::OUTIM, '>', // if b > a, output >
		CPU::op::OUTIM, '\n', // newline
		CPU::op::JMPR, 0x00, 0x00, 0x18, 0x00, // go back to start of loop, 24 bytes back
		// case b < a (JNSR)
		CPU::op::OUTIM, '<', // if b < a, output <
		CPU::op::OUTIM, '\n', // newline
		CPU::op::JMPR, 0x00, 0x00, 0x21, 0x00, // go back to start of loop (33 bytes back)
		// case equal
		CPU::op::OUTIM, '=', // if equal, output =
		CPU::op::HLT // end
	};

	BYTE recursiveFactorialProgram[] = {
		CPU::op::SETC, 0x02, 0x00, // set C to 2
		CPU::op::ININT, CPU::regID::A, // input number into A
		CPU::op::SETDST, 0x0C, 0x50, // set dst to 0x500C, address of factorial subroutine
		CPU::op::CALL, // call the factorial subroutine
		CPU::op::OUTINT, CPU::regID::A, // result of factorial is stored in A, so output it
		CPU::op::HLT, // halt at the end of main
		// start of subroutine, A has the number to be factorialized
		CPU::op::CMP, CPU::regID::A, CPU::regID::C, // compare a and c (2)
		CPU::op::JNSR, 0x09, 0x00, 0x00, 0x00, // if a >= 2, then jump to recursion part
		CPU::op::SETA, 0x01, 0x00, // if a is < 2, set factorial result to 1
		CPU::op::RET, // return
		CPU::op::PUSH, CPU::regID::A, // push a to store it so that it can be multiplied by (a-1)!
		CPU::op::DEC, CPU::regID::A, // decrement A
		CPU::op::CALL, // call factorial subroutine
		CPU::op::POP, CPU::regID::B, // B now holds the stored value of A
		CPU::op::MUL, CPU::regID::A, CPU::regID::A, CPU::regID::B, // a = a * b
		CPU::op::RET

	};

	cout << "HEXDUMP:\n";
	for (BYTE b : recursiveFactorialProgram) {
		cout << "0x" << hex << setw(2) << setfill('0') << (int)b << ' ' << dec;
	}
	cout << endl;

	protium.StoreProgram(0x5000, recursiveFactorialProgram, sizeof(recursiveFactorialProgram));
	protium.SetStartingPoint(0x5000);
	protium.Start();
}