#include <iostream>
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
		CPU::op::SETC, 0x01, 0x00, // c is now 1
		// start of loop
		CPU::op::CMP, CPU::regID::B, CPU::regID::C, // compare B with 1
		CPU::op::JIZR, 0x10, 0x00, 0x00, 0x00, // jump out of loop if B is 1
		CPU::op::MUL, CPU::regID::A, CPU::regID::A, CPU::regID::B, // a = a * b
		CPU::op::DEC, CPU::regID::B, // decrement B
		CPU::op::JMPR, 0x00, 0x00, 0x0E, 0x00, // jump 14 bytes backwards
		CPU::op::RET // returns from subroutine, answer is stored in A
	};

	protium.StoreProgram(0x5000, factorialProgram, sizeof(factorialProgram));
	protium.SetStartingPoint(0x5000);
	protium.Start();
}