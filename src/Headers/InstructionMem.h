#ifndef INSTRUCTIONMEM_H
#define INSTRUCTIONMEM_H

#pragma once
#include "Definitions.h"

class InstructionMem
{
public:
	///Constructor
	InstructionMem();
	virtual ~InstructionMem();
	
	///Methods
	void ReadFile(string sFilename);
	bitset<OP> GetOpcode(bitset<MIPS_32> mInstruction);
	bitset<MIPS_32> GetInstruction(bitset<MIPS_32> ReadAddress);
	
private:
	/// Defined to prevent copying
	InstructionMem(const InstructionMem& other);
	InstructionMem& operator=(const InstructionMem& other) {};

	///Attributes
	vector<bitset<MIPS_32>>		m_vMemory;					///< Stores all instructions of a program
	bitset<OP>					mOpcode;					///< Store Opcode
	bitset<MIPS_32>				m_Instruction;				///< Store current Instruction
};
#endif // !INSTRUCTIONMEM_H