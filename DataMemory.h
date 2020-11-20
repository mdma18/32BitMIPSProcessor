#ifndef DATAMEMORY_H
#define	DATAMEMORY_H

#include "Definitions.h"

class DataMemory
{
public:
	///constructor
	DataMemory();
	
	///Destructor
	virtual ~DataMemory();

	///Methods
	bitset<MIPS_32> MemoryAccess(bitset<MIPS_32> mAddress, bitset<MIPS_32> mWriteData, bool bReadMem, bool bWriteMem);
	void OutputDataMem();

private:
	/// Defined to prevent copying
	DataMemory(const DataMemory& other);
	DataMemory& operator=(const DataMemory& other) {};

	///Attributes
	vector<bitset<MIPS_32>>	m_vDataMemory;			///< 32 bit Memory vector
	bitset<MIPS_32>			mData;					///< Store data variable
};
#endif // !DATAMEMORY


