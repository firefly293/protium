#include <iostream>
using namespace std;

namespace protium {
	/// <summary>
	/// Protium CPU emulator
	/// </summary>
	class CPU {
		// typedefs
		typedef unsigned char BYTE;
		typedef unsigned short WORD;
		typedef int DWORD;
		typedef unsigned long long int QWORD;

		// internal classes
	private:
		/// <summary>
		/// static registers class
		/// </summary>
		class reg {
			static DWORD A;
			static DWORD B;
			static DWORD C;
			static WORD SRC;
			static WORD DST;
			static WORD PC;
			static WORD SP;
			static WORD BP;
		};

		class regID {
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


	};
}