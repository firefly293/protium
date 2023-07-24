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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
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
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
			error(msg.str());
			return;
		}
		// set the ith byte to mem[ptr + i]
		to = (to & ~((QWORD)0xFF << (i * 8))) | ((QWORD)mem[ptr + i] << (i * 8));
	}
}

void CPU::load(WORD ptr, BYTE* buf, WORD size) {
	for (int i = 0; i < size; i++) {
		if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
			stringstream msg;
			msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << PC << dec;
			error(msg.str());
			return;
		}
		// set the ith byte to mem[ptr + i]
		buf[i] = mem[ptr + i];
	}
}

void CPU::push(WORD val) {
	// check for stack overflow
	if (SP - sizeof(val) > STACK_END + 1) {
		// stack overflow
		stringstream msg;
		msg << "Stack overflow on PC 0x" << hex << PC << dec;
		error(msg.str());
		return;
	}
	SP -= sizeof(val);
	sto(SP, val);
}

void CPU::push(DWORD val) {
	// check for stack overflow
	if (SP - sizeof(val) > STACK_END + 1) {
		// stack overflow
		stringstream msg;
		msg << "Stack overflow on PC 0x" << hex << PC << dec;
		error(msg.str());
		return;
	}
	SP -= sizeof(val);
	sto(SP, val);
}

void CPU::push(QWORD val) {
	// check for stack overflow
	if (SP - sizeof(val) > STACK_END + 1) {
		// stack overflow
		stringstream msg;
		msg << "Stack overflow on PC 0x" << hex << PC << dec;
		error(msg.str());
		return;
	}
	SP -= sizeof(val);
	sto(SP, val);
}

void CPU::pop(WORD& to) {
	// check for stack underflow
	if (SP + sizeof(to) > STACK_END + 1) {
		// stack underflow
		stringstream msg;
		msg << "Stack underflow on PC 0x" << hex << PC << dec;
		error(msg.str());
		return;
	}
	load(SP, to);
	SP += sizeof(to);
}

void CPU::pop(DWORD& to) {
	// check for stack underflow
	if (SP + sizeof(to) > STACK_END + 1) {
		// stack underflow
		stringstream msg;
		msg << "Stack underflow on PC 0x" << hex << PC << dec;
		error(msg.str());
		return;
	}
	load(SP, to);
	SP += sizeof(to);
}

void CPU::pop(QWORD& to) {
	// check for stack underflow
	if (SP + sizeof(to) > STACK_END + 1) {
		// stack underflow
		stringstream msg;
		msg << "Stack underflow on PC 0x" << hex << PC << dec;
		error(msg.str());
		return;
	}
	load(SP, to);
	SP += sizeof(to);
}


