/**/
/*
*	Austin Fouch
*	CMPS361 Software Design
*	Assembler Project
*	Instruction.h:
*		Parses and provides information about instructions
*/
/**/

#pragma once

#include "stdafx.h"
#include "Errors.h"

// The elements of an instruction.
class Instruction {

public:

	// initalize instruction by setting all members to empty or invalid
	Instruction() :
		m_Label(""),				// "" empties the string members
		m_OpCode(""),
		m_Operand(""),
		m_instruction(""),
		m_NumOpCode(-1),			// -1 invalidates the int members
		m_OperandValue(-1),
		m_IsNumericOperand(false),
		m_LineHasInstr(false),
		m_type(ST_Comment)			// current type is blank
	{};

	// Codes to indicate the type of instruction being processed
	enum InstructionType 
	{
		ST_MachineLanguage,	// 0 - A machine language instruction.
		ST_AssemblerInstr,	// 1 - Assembler Language instruction.
		ST_Comment,         // 2 - Comment or blank line
		ST_End				// 3 - end instruction.
	};

	// Codes to indicate the type of symbolic operand being processed
	enum MachineOperandCode 
	{
		MT_ADD,		// 0 
		MT_SUB,		// 1
		MT_MULT,	// 2
		MT_DIV,		// 3
		MT_LOAD,	// 4
		MT_STORE,	// 5
		MT_READ,	// 6
		MT_WRITE,	// 7
		MT_B,		// 8
		MT_BM,		// 9
		MT_BZ,		// 10
		MT_BP,		// 11
		MT_HALT		// 12
	};

	// Codes to indicate the type of assembly instruction being processed
	enum AssemblyOperandCode
	{
		AT_ORG,	// 0 - define const. Constant is a decimal int in op field
		AT_DC,	// 1 - def storage. Op specifies # of words of storage
		AT_DS,	// 2 - def origin. Op spcifies adrs of translation for next inst
		AT_END	// 3 - indicates there are no more statments to translate
	};

	// clears member data, basically calling the cstor again
	void clear();

	// Parse the line for data, push data into a vector
	InstructionType ParseLine(string &a_buff);

	// Parse the vector data and set member variable
	void ParseInstruction(string &a_currLine, vector<string>& a_lineData);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// To access the label
	inline string &GetLabel() { return m_Label; }

	// To determine if a label is blank.
	inline bool isLabel() { return !m_Label.empty(); }

	// To access number operand code
	inline int &GetNumOpCode() { return m_NumOpCode; }

	// To access operand code
	inline string &GetOpCode() { return m_OpCode; }

	// To access operand
	inline string &GetOperand() { return m_OpCode; }

	// To access operand value
	inline int &GetOperandValue() { return m_OperandValue; }

	// To see if operand is numeric operand
	inline bool IsNumericOperand() { return m_IsNumericOperand; }

	// To see if line has a valid instruction
	inline bool IsLineValid() { return m_LineHasInstr; }

	// See if passed string is found in respective instruction list,
	// if it is, set member data accordingly
	bool InstrIsMachine(const string &a_currentInstr);
	bool InstrIsAssembly(const string &a_currentInstr);


	// Removes comments from the current line
	void removeComments(string &a_line);

	// Current instruction is not machine or assembly, records error
	void syntaxError();
private:
	// The elemements of a instruction
	string m_Label;		// The label.
	string m_OpCode;	// The symbolic op code.
	string m_Operand;	// The operand.


	string m_instruction;	// The original instruction.
	int m_NumOpCode;		// The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// true if the operand is numeric.
	bool m_LineHasInstr;	// true if the line has machine or assembly instr
	int m_OperandValue;		// The value of the operand if it is numeric.

	// Contains valid operands in the machine language
	const map <string, MachineOperandCode> m_MachineInstructions =
	{ 
		{ "ADD", MT_ADD },
		{ "SUB", MT_SUB },
		{ "MULT", MT_MULT },
		{ "DIV", MT_DIV },
		{ "LOAD", MT_LOAD },
		{ "STORE", MT_STORE },
		{ "READ", MT_READ },
		{ "WRITE", MT_WRITE },
		{ "B", MT_B },
		{ "BM", MT_BM },
		{ "BZ", MT_BZ },
		{ "BP", MT_BP },
		{ "HALT", MT_HALT }
	};

	// Contains valid operands in the assembly language
	const map <string, AssemblyOperandCode> m_AssemblyInstructions = 
	{ 
		{ "ORG", AT_ORG },
		{ "DC", AT_DC },
		{ "DS", AT_DS },
		{ "END", AT_END }
	};

};
