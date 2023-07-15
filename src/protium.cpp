#include <iostream>
using namespace std;

#define REGION


namespace protium {
	/// <summary>
	/// Protium CPU emulator
	/// </summary>
	class CPU {

		// typedefs
#ifdef REGION
	public:
		typedef unsigned char BYTE;
		typedef unsigned short WORD;
		typedef int DWORD;
		typedef unsigned long long int QWORD;
#endif

		// special pointers
#ifdef REGION
	private:
		/// <summary>
		/// used as null pointer
		/// </summary>
		WORD NULLPTR = 0xFFFF;
#endif

		// private classes
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
		};

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
#endif


		// constructor
	public:
		CPU() {
			// init registers
			reg::A = reg::B = reg::C = 0;
			reg::SRC = reg::DST = NULLPTR;
			reg::PC = 0x5000;
			reg::SP = reg::BP = 0x1000;

		}


	};
}