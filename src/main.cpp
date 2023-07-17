#include <iostream>
#include "protium.h"
using namespace std;

int main() {
	CPU protium;

	// does 5 + 3
	BYTE program[] = {
		CPU::op::ININT, CPU::regID::A, // input to A
		CPU::op::ININT, CPU::regID::B, // input to B
		CPU::op::ADD, CPU::regID::C, CPU::regID::A, CPU::regID::B, // C = A + B
		CPU::op::OUTINT, CPU::regID::C // output C
	};

	protium.StoreProgram(0x5000, program, sizeof(program));
	protium.SetStartingPoint(0x5000);
	protium.Start();
}