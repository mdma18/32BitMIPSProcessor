#include "Processor.h"

///Constructor: Initialise variables
//==============================================================================================
Processor::Processor(string sProgram) :
//==============================================================================================
mProgCount()
{
	pInstrMem = new InstructionMem();	///Pointer to Instruction Memory
	pALU = new ALU();					///Create new instance of ALU
	pRegisters = new Registers();		///Create new instance of Registers
	pDataMem = new DataMemory();		///Create new instance of Data Memory
	pInstrMem->ReadFile(sProgram);		///Parse in Machine code prog
}

///Destructor: Delete/Clear pointers and vectors
//==============================================================================================
Processor::~Processor()
//==============================================================================================
{
	///Housekeeping
	delete pInstrMem, pALU, pRegisters, pDataMem;
	pInstrMem = NULL;
	pALU = NULL;
	pRegisters = NULL;
	pDataMem = NULL;
	mResult.clear();
	mResult.shrink_to_fit();
}

///Method: To grab the next instruction
//==============================================================================================
bitset<MIPS_32> Processor::NextInstr(bitset<MIPS_32> mProgCounter)
//==============================================================================================
{
	///Prog Counter is byte addressable and 32 bit wide
	mProgCounter = bitset<MIPS_32>(mProgCounter.to_ulong() + 1);
	return mProgCounter;
}

///Method: To initialise variables based on the Type of instruction 
//==============================================================================================
Type Processor::InstructionDecode(string sInstruction)
//==============================================================================================
{
	Type InsType(None);
	switch (mOpcode.to_ulong())		///All R-Type instructions have opcode = 0, All instructions 
	{
	case RTYPE:
		mSourceReg = bitset<DATA>(sInstruction.substr(0, DATA));
		sInstruction = sInstruction.substr(DATA);
		mSourceReg2 = bitset<DATA>(sInstruction.substr(0, DATA));
		sInstruction = sInstruction.substr(DATA);
		mDestinationReg = bitset<DATA>(sInstruction.substr(0, DATA));
		sInstruction = sInstruction.substr(DATA);
		mShiftReg = bitset<DATA>(sInstruction.substr(0, DATA));
		mFuncReg = bitset<OP>(sInstruction = sInstruction.substr(DATA));
		InsType = RType;
		break;

	case JTYPE2:
	case JTYPE3: ///All J-Type instructions have opcode = 2 or 3
		mTarget = bitset<TARGET>(sInstruction);
		InsType = JType;
		break;

	default:	///All I-Type instructions have opcode > 3
		mSourceReg = bitset<DATA>(sInstruction.substr(0, DATA));
		sInstruction = sInstruction.substr(DATA);
		mSourceReg2 = bitset<DATA>(sInstruction.substr(0, DATA));
		mConstant = bitset<CONST>(sInstruction.substr(DATA));
		InsType = IType;
		break;
	}
	return InsType;
}

