#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Definitions.h"
#include "InstructionMem.h"
#include "ALU.h"
#include "Registers.h"
#include "DataMemory.h"

typedef enum { Fetch, Decode, Execute, WriteBack, MemoryAccess }State;
typedef enum { None, RType, IType, JType }Type;

class Processor
{
public:
	///Constructor
	Processor(string sProgram);

	///Destructor
	virtual ~Processor();

	///Methods
	void InstructionProcess();
	bitset<MIPS_32> NextInstr(bitset<32> programCounter);
	Type InstructionDecode(string sInstruction);
	void ControlUnit(Type Type);
	void OutputResult();

private:
	/// Defined to prevent copying
	Processor(const Processor& other);
	Processor& operator=(const Processor& other) {};

	///Attributes
	InstructionMem*		pInstrMem;			///< Pointer to Instruction Memory
	ALU*				pALU;				///< Pointer to ALU
	Registers*			pRegisters;			///< Pointer to Registers
	DataMemory*			pDataMem;			///< Pointer to Data Memory

	vector<int>			mResult;			///< To store result of programs
	bitset<OP>			mOpcode;			///< Variable to store Opcode
	bitset<MIPS_32>		mInstruction;		///< variable to store the current Instruction
	bitset<MIPS_32>		mProgCount;			///< Variable to store the Program Counter
	bitset<DATA> 		mSourceReg;			///< Variable to store Rs 
	bitset<DATA> 		mSourceReg2;		///< Variable to store Rt
	bitset<DATA> 		mDestinationReg;	///< Variable to store Rd
	bitset<DATA> 		mShiftReg;			///< Variable to store Shift amount 
	bitset<OP>			mFuncReg;			///< Variable to store the Function register 
	bitset<CONST>		mConstant;			///< Constant For I Type instruction
	bitset<TARGET>		mTarget;			///< Constant For J Type instruction
};
#endif // !PROCESSOR_H