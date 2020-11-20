#include "ALU.h"

//==============================================================================================
ALU::ALU()
//==============================================================================================
{
	//Do nothing
}

//==============================================================================================
bitset<MIPS_32> ALU::ALUOp(bitset<OP> mOperation, bitset<MIPS_32> mOperand1, bitset<MIPS_32> mOperand2)
//==============================================================================================
{
	unsigned long uResult(0); //Temporary container to store result 
		
	switch (mOperation.to_ulong())
	{
		case SW:
		case ADDI:
		case ADD:
		case ADDIU:											//FOR I TYPE
			uResult = mOperand1.to_ulong() + mOperand2.to_ulong();
			break;

		case SUB:
			uResult = mOperand1.to_ulong() - mOperand2.to_ulong();
			break;

		case SLT:
			uResult = (mOperand1.to_ulong() < mOperand2.to_ulong()) ? 1 : 0;
			break;

		case BEQ:
			uResult = (mOperand1.to_ulong() == mOperand2.to_ulong()) ? 1 : 0;
			break;

		case BNE:
			uResult = (mOperand1.to_ulong() != mOperand2.to_ulong()) ? 1 : 0;
			break;
	}
	ALUResult = bitset<MIPS_32> (uResult);
	return ALUResult;
}