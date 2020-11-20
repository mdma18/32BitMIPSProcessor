#ifndef ALU_H
#define ALU_H

#include "Definitions.h"

class ALU
{
public:
	///Constructor
	ALU();

	///Methods
	bitset<MIPS_32> ALUOp(bitset<OP> mOperation, bitset<MIPS_32> mOperand1, bitset<MIPS_32> mOperand2);

private:
	/// Defined to prevent copying
	ALU(const ALU& other);
	ALU& operator=(const ALU& other) {};
	
	///Attributes
	bitset<MIPS_32> ALUResult;			///< Store ALU result variable
};
#endif // !ALU_H
