/**/
/*
*	Austin Fouch
*	CMPS361 Software Design
*	Assembler Project
*	Assembler.h:
*		Contains definitions for the Assembler class
*/
/**/

#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"
#include "Errors.h"
#include "stdafx.h"

class Assembler {

public:
	Assembler( int argc, char *argv[] );

	// Pass I - establish the locations of the symbols
	void PassI( );

	// Pass II - generate a translation
	void PassII( );

	// Display the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }
	
	// Run emulator on the translation.
	void RunEmulator();

private:

	struct Instructions
	{
		int location;
		int contents;
	};

	FileAccess m_facc;	    // File Access object
	SymbolTable m_symtab;	// Symbol table object
	Instruction m_inst;	    // Instruction object
	Emulator m_emul;        // Emulator object
	vector<Instructions> m_instructions;
};

