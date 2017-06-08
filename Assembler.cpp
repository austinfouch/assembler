/**/
/*
*	Austin Fouch
*	CMPS361 Software Design
*	Assembler Project
*	Assembler.cpp:
*		Contains the implementation of the Assembler class and the Assembler.
*/
/**/

#include "Assembler.h"
#include "stdafx.h"
#include "Errors.h"

/**/
/*
	Assembler::Assembler() Assembler::Assembler

NAME

	Assembler::Assembler

SYNOPSIS

	Assembler::Assembler(int argc, char *argv[]);

		argc	--> number of arguments passed to the progam, which should 
					always be 2.
		argv	--> the array of arguments passed to the program, first should
					be the program name, second should be the file being 
					read from.

DESCRIPTION

	Opens file passed by command line arg for the FileAccess class.

RETURNS

	Void

*/
/**/
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
}

/**/
/*
	Assembler::PassI() Assembler::PassI()

NAME

	void Assembler::PassI

SYNOPSIS

	void Assembler::PassI();

DESCRIPTION

	This function:
		1. identifies instruction type in each line of the input
		2. copies the input file into the symbol table
		3. checks for errors
			
RETURNS
		
	Void

*/
/**/
void Assembler::PassI()
{
	Errors::InitErrorReporting(); // intializes error checking during parsing
	int loc = 0;

	// process each line of source code from a file
	for (; ; ) {

		// Read the next line from the source code file
		string buff;
		if (!m_facc.GetNextLine(buff)) 
		{
			// reached EOF without an end statment, reported in ParseII
			return;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseLine(buff);

		// reached end statement, go to ParseII
		if (st == Instruction::ST_End) return;

		// skip labels that are not machine or assembler language instructions
		if (st != Instruction::ST_MachineLanguage 
				&& st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}

		// insert label into symbol tabel and continue to next
		if (m_inst.isLabel()) 
		{ 
			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		loc = m_inst.LocationNextInstruction(loc);
	}
}

/**/
/*
	Assembler::PassII() void Assembler::PassII()

NAME

	void Assembler::PassII

SYNOPSIS

	void Assembler::PassII();

DESCRIPTION

	This function:
		1. Translates
		(2) Finding each error, and reporting them accordingly.

RETURNS
	
	Void

*/
/**/
void Assembler::PassII() {

	// Initialize the error reporting, clears out any unwanted information from Pass I
	Errors::InitErrorReporting();
	m_facc.rewind();

	// Parse in each line from the file :: re-examining, except this time around we have the filled Symbol Table.
	int loc = 0;
	int operandLoc = 0;

	cout << "Translation of Program : " << endl << endl;
	cout << "Location\tContents\tOriginal Instruction" << endl;
	for (; ; ) 
	{
		string buff;
		if (!m_facc.GetNextLine(buff)) 
		{
			// reached EOF without an end statment, record the error
			Errors::RecordError(string("Assembly language END statement missing"));
			return;
		}

		// Parse through the instructions, determining what to do based on Instruction type
		Instruction::InstructionType st = m_inst.ParseLine(buff);
		if (st == Instruction::ST_End) 
		{
			if (m_facc.GetNextLine(buff)) 
			{
				Errors::RecordError(string("Statement after assembly language END statement"));
				Errors::DisplayErrors();
			}
			return;
		}
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) {
			continue;
		}
		operandLoc = 0;

		// Read this next statement with caution :: checking for a alphanumeric operand that is within a symbol table.
		if (!m_inst.GetOperand().empty() && !m_symtab.LookupSymbol(m_inst.GetOperand(), operandLoc)) {

			// If it does not satisfy the above condition, then there is probably a garbage value in the symbol table.
			if (operandLoc == -999) {
				Errors::RecordError(string("multiply defined variable named - " + m_inst.GetOperand()));
				Errors::DisplayErrors();
			}
			else {
				Errors::RecordError(string("undefined variable named - " + m_inst.GetOperand()));
				m_symtab.AddSymbol(m_inst.GetOperand(), 99);
				Errors::DisplayErrors();
			}
		}
		loc = m_inst.LocationNextInstruction(loc);
	}
}

/**/
/*
	Assembler::RunEmulator() Assembler::RunEmulator()

NAME

	void Assembler::RunEmulator

SYNOPSIS
	
	void Assembler::RunEmulator()

DESCRIPTION

	This function runs the emulator for the VC3600 on the translated input file,
	and displays errors if any accumalte before or during emulation.

RETURNS
	
	Void

*/
/**/
void Assembler::RunEmulator() {
	
	if (Errors::isError()) 
	{
		Errors::DisplayErrors();
		return;
	}
	else 
	{
		// if no errors: insert instructions and data into VC3600 memory
		for (auto it : m_instructions)
		{
			// if memory insertion fails, report error and exit
			if (Assembler::m_emul.InsertMemory(it.location, it.contents)) 
				continue;
			else 
			{
				Errors::RecordError(string("VC3600 is out of memory."));
				Errors::DisplayErrors();
				exit(1);
			}
		}
	}

	// no insertion errors, run the emulator
	if (m_emul.RunProgram()) 
		cout << "Emulation successful." << endl;
	else
	{
		cout << "Emulation was unsuccessful." << endl;
		Errors::DisplayErrors();
	}

	return;
}