///Method: Control unit, decides the datapath taken by each instruction
//==============================================================================================
void Processor::ControlUnit(Type Type)
//==============================================================================================
{
	bitset<MIPS_32> Res, bTemp;
	string sTemp;
	switch (Type)
	{
	case RType: ///Load value of rs and rt from Registers, perform and store ALU operation 
		pRegisters->ReadWrite(mSourceReg, mSourceReg2, 0, 0, false);		
		Res = pALU->ALUOp(mFuncReg, pRegisters->ReadData1, pRegisters->ReadData2);	
		pRegisters->ReadWrite(0, 0, mDestinationReg, Res, true);  ///Store result in register
		mProgCount = NextInstr(mProgCount); ///Fetch next instruction 
		break;

	case IType: ///Datapath is different for most instructions
		if (mOpcode.to_ulong() == ADDIU || mOpcode.to_ulong() == ADDI)
		{
			pRegisters->ReadWrite(mSourceReg, 0, 0, 0, false); ///Get value of Rs
			///Sign extend constant value
			sTemp = mConstant.test(CONST - 1) ? ("1111111111111111" + mConstant.to_string()) :
												("0000000000000000" + mConstant.to_string());
			bTemp = bitset<MIPS_32>(sTemp);
			bTemp = bTemp.test(CONST - 1) ? bTemp.flip() : bTemp;
			Res = pALU->ALUOp(mOpcode, pRegisters->ReadData1, bTemp); ///Store ALU result
			pRegisters->ReadWrite(0, 0, mSourceReg2, Res, true); ///Store value in Rt
			mProgCount = NextInstr(mProgCount); ///Get next instruction 
		}
		else if (mOpcode.to_ulong() == BEQ || mOpcode.to_ulong() == BNE)
		{
			pRegisters->ReadWrite(mSourceReg, mSourceReg2, 0, 0, false); ///Rs, Rt comparison
			Res = pALU->ALUOp(mOpcode, pRegisters->ReadData1, pRegisters->ReadData2); 
			if (Res == 1)
			{
				if (mConstant.test(CONST - 1))
				{
					mConstant = mConstant.flip(); ///Fetch instruction from address in Constant
					mProgCount = bitset<MIPS_32>(mProgCount.to_ulong() - mConstant.to_ulong());
				}
				else
				{
					mProgCount = bitset<MIPS_32>(mConstant.to_ulong() + mProgCount.to_ulong() + 1);
				}
			}
			else if (Res == 0) ///Grab the next instruction otherwise
				mProgCount = NextInstr(mProgCount);
		}
		else if (mOpcode.to_ulong() == SW)
		{
			pRegisters->ReadWrite(mSourceReg2, 0, 0, 0, false);
			sTemp = mConstant.test(CONST - 1) ? ("1111111111111111" + mConstant.to_string()) :
												("0000000000000000" + mConstant.to_string());
			bTemp = bitset<MIPS_32>(sTemp);
			bTemp = bTemp.test(15) ? bTemp.flip() : bTemp;
			Res = pALU->ALUOp(mOpcode, pRegisters->ReadData1, bTemp);
			pDataMem->MemoryAccess(Res, pRegisters->ReadData1, false, true); ///Store in Memory
			// cout << pRegisters->ReadData1.to_ulong() << endl;
			//pRegisters->PrintOutput(mSourceReg2.to_ulong());
			mResult.push_back(pRegisters->ReadData1.to_ulong()); ///Store result in vector
			mProgCount = NextInstr(mProgCount); ///Grab next instruction 
		}
		break;

	case JType: ///Jump to address specified by the Target address
		mProgCount = bitset<MIPS_32>(bitset<MIPS_32>(mTarget.to_string().substr(OP)).to_ulong());
		break;
	}
}

///Method: To output the result in a file, called at the end of InstructionProcess()
//==============================================================================================
void Processor::OutputResult()
//==============================================================================================
{
	vector<int>::iterator it;
	ofstream Output("Output.txt");				//Dump Register state after every instruction			
	Output << "The output of the Program is :" << endl;
	if (Output.is_open())
	{
		for (it = mResult.begin(); it != mResult.end(); ++it)
		{
			Output << *it << endl;
		}
	}
	else
		cout << "Unable to open file";
	Output.close();
}

///Method: Process instruction one per cycle through: Fetch, Decode, Execute, Writeback, Memory
//==============================================================================================
void Processor::InstructionProcess()
//==============================================================================================
{
	State State(Fetch);
	Type Type;
	bool bCompleted(false);
	while (!bCompleted)
	{
		switch (State)
		{
		case Fetch: ///Get next instruction, get opcode and pass to Decode state
			mInstruction = pInstrMem->GetInstruction(mProgCount); ///Retrieve instruction 
			mOpcode = pInstrMem->GetOpcode(mInstruction);	///Get opcode
			State = Decode;
			break;

		case Decode:
			if (mInstruction == NOP)	///End of program reached, nop
			{
				bCompleted = true;
				State = WriteBack;		
			}
			else ///Commence decoding
				Type = InstructionDecode(mInstruction.to_string().substr(OP));
			State = Execute;
			break;

		case Execute:
			if (Type != None)
				ControlUnit(Type); ///Let the Control Unit handle the instruction
			else
				cout << "No matching instruction type" << endl;
			State = Fetch;
			break;
		default:
			State = Fetch;
			break;
		}
	}
	State = WriteBack;
	switch (State)
	{
	case WriteBack:
		pRegisters->DumpRegister();	///Dumps Register contents to a file
		State = MemoryAccess;
		break;

	case MemoryAccess:
		pDataMem->OutputDataMem(); ///Dump Memory contents
		break;
	}
}

///==============================================================================================
///==============================================================================================
int main()
{
	Processor* pProcessor; ///Pointer to Processor
	string fileName; ///Store filename
	cout << "Please enter a file name: " << endl; ///Prompt for user input 
	cin >> fileName; 
	pProcessor = new Processor(fileName); ///Create new instance of Processor & parse filename
	//pProcessor = new Processor("Squares.txt");
	pProcessor->InstructionProcess(); ///Start Instruction Process
	pProcessor->OutputResult();	///Dump Result of Program to a file
	return 0;
}