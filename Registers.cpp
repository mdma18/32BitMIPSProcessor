#include "Registers.h"

//==============================================================================================
Registers::Registers()
//==============================================================================================
{
	mRegisters.resize(MIPS_32);					//32 bit Registers of size 32
	mRegisters[0] = bitset<MIPS_32>(0);			//Register 0 always set to zero (Zero Register)
}

//==============================================================================================
Registers::~Registers()
//==============================================================================================
{
	mRegisters.clear();
	mRegisters.shrink_to_fit();
}

//==============================================================================================
void Registers::ReadWrite(bitset<DATA> RdReg1, bitset<DATA> RdReg2, 
				bitset<DATA> WrtReg, bitset<MIPS_32> WrtData, bool WrtEnable)
//==============================================================================================
{
	ReadData1 = mRegisters[RdReg1.to_ulong()];		// perform read operation
	ReadData2 = mRegisters[RdReg2.to_ulong()];

	if (WrtEnable)
		mRegisters[WrtReg.to_ulong()] = WrtData;	// Write to destination Register
}

//==============================================================================================
void Registers::DumpRegister()
//==============================================================================================
{
	ofstream RegisterState;						//Dump Register contents			
	RegisterState.open("RegisterState.txt", ios_base::app);
	if (RegisterState.is_open())
	{
		RegisterState << "A state of the Register:" << endl;
		for (int i = 0; i < MIPS_32; i++)
			RegisterState << mRegisters[i] << endl;
	}
	else 
		cout << "Unable to open file";
	RegisterState.close();
}

//==============================================================================================
void Registers::PrintOutput(unsigned long mReg)
//==============================================================================================
{
	ofstream Output;						//Dump Register state after every instruction			
	Output.open("Output.txt", ios_base::app);
	if (Output.is_open())
	{
		Output << "The output of Register " << mReg << " is :" << endl;
		Output << mRegisters[mReg].to_ulong() << endl;
	}
	else
		cout << "Unable to open file";
	Output.close();
}