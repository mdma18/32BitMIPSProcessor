#include "DataMemory.h"

///Contructor: Initialise memory size
//==============================================================================================
DataMemory::DataMemory():
//==============================================================================================
m_vDataMemory(MemSize)
{
	//Do Nothing
}

///Destructor: Clear vector
//==============================================================================================
DataMemory::~DataMemory()
//==============================================================================================
{
	m_vDataMemory.clear();
	m_vDataMemory.shrink_to_fit();
}

///Method: Write to Memory  
//==============================================================================================
bitset<MIPS_32> DataMemory::MemoryAccess(bitset<MIPS_32> mAddress, bitset<MIPS_32> mWriteData, 
											bool bReadMem, bool bWriteMem)
//==============================================================================================
{
	if (bReadMem && !bWriteMem)
		return m_vDataMemory[mAddress.to_ulong()];
	
	else if (!bReadMem && bWriteMem) 
	{
		m_vDataMemory[mAddress.to_ulong()] = mWriteData; ///Write data to speicifed register
	}
	return mAddress;
}

///Method: Output Memory 
//==============================================================================================
void DataMemory::OutputDataMem()
//==============================================================================================
{
	ofstream Output;
	Output.open("MemoryOutput.txt");
	vector<bitset<MIPS_32>>::iterator it;
	bitset<MIPS_32> mValue;
	if (Output.is_open())
	{
		for (it = m_vDataMemory.begin(); it != m_vDataMemory.end(); ++it)    
		{
			mValue = *it;
			if(mValue != 0)
				Output << *it << endl;
		}
	}
	else 
		cout << "Unable to open file";
	Output.close();
}