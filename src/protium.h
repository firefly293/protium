#pragma once
#define REGION

using namespace std;

// typedefs
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef int DWORD;
typedef unsigned long long int QWORD;

class CPU {
	// special pointers
private:
	const WORD STACK_START = 0x0000;
	const WORD STACK_END = 0x0FFF;
	const WORD HEAP_START = 0x1000;
	const WORD HEAP_END = 0x4FFF;
	const WORD PRGM_MEM_START = 0x5000;
	const WORD PRGM_MEM_END = 0x7FFF;
	const WORD EXTRA_MEM_START = 0x8000;
	const WORD EXTRA_MEM_END = 0xEFFF;
	const WORD SYS_MEM_START = 0xF000;
	const WORD NULLPTR = 0xFFFF;

	WORD _;
	WORD A; // reg A
	WORD B; // reg B
	WORD C; // reg C
	WORD SRC; // reg SRC
	WORD DST; // reg DST
	WORD PC; // program counter
	WORD SP; // stack pointer
	WORD BP; // base pointer
	QWORD IR; // instruction register
	WORD AR; // allocation register
	BYTE flags; // flags register


	QWORD clockTime;
	QWORD sysRand;

	// readability classes
#ifdef REGION
public:
/// <summary>
/// contains register IDs
/// </summary>
	class regID {
public:
	static const BYTE _ = 0;
	static const BYTE A = 1;
	static const BYTE B = 2;
	static const BYTE C = 3;
	static const BYTE SRC = 4;
	static const BYTE DST = 5;
	static const BYTE PC = 6;
	static const BYTE SP = 7;
	static const BYTE BP = 8;
	};

	class op {
	public:
		// CPU functions
		static const BYTE HLT = 0x00;
		static const BYTE NOP = 0x01;
		// flag functions
		static const BYTE CLRF = 0x02;
		static const BYTE SETZF = 0x03;
		static const BYTE SETSF = 0x04;
		static const BYTE SETCF = 0x05;
		static const BYTE SETOF = 0x06;
		static const BYTE UNSZF = 0x07;
		static const BYTE UNSSF = 0x08;
		static const BYTE UNSCF = 0x09;
		static const BYTE UNSOF = 0x0A;
		// memory functions
		static const BYTE CLR = 0x10;
		static const BYTE CP = 0x11;
		static const BYTE LDA = 0x12;
		static const BYTE LDB = 0x13;
		static const BYTE LDC = 0x14;
		static const BYTE STOA = 0x15;
		static const BYTE STOB = 0x16;
		static const BYTE STOC = 0x17;
		// general register functions
		static const BYTE MOV = 0x20;
		static const BYTE CLRA = 0x21;
		static const BYTE CLRB = 0x22;
		static const BYTE CLRC = 0x23;
		static const BYTE SETA = 0x24;
		static const BYTE SETB = 0x25;
		static const BYTE SETC = 0x26;
		static const BYTE OFFST = 0x27;
		static const BYTE SWAP = 0x28;
		// address specific register functions
		static const BYTE LDSRC = 0x29;
		static const BYTE LDDST = 0x2A;
		static const BYTE STOSRC = 0x2B;
		static const BYTE STODST = 0x2C;
		static const BYTE SETSRC = 0x2D;
		static const BYTE SETDST = 0x2E;
		// control functions
		static const BYTE CMP = 0x30;
		static const BYTE JMP = 0x31;
		static const BYTE JIZ = 0x32;
		static const BYTE JNZ = 0x33;
		static const BYTE JIS = 0x34;
		static const BYTE JNS = 0x35;
		static const BYTE JIC = 0x36;
		static const BYTE JNC = 0x37;
		static const BYTE JIO = 0x38;
		static const BYTE JNO = 0x39;
		static const BYTE JMPR = 0x3A;
		static const BYTE JIZR = 0x3B;
		static const BYTE JNZR = 0x3C;
		static const BYTE JISR = 0x3D;
		static const BYTE JNSR = 0x3E;
		static const BYTE JICR = 0x3F;
		static const BYTE JNCR = 0x40;
		static const BYTE JIOR = 0x41;
		static const BYTE JNOR = 0x42;
		// subroutine functions
		static const BYTE CALL = 0x43;
		static const BYTE RET = 0x44;
		// stack functions
		static const BYTE PUSH = 0x45;
		static const BYTE POP = 0x46;
		static const BYTE TOP = 0x47;
		// heap functions
		static const BYTE ALLOC = 0x48;
		static const BYTE DEALLOC = 0x49;
		// arithmetic functions
		static const BYTE ADD = 0x50;
		static const BYTE SUB = 0x51;
		static const BYTE MUL = 0x52;
		static const BYTE DIV = 0x53;
		static const BYTE MOD = 0x54;
		static const BYTE INC = 0x55;
		static const BYTE DEC = 0x56;
		static const BYTE SHL = 0x57;
		static const BYTE SHR = 0x58;
		static const BYTE AND = 0x59;
		static const BYTE OR = 0x5A;
		static const BYTE XOR = 0x5B;
		static const BYTE NOT = 0x5C;
		static const BYTE BAND = 0x5D;
		static const BYTE BOR = 0x5E;
		static const BYTE NEQ = 0x5F;
		static const BYTE BNOT = 0x60;
		// input/output
		static const BYTE ININT = 0x61;
		static const BYTE INCH = 0x62;
		static const BYTE INMEM = 0x63;
		static const BYTE OUTINT = 0x64;
		static const BYTE OUTINTS = 0x65;
		static const BYTE OUTCH = 0x66;
		static const BYTE OUTIM = 0x67;
		static const BYTE OUTMEM = 0x68;
		// debugging functions
		static const BYTE RDUMP = 0x70;
		static const BYTE SDUMP = 0x71;
		static const BYTE FDUMP = 0x72;

	};
#endif

	const enum FLAGS {
		OF,
		CF,
		SF,
		ZF,
		_0F,
		_1F,
		_2F,
		HF
	};
private:

	BYTE* mem;

	void setFlag(FLAGS flag);
	void unsetFlag(FLAGS flag);
	bool checkFlag(FLAGS flag);

	void sto(WORD ptr, BYTE& val);
	void sto(WORD ptr, WORD& val);
	void sto(WORD ptr, DWORD& val);
	void sto(WORD ptr, QWORD& val);
	void sto(WORD ptr, BYTE* buf, WORD size);
	void stoSys(WORD ptr, BYTE& val);
	void stoSys(WORD ptr, WORD& val);
	void stoSys(WORD ptr, DWORD& val);
	void stoSys(WORD ptr, QWORD& val);
	void stoSys(WORD ptr, BYTE* buf, WORD size);
	void load(WORD ptr, BYTE& to);
	void load(WORD ptr, WORD& to);
	void load(WORD ptr, DWORD& to);
	void load(WORD ptr, QWORD& to);
	void load(WORD ptr, BYTE* buf, WORD size);
	void push(WORD val);
	void push(DWORD val);
	void push(QWORD val);
	void pop(WORD& to);
	void pop(DWORD& to);
	void pop(QWORD& to);
	void cpy(WORD dst, WORD src, WORD size);
	void jmp(bool condition);
	void jmpr(bool condition);
	WORD* getReg(BYTE id);
	void updateFlags(WORD a, WORD b, WORD result);
	void updateFlags(WORD result);
	void updateSysRand();

	void executeInstruction();

	void error(string msg);

public:
	void StoreProgram(WORD ptr, BYTE* program, WORD size);
	void SetStartingPoint(WORD startingPoint);
	void Reset();
	void Start();
		
	// constructor
	CPU();
	~CPU();
};
