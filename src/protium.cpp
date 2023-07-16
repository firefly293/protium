#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

#define REGION


namespace protium {



	// typedefs
	typedef unsigned char BYTE;
	typedef unsigned short WORD;
	typedef int DWORD;
	typedef unsigned long long int QWORD;

	/// <summary>
	/// Protium CPU emulator
	/// </summary>
	class CPU {

		// special pointers
#ifdef REGION
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
#endif

		// private CPU data classes
#ifdef REGION
	private:
		/// <summary>
		/// static registers class
		/// </summary>
		class reg {
		public:
			static DWORD A; // reg A
			static DWORD B; // reg B
			static DWORD C; // reg C
			static WORD SRC; // reg SRC
			static WORD DST; // reg DST
			static WORD PC; // program counter
			static WORD SP; // stack pointer
			static WORD BP; // base pointer
			static QWORD IR; // instruction register
			static WORD AR; // allocation register
			static BYTE flags; // flags register
		};

		/// <summary>
		/// system variables class
		/// </summary>
		class sys {
		public:
			static QWORD clockTime;
			static QWORD sysRand;
		};
#endif

		// private readability classes
#ifdef REGION
	private:
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
			// CPU functions
			static const BYTE HLT = 0x00;
			static const BYTE NOP = 0x01;
			// flag functions
			static const BYTE CLRF = 0x02;
			static const BYTE SETZ = 0x03;
			static const BYTE SETS = 0x04;
			static const BYTE SETC = 0x05;
			static const BYTE SETO = 0x06;
			static const BYTE UNSZ = 0x07;
			static const BYTE UNSS = 0x08;
			static const BYTE UNSC = 0x09;
			static const BYTE UNSO = 0x0A;
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
			static const BYTE DOFFST = 0x28;
			static const BYTE SWAP = 0x29;
			// address specific register functions
			static const BYTE LDSRC = 0x2A;
			static const BYTE LDDST = 0x2B;
			static const BYTE STOSRC = 0x2C;
			static const BYTE STODST = 0x2D;
			static const BYTE SETSRC = 0x2E;
			static const BYTE SETDST = 0x2F;
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
			static const BYTE OUTCH = 0x65;
			static const BYTE OUTMEM = 0x66;
			// debugging functions
			static const BYTE RDUMP = 0x70;
			static const BYTE SDUMP = 0x71;
			static const BYTE FDUMP = 0x72;

		};
#endif

		// private enums
#ifdef REGION
	private:
		const enum FLAGS {
			O,
			C,
			S,
			Z,
			_0,
			_1,
			_2,
			H
		};
#endif

		// CPU variables
#ifdef REGION
	private:
		BYTE* mem;
#endif

		// CPU methods
#ifdef REGION
	private:

		void setFlag(FLAGS flag) {
			if (!(reg::flags & (1 << flag))) {
				// flag is not set
				reg::flags ^= 1 << flag;
			}
		}

		void unsetFlag(FLAGS flag) {
			if (reg::flags & (1 << flag)) {
				// flag is set
				reg::flags ^= 1 << flag;
			}
		}

		bool checkFlag(FLAGS flag) {
			return reg::flags & (1 << flag);
		}