void CPU::cpy(WORD dst, WORD src, WORD size) {
	// check for overflow
	if (dst + size < dst || src + size < src) {
		stringstream msg;
		msg << "Overflow while copying from 0x" << hex << src << " to 0x" << hex << dst << " on PC 0x" << hex << PC << dec;
		error(msg.str());
		return;
	}
	// check for copying into/from sys memory
	if (dst + size >= SYS_MEM_START || src + size >= SYS_MEM_START) {
		stringstream msg;
		msg << "Attempted to copy from/into system memory on PC 0x" << hex << PC << dec;
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

void CPU::updateFlags(WORD a, WORD b, WORD result) {
	flags = 0;
	// update 0 and sign
	if (result == 0) setFlag(FLAGS::ZF);
	if (result >> 7) setFlag(FLAGS::SF);

	// check for carry out
	if (result < a || result < b) setFlag(FLAGS::CF);
	// check for signed overflow
	if ((a >> 7) == (b >> 7) && (result >> 7) != (a >> 7)) setFlag(FLAGS::OF);
}

void CPU::updateFlags(WORD result) {
	if (result == 0) setFlag(FLAGS::ZF);
	if (result >> 7) setFlag(FLAGS::SF);
}

void CPU::updateSysRand() {
	// get 1 byte random at a time, and update each byte of sysRand correspondingly
	for (int i = 0; i < sizeof(sysRand); i++) {
		// set the ith byte to masked rand() to ensure each byte is random
		sysRand = (sysRand & ~(((QWORD)0xFF << (i * 8)))) | ((rand() & 0xFF) << (i * 8));
	}

}

void CPU::executeInstruction() {
	// implement every opcode
	BYTE opcode = IR & 0xFF; // extract lowest byte of IR for opcode

	switch (opcode) {
		// CPU functions
	case op::HLT:
		setFlag(FLAGS::HF);
		PC++;
		break;
	case op::NOP:
		PC++;
		return;
		break;
		// flag functions
	case op::CLRF:
		flags = 0;
		PC++;
		break;
	case op::SETZF:
		setFlag(FLAGS::ZF);
		PC++;
		break;
	case op::SETSF:
		setFlag(FLAGS::SF);
		PC++;
		break;
	case op::SETCF:
		setFlag(FLAGS::CF);
		PC++;
		break;
	case op::SETOF:
		setFlag(FLAGS::OF);
		PC++;
		break;
	case op::UNSZF:
		unsetFlag(FLAGS::ZF);
		PC++;
		break;
	case op::UNSSF:
		unsetFlag(FLAGS::SF);
		PC++;
		break;
	case op::UNSCF:
		unsetFlag(FLAGS::CF);
		PC++;
		break;
	case op::UNSOF:
		unsetFlag(FLAGS::OF);
		PC++;
		break;
		// memory functions
	case op::CLR:
		for (int i = 0; i < (WORD)(IR >> 8); i++) { // IR >> 8 is amount
			if (DST + i >= SYS_MEM_START) break;
			mem[DST + i] = 0;
		}
		PC += 3;
		break;
	case op::CP:
		cpy(DST, SRC, (WORD)(IR >> 8));
		PC += 3;
		break;
	case op::LDA:
		load(SRC, A);
		PC++;
		break;
	case op::LDB:
		load(SRC, B);
		PC++;
		break;
	case op::LDC:
		load(SRC, C);
		PC++;
		break;
	case op::STOA:
		sto(DST, A);
		PC++;
		break;
	case op::STOB:
		sto(DST, B);
		PC++;
		break;
	case op::STOC:
		sto(DST, C);
		PC++;
		break;
		// general register functions
	case op::MOV:
	{WORD* dstreg = getReg(IR >> 8);
	WORD* srcreg = getReg(IR >> 16);
	*dstreg = *srcreg; }
	PC += 3;
	break;
	case op::CLRA:
		A = 0;
		PC++;
		break;
	case op::CLRB:
		B = 0;
		PC++;
		break;
	case op::CLRC:
		C = 0;
		PC++;
		break;
	case op::SETA:
		A = (WORD)(IR >> 8);
		PC += 3;
		break;
	case op::SETB:
		B = (WORD)(IR >> 8);
		PC += 3;
		break;
	case op::SETC:
		C = (WORD)(IR >> 8);
		PC += 3;
		break;
	case op::OFFST:
		if ((BYTE)(IR >> 8)) {
			// forwards
			WORD* reg = getReg(IR >> 16);
			WORD* basereg = getReg(IR >> 24);
			*reg = *basereg + (WORD)(IR >> 32);
		}
		else {
			// backwards
			WORD* reg = getReg(IR >> 16);
			WORD* basereg = getReg(IR >> 24);
			*reg = *basereg - (WORD)(IR >> 32);
		}
		PC += 6;
		break;
	case op::SWAP:
	{WORD* reg1 = getReg(IR >> 8);
	WORD* reg2 = getReg(IR >> 16);
	WORD tmp;
	tmp = *reg1;
	*reg1 = *reg2;
	*reg2 = tmp;
	}
	PC += 3;
	break;
	// address specific register functions
	case op::LDSRC:
		load((WORD)(IR >> 8), SRC);
		PC += 3;
		break;
	case op::LDDST:
		load((WORD)(IR >> 8), DST);
		PC += 3;
		break;
	case op::STOSRC:
		sto((WORD)(IR >> 8), SRC);
		PC += 3;
		break;
	case op::STODST:
		sto((WORD)(IR >> 8), DST);
		PC += 3;
		break;
	case op::SETSRC:
		SRC = IR >> 8;
		PC += 3;
		break;
	case op::SETDST:
		DST = IR >> 8;
		PC += 3;
		break;
	case op::CMP:
	{WORD* reg1 = getReg(IR >> 8);
	WORD* reg2 = getReg(IR >> 16);
	updateFlags(*reg1, -(*reg2), *reg1 - *reg2);
	}
	PC += 3;
	break;
	case op::JMP:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		PC = DST;
		break;
	case op::JIZ:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (checkFlag(ZF)) PC = DST;
		else PC++;
		break;
	case op::JNZ:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (!checkFlag(ZF)) PC = DST;
		else PC++;
		break;
	case op::JIS:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (checkFlag(SF)) PC = DST;
		else PC++;
		break;
	case op::JNS:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (!checkFlag(SF)) PC = DST;
		else PC++;
		break;
	case op::JIC:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (checkFlag(CF)) PC = DST;
		else PC++;
		break;
	case op::JNC:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (!checkFlag(CF)) PC = DST;
		else PC++;
		break;
	case op::JIO:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (checkFlag(OF)) PC = DST;
		else PC++;
		break;
	case op::JNO:
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attempted to jump to invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		if (!checkFlag(OF)) PC = DST;
		else PC++;
		break;
	case op::JMPR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	PC += forward;
	PC -= backward;
	}
	break;
	case op::JIZR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (checkFlag(ZF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	case op::JNZR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (!checkFlag(ZF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	case op::JISR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (checkFlag(SF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	case op::JNSR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (!checkFlag(SF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	case op::JICR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (checkFlag(CF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	case op::JNCR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (!checkFlag(CF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	case op::JIOR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (checkFlag(OF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	case op::JNOR:
	{WORD forward = (WORD)(IR >> 8);
	WORD backward = (WORD)(IR >> 24);
	if (PC + forward > PRGM_MEM_END - 8 || PC - backward < PRGM_MEM_START) {
		stringstream msg;
		msg << "Attempted to jump to invalid location 0x" << hex << PC + forward << " or 0x" << hex << PC - backward << dec;
		error(msg.str());
		break;
	}
	if (!checkFlag(OF)) {
		PC += forward;
		PC -= backward;
	}
	else PC += 5;
	}
	break;
	// subroutine functions
	case op::CALL:
		// make sure DST is within bounds
		if (DST < PRGM_MEM_START || DST > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Attemped to call invalid location 0x" << hex << DST << dec;
			error(msg.str());
			break;
		}
		// push PC
		PC++;
		push(PC);
		// push BP
		push(BP);
		// update BP
		BP = SP;
		// jump to subroutine
		PC = DST;
		break;
	case op::RET:
		SP = BP;
		pop(BP);
		pop(PC);
		break;
		// stack functions
	case op::PUSH:
		push(*(getReg(IR >> 8)));
		PC += 2;
		break;
	case op::POP:
		pop(*(getReg(IR >> 8)));
		PC += 2;
		break;
	case op::TOP:
		load(SP, *(getReg(IR >> 8)));
		PC += 2;
		break;
		// heap functions
	case op::ALLOC:
		// check for enough space/overflow
		if (AR + *(getReg(IR >> 8)) - 1 > HEAP_END || AR + *(getReg(IR >> 8)) - 1 < AR) {
			stringstream msg;
			msg << "Ran out of space on heap on PC 0x" << hex << PC << dec;
			error(msg.str());
			break;
		}
		DST = AR;
		AR += *(getReg(IR >> 8));
		PC += 2;
		break;
	case op::DEALLOC:
		// check for enough space / overflow
		if (AR - *(getReg(IR >> 8)) < HEAP_START || AR - *(getReg(IR >> 8)) > AR) {
			AR = HEAP_START;
		}
		else
			AR -= *(getReg(IR >> 8));
		PC += 2;
		break;
		// arithmetic functions
	case op::ADD:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) + (*reg2);
		updateFlags(*reg1, *reg2, result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::SUB:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) - (*reg2);
		updateFlags(*reg1, -(*reg2), result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::MUL:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) * (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::DIV:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) / (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::MOD:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) % (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::INC:
		*(getReg(IR >> 8)) += 1;
		PC += 2;
		break;
	case op::DEC:
		*(getReg(IR >> 8)) -= 1;
		PC += 2;
		break;
	case op::SHL:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) << (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::SHR:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) >> (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::AND:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) & (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::OR:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) | (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::XOR:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) ^ (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::NOT:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg = getReg(IR >> 16);
		WORD result = ~(*reg);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 3;
		break;
	case op::BAND:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) && (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::BOR:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) || (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::NEQ:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg1 = getReg(IR >> 16);
		WORD* reg2 = getReg(IR >> 24);
		WORD result = (*reg1) != (*reg2);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 4;
		break;
	case op::BNOT:
		{
		WORD* dstreg = getReg(IR >> 8);
		WORD* reg = getReg(IR >> 16);
		WORD result = !(*reg);
		updateFlags(result);
		*dstreg = result;
		}
		PC += 3;
		break;
		// i/o
	case op::ININT:
		{
		WORD* reg = getReg(IR >> 8);
		cin >> *reg;
		}
		PC += 2;
		break;
	case op::INCH:
		*(getReg(IR >> 8)) = cin.get();
		PC += 2;
		break;
	case op::INMEM:
		{
		BYTE amount = IR >> 8;
		for (int i = 0; i < amount; i++) {
			if (DST + i >= SYS_MEM_START) {
				stringstream msg;
				msg << "Attempted to input to memory location 0x" << hex << DST + i << dec;
				error(msg.str());
				break;
			}
			mem[DST + i] = cin.get();
		}
		}
		PC += 2;
		break;
	case op::OUTINT:
		cout << *(getReg(IR >> 8));
		PC += 2;
		break;
	case op::OUTINTS:
		cout << (short)(*(getReg(IR >> 8)));
	case op::OUTCH:
		cout << (char)(*(getReg(IR >> 8)));
		PC += 2;
		break;
	case op::OUTIM:
		cout << (char)(IR >> 8);
		PC += 2;
		break;
	case op::OUTMEM:
		{
		BYTE amount = IR >> 8;
		for (int i = 0; i < amount; i++) {
			if (SRC + i >= SYS_MEM_START) {
				stringstream msg;
				msg << "Attempted to output from memory location 0x" << hex << SRC + i << dec;
				error(msg.str());
				break;
			}
			cout << (char)mem[SRC + i];
		}
		}
		PC += 2;
		break;
		// debugging functions
	case op::RDUMP:
		cout << "\nREGISTERS:\nA: " << A << dec;
		cout << "\nB: " << B << dec;
		cout << "\nC: " << C << dec;
		cout << "\nSRC: 0x" << hex << SRC << dec;
		cout << "\nDST: 0x" << hex << DST << dec;
		cout << "\nPC: 0x" << hex << PC << dec;
		cout << "\nSP: 0x" << hex << SP << dec;
		cout << "\nBP: 0x" << hex << BP << "\n" << dec;
		PC++;
		break;
	case op::SDUMP:
		cout << "\nSTACK:\n";
		for (int i = 0xFFE; i >= SP; i -= 2) {
			cout << hex << mem[i + 1] << ' ' << hex << mem[i] << '\n' << dec;
		}
		PC++;
		break;
	case op::FDUMP:
		cout << "\nFLAGS:\nHF: " << checkFlag(HF);
		cout << "\nZF: " << checkFlag(ZF);
		cout << "\nSF: " << checkFlag(SF);
		cout << "\nCF: " << checkFlag(CF);
		cout << "\nOF: " << checkFlag(OF) << '\n';
		PC++;
		break;
	default:
		stringstream msg;
		msg << "Invalid opcode 0x" << hex << opcode;
		error(msg.str());
		break;

	}
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
			msg << "Attempted to write program to 0x" << hex << ptr + i << dec;
			error(msg.str());
			return;
		}
		mem[ptr + i] = program[i];
	}
}

void CPU::SetStartingPoint(WORD startingPoint) {
	if (startingPoint < PRGM_MEM_START || startingPoint > PRGM_MEM_END - 8) {
		// is out of range
		stringstream msg;
		msg << "Invalid starting point 0x" << hex << startingPoint << ", must be from 0x5000 - 0x7FFF" << dec;
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
		
		// set _ to 0
		_ = 0;

		// load instruction register
		if (PC < PRGM_MEM_START || PC > PRGM_MEM_END || PC > PRGM_MEM_END - 8) {
			stringstream msg;
			msg << "Invalid PC at 0x" << hex << PC << dec;
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
