#ifndef REGISTERS_H
#define REGISTERS_H

#include "Definitions.h"
#pragma once

class Registers
{
public:	
	///Constructor
	Registers();
	
	///Destructor
	virtual ~Registers();
	
	///Methods
	void ReadWrite(bitset<DATA> RdReg1, bitset<DATA> RdReg2, bitset<DATA> WrtReg, bitset<MIPS_32> WrtData, bool WrtEnable);
	void DumpRegister();
	void PrintOutput(unsigned long mReg);
	
	///Public Attributes
	bitset<MIPS_32> ReadData1, ReadData2;

private:
	///Defined to prevent copying
	Registers(const Registers& other);
	Registers& operator=(const Registers& other) {};

	///Attributes
	vector<bitset<MIPS_32> > mRegisters;				///< 32 bit Vector for storing Register values
};
#endif // !REGISTERS_H