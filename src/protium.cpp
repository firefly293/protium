#include <iostream>
#include "protium.h"
#include <sstream>
//#ifdef _WIN32
//#include <windows.h>
//#else
//#include <unistd.h>
//#endif

using namespace std;


#define REGION

// private CPU data classes
#ifdef REGION

#endif



// CPU methods
#ifdef REGION

void CPU::setFlag(FLAGS flag) {
	if (!(flags & (1 << flag))) {
		// flag is not set
		flags ^= 1 << flag;
	}
}

void CPU::unsetFlag(FLAGS flag) {
	if (flags & (1 << flag)) {
		// flag is set
		flags ^= 1 << flag;
	}
}

bool CPU::checkFlag(FLAGS flag) {
	return flags & (1 << flag);
}

void CPU::sto(WORD ptr, BYTE& val) {
			
	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::sto(WORD ptr, WORD& val) {

	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::sto(WORD ptr, DWORD& val) {

	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::sto(WORD ptr, QWORD& val) {

	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::sto(WORD ptr, BYTE* buf, WORD size) {

	for (int i = 0; i < size; i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = buf[i];
	}
}

void CPU::stoSys(WORD ptr, BYTE& val) {

	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::stoSys(WORD ptr, WORD& val) {

	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::stoSys(WORD ptr, DWORD& val) {

	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::stoSys(WORD ptr, QWORD& val) {

	for (int i = 0; i < sizeof(val); i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = val >> (i * 8);
	}
}

void CPU::stoSys(WORD ptr, BYTE* buf, WORD size) {

	for (int i = 0; i < size; i++) {
		// get each byte in succession and put it in ptr + i
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		mem[ptr + i] = buf[i];
	}
}

void CPU::load(WORD ptr, BYTE& to) {
	for (int i = 0; i < sizeof(to); i++) {
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		// set the ith byte to mem[ptr + i]
		to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
	}
}

void CPU::load(WORD ptr, WORD& to) {
	for (int i = 0; i < sizeof(to); i++) {
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		// set the ith byte to mem[ptr + i]
		to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
	}
}

void CPU::load(WORD ptr, DWORD& to) {
	for (int i = 0; i < sizeof(to); i++) {
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		// set the ith byte to mem[ptr + i]
		to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
	}
}

void CPU::load(WORD ptr, QWORD& to) {
	for (int i = 0; i < sizeof(to); i++) {
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		// set the ith byte to mem[ptr + i]
		to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
	}
}

void CPU::load(WORD ptr, BYTE* buf, WORD size) {
	for (int i = 0; i < size; i++) {
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC;
			error(msg.str());
			return;
		}
		// set the ith byte to mem[ptr + i]
		buf[i] = mem[ptr + i];
	}
}

void CPU::cpy(WORD dst, WORD src, WORD size) {
	// check for overflow
	if (dst + size < dst || src + size < src) {
		stringstream msg;
		msg << "Overflow while copying from 0x" << hex << src << " to 0x" << hex << dst << " on PC 0x" << hex << PC;
		error(msg.str());
		return;
	}
	// check for copying into/from sys memory
	if (dst + size >= SYS_MEM_START || src + size >= SYS_MEM_START) {
		stringstream msg;
		msg << "Attempted to copy from/into system memory on PC 0x" << hex << PC;
		error(msg.str());
		return;
	}
	// copy
	memcpy(mem + dst, mem + src, size);
}

WORD* CPU::getReg(BYTE id) {
	if (id == regID::A) return &A;
	if (id == regID::B) return &B;
	if (id == regID::C) return &C;
	if (id == regID::SRC) return &SRC;
	if (id == regID::DST) return &DST;
	if (id == regID::PC) return &PC;
	if (id == regID::SP) return &SP;
	if (id == regID::BP) return &BP;

}

void CPU::updateSysRand() {
	// get 1 byte random at a time, and update each byte of sysRand correspondingly
	for (int i = 0; i < sizeof(sysRand); i++) {
		// set the ith byte to masked rand() to ensure each byte is random
		sysRand = (sysRand & ~(((QWORD)0xFF << (i * 8)))) | ((rand() & 0xFF) << (i * 8));
	}

}

void executeInstruction() {

}

#endif

// non-CPU methods
#ifdef REGION
void CPU::error(string msg) {
	// output message
	cout << endl << "ERROR: " << msg;
	// set halt flag
	setFlag(FLAGS::HF);

}

#endif

// user interaction methods
#ifdef REGION
void CPU::StoreProgram(WORD ptr, BYTE* program, WORD size) {
	// iterate over the program and store the bytes one by one
	for (int i = 0; i < size; i++)
	{
		// check if ptr is out of range
		if (ptr + i < PRGM_MEM_START || ptr + i > PRGM_MEM_END) {
			// is out of range
			stringstream msg;
			msg << "Attempted to write program to 0x" << hex << ptr + i;
			error(msg.str());
			return;
		}
		mem[ptr + i] = program[i];
	}
}

void CPU::SetStartingPoint(WORD startingPoint) {
	if (startingPoint < PRGM_MEM_START || startingPoint > PRGM_MEM_END) {
		// is out of range
		stringstream msg;
		msg << "Invalid starting point 0x" << hex << startingPoint << ", must be from 0x5000 - 0x7FFF";
		error(msg.str());
		return;
	}
	PC = startingPoint;
}

void CPU::Reset() {
	// init registers
	A = B = C = 0;
	SRC = DST = NULLPTR;
	PC = PRGM_MEM_START;
	SP = BP = STACK_END + 1;
	IR = 0;
	AR = HEAP_START;

	// init system variables
	srand(time(NULL));
	clockTime = 0;
	sysRand = 0;

	// clear memory
	for (int i = 0; i < 0x10000; i++) {
		mem[i] = 0;
	}

	// set up special pointers
	stoSys(0xF000, (BYTE*)"PROTIUM", 7); // name of CPU
	stoSys(0xF007, (BYTE*)" AB", 3); // initials
	stoSys(0xF00A, (BYTE*)" SYS VARS:", 10); // label for system variables

	// debugging
	QWORD a = 98000;
	sto(0x5000, a);
	a = 0;
	load(0x5000, a);
}

void CPU::Start() {
	while (!checkFlag(FLAGS::HF)) {
		// update system variables
		updateSysRand();
		stoSys(0xF014, clockTime);
		stoSys(0xF01C, sysRand);

		// load instruction register
		if (PC < PRGM_MEM_START || PC > PRGM_MEM_END || PC + 8 > PRGM_MEM_END) {
			stringstream msg;
			msg << "Invalid PC at 0x" << hex << PC;
			error(msg.str());
			continue;
		}
		load(PC, IR);

		executeInstruction();

		clockTime++;
				
	}
}
#endif


// constructor
CPU::CPU() {
	// init memory
	mem = (BYTE*)malloc(sizeof(BYTE) * 0x10000);
	Reset(); // perform other necessary commands in Reset()
			
}

// destructor
CPU::~CPU() {
	// free mem
	free(mem);
}