		void sto(WORD ptr, BYTE& val) {
			
			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void sto(WORD ptr, WORD& val) {

			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void sto(WORD ptr, DWORD& val) {

			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void sto(WORD ptr, QWORD& val) {

			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void sto(WORD ptr, BYTE* buf, WORD size) {

			for (int i = 0; i < size; i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= SYS_MEM_START) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = buf[i];
			}
		}

		void stoSys(WORD ptr, BYTE& val) {

			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void stoSys(WORD ptr, WORD& val) {

			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void stoSys(WORD ptr, DWORD& val) {

			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void stoSys(WORD ptr, QWORD& val) {

			for (int i = 0; i < sizeof(val); i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = val >> (i * 8);
			}
		}

		void stoSys(WORD ptr, BYTE* buf, WORD size) {

			for (int i = 0; i < size; i++) {
				// get each byte in succession and put it in ptr + i
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to write to 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				mem[ptr + i] = buf[i];
			}
		}

		void load(WORD ptr, BYTE& to) {
			for (int i = 0; i < sizeof(to); i++) {
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				// set the ith byte to mem[ptr + i]
				to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
			}
		}

		void load(WORD ptr, WORD& to) {
			for (int i = 0; i < sizeof(to); i++) {
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				// set the ith byte to mem[ptr + i]
				to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
			}
		}

		void load(WORD ptr, DWORD& to) {
			for (int i = 0; i < sizeof(to); i++) {
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				// set the ith byte to mem[ptr + i]
				to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
			}
		}

		void load(WORD ptr, QWORD& to) {
			for (int i = 0; i < sizeof(to); i++) {
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				// set the ith byte to mem[ptr + i]
				to = (to & ~(((QWORD)0xFF << (i * 8)))) | (mem[ptr + i] << (i * 8));
			}
		}

		void load(WORD ptr, BYTE* buf, WORD size) {
			for (int i = 0; i < size; i++) {
				if (ptr + i >= NULLPTR) { // make sure ptr is not out of bounds
					stringstream msg;
					msg << "Attempted to read from 0x" << hex << ptr + i << " on PC 0x" << hex << reg::PC;
					error(msg.str());
					return;
				}
				// set the ith byte to mem[ptr + i]
				buf[i] = mem[ptr + i];
			}
		}

		void updateSysRand() {
			// get 1 byte random at a time, and update each byte of sysRand correspondingly
			for (int i = 0; i < sizeof(sys::sysRand); i++) {
				// set the ith byte to masked rand() to ensure each byte is random
				sys::sysRand = (sys::sysRand & ~(((QWORD)0xFF << (i * 8)))) | ((rand() & 0xFF) << (i * 8));
			}

		}

#endif

		// non-CPU methods
#ifdef REGION
	private:
		void error(string msg) {
			// output message
			cout << endl << "ERROR: " << msg;
			// set halt flag
			setFlag(FLAGS::H);

		}

#endif

		// user interaction methods
#ifdef REGION
	public:
		void StoreProgram(WORD ptr, BYTE* program, WORD size) {
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

		void SetStartingPoint(WORD startingPoint) {
			if (startingPoint < PRGM_MEM_START || startingPoint > PRGM_MEM_END) {
				// is out of range
				stringstream msg;
				msg << "Invalid starting point 0x" << hex << startingPoint << ", must be from 0x5000 - 0x7FFF";
				error(msg.str());
				return;
			}
			reg::PC = startingPoint;
		}

		void Reset() {
			// init registers
			reg::A = reg::B = reg::C = 0;
			reg::SRC = reg::DST = NULLPTR;
			reg::PC = 0x5000;
			reg::SP = reg::BP = 0x1000;
			reg::IR = 0;
			reg::AR = 0x1000;

			// init system variables
			srand(time(NULL));
			sys::clockTime = 0;
			sys::sysRand = 0;

			// clear memory
			for (int i = 0; i < 0x10000; i++) {
				mem[i] = 0;
			}

			// set up special pointers
			stoSys(0xF000, (BYTE*)"PROTIUM", 7); // name of CPU
			stoSys(0xF007, (BYTE*)" AB", 3); // initials
			stoSys(0xF00A, (BYTE*)" SYS VARS:", 10); // label for system variables
		}

		void Start() {
			while (!checkFlag(FLAGS::H)) {
				// update system variables
				updateSysRand();
				stoSys(0xF014, sys::clockTime);
				stoSys(0xF01C, sys::sysRand);

				// load instruction register
				if (reg::PC < PRGM_MEM_START || reg::PC > PRGM_MEM_END || reg::PC + 8 > PRGM_MEM_END) {
					stringstream msg;
					msg << "Invalid PC at 0x" << hex << reg::PC;
					error(msg.str());
					continue;
				}

				load(reg::PC, reg::IR);

				
			}
		}
#endif


		// constructor
	public:
		CPU() {
			// init memory
			mem = (BYTE*)malloc(sizeof(BYTE) * 0x10000);
			Reset(); // perform other necessary commands in Reset()
			
		}

		// destructor
	public:
		~CPU() {
			// free mem
			free(mem);
		}


	};
}