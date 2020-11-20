#include "InstructionMem.h"

///Constructor: Initialise Register 
//==============================================================================================
InstructionMem::InstructionMem():
//==============================================================================================
mOpcode(""),
m_vMemory(MemSize)
{

}

///Destructor: Clear Register
//==============================================================================================
InstructionMem::~InstructionMem()
//==============================================================================================
{
	m_vMemory.clear();
	m_vMemory.shrink_to_fit();
}

///Method: Read from a file line by line. Convert line to bits and store in memory
//==============================================================================================
void InstructionMem::ReadFile(string sFilename)
//==============================================================================================
{
	ifstream File(sFilename);

	if (File.is_open())
	{
		string sLine;
		for (int i = 0; getline(File, sLine); i++)	///Just get 32 bits instruction
		{
			m_vMemory[i] = bitset<MIPS_32>(sLine);
		}
	}
	else 
		cout << "Unable to open file";
	File.close();
}

///Method: Return Instruction
//==============================================================================================
bitset<MIPS_32> InstructionMem::GetInstruction(bitset<MIPS_32> ReadAddress)
//==============================================================================================
{
	return m_vMemory[ReadAddress.to_ulong()];
}

///Method: Return Opcode
//==============================================================================================
bitset<OP> InstructionMem::GetOpcode(bitset<MIPS_32> mInstruction)
//==============================================================================================
{
	string sTemp = mInstruction.to_string();
	mOpcode = bitset<OP>(sTemp.substr(0, 6));
	return mOpcode;
}