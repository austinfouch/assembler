/**/
/*
*	Austin Fouch
*	CMPS361 Software Design
*	Assembler Project
*	Instruction.h:
*		Parses and provides information about instructions 
*/
/**/

#include "Instruction.h"

/**/
/*
	Instruction::ParseLine() Instruction::ParseLine()

NAME

	Instruction::InstructionType Instruction::ParseLine

SYNOPSIS

	Instruction::InstructionType Instruction::ParseLine(string &a_buff);

		a_buff	-->	current line being parsed

DESCRIPTION

	This function parses a line and determines what instruction type is
	being used on the line.

RETURNS

	Returns a variable of InstructionType, which is the instruction type 
	of line being parsed
*/
/**/
Instruction::InstructionType Instruction::ParseLine(string &a_buff) 
{	
	clear();
	// Return as comment/blank line as nothing
	if (a_buff.empty()) 
	{
		return m_type;
	}
	
	// not a comment/blank line
	m_instruction = a_buff;
	string currentLine = m_instruction;	
	removeComments(currentLine);		
	istringstream strSegment(currentLine);	// splits up the line by spaces
	vector <string> lineData;				// will store 3 strings at a time

	// push back line data while not at the end of the line
	while (strSegment >> currentLine) 
	{
		// skip pushing empty strings into vector
		if (!lineData.empty())
		{
			lineData.push_back(currentLine);
		}
	}

	// if the parsed line is empty, return it as a comment/blank
	if (lineData.empty())
	{
		return m_type;
	}

	// if the parsed line has more than 3 strings records an error
	if (lineData.size() > 3) 
	{
		Errors::RecordError(
			string("Too many arguements in line, expects LABEL OPCODE OPERAND.")
		);
	}

	// parses data in lineData vector and checks validity of each piece of data
	ParseInstruction(currentLine, lineData);

	// if line is assembly or machine, return instruction type
	if (m_LineHasInstr)
	{
		return m_type;
	}
	// line wasn't read as assembly or machine language
	else
	{
		syntaxError();
	}
	return m_type;
}

/**/
/*
	Instruction::ParseInstruction() Instruction::ParseInstruction()

NAME

	void Instruction::ParseInstruction

SYNOPSIS

	void Instruction::ParseInstruction(string &a_currentInstr, 
			vector<string> &a_lineData);

		a_currentInstr	-->	current line being parsed
		a_lineData		--> current line data

DESCRIPTION

	This function parses a line and determines what instruction type is
	being used on the line.

RETURNS

	void
*/
/**/
void Instruction::ParseInstruction(string &a_currentInstr, 
		vector<string> &a_lineData)
{
	bool lineIsAssembly = false, lineIsMachine = false;
	for (unsigned column = 1; column <= a_lineData.size(); column++)
	{
		a_currentInstr = a_lineData.at(column - 1);

		// set all strings in lineData to uppercase characters
		transform(a_currentInstr.begin(), a_currentInstr.end(),
			a_currentInstr.begin(), toupper);
		if (column == 1 && a_lineData.size() == 3)
		{
			m_Label = a_lineData.at(column - 1);
			continue;
		}
		if (lineIsMachine)
		{
			m_Operand = a_lineData.at(column - 1);
			continue;
		}
		else if (lineIsAssembly)
		{
			m_Operand = a_lineData.at(column - 1);
			m_OperandValue = stoi(a_lineData.at(column - 1));
			continue;
		}

		// if either bool is true 
		if (lineIsMachine = InstrIsMachine(a_currentInstr))
		{
			m_LineHasInstr = true;
			continue;
		}
		else if (lineIsAssembly = InstrIsAssembly(a_currentInstr))
		{
			m_LineHasInstr = true;
			continue;
		}
	}
}

int Instruction::LocationNextInstruction(int a_loc) 
{
	// if instruction type is assembly and operand isnt empty
	if (m_type == ST_AssemblerInstr && !m_Operand.empty()) 
	{
		// if the current OpCode is ORG, return its value if
		if (m_AssemblyInstructions.at(m_OpCode) == AT_ORG) 
		{
			// follow the ORG instr
			if (m_IsNumericOperand) 
				return m_OperandValue;
		}
		// since not ORG, next instr found after line increment
		else if (m_AssemblyInstructions.at(m_OpCode) == AT_DS) 
		{
			if (m_IsNumericOperand) 
				return a_loc + m_OperandValue;
		}
	}

	return a_loc + 1;
}

void Instruction::syntaxError()
{
	Errors::RecordError(
		string("No machine or assembly language instruction found in line")
	);
	m_OpCode = "?";
	m_Operand = "?";
}

void Instruction::clear()
{
	m_Label = "";
	m_OpCode = "";
	m_Operand = "";
	m_instruction = "";
	m_NumOpCode = -1;
	m_OperandValue = -1;
	m_IsNumericOperand = false;
	m_LineHasInstr = false;
	m_type = ST_Comment;
}

bool Instruction::InstrIsMachine(const string &a_currentInstr) 
{
	// search valid machine instructions for the current instruction
	auto it = m_MachineInstructions.find(a_currentInstr);

	// if currentInstr found in list, set member data accordingly
	if (it != m_MachineInstructions.end()) 
	{
		m_OpCode = it->first;
		m_NumOpCode = it->second;
		m_type = ST_MachineLanguage;
		return true;
	}
	else 
		return false;
}

bool Instruction::InstrIsAssembly(const string &a_currentInstr)
{
	// search valid assembler instructions for the current instruction
	auto it = m_AssemblyInstructions.find(a_currentInstr);

	// if currentInstr found in list, set member data accordingly
	if (it != m_AssemblyInstructions.end())
	{
		m_OpCode = it->first;
		m_NumOpCode = it->second;
		m_type = ST_AssemblerInstr;
		return true;
	}
	else
		return false;
}

void Instruction::removeComments(string &a_line) {

	// find where the comment will start and split 
	auto commentSplit = a_line.find(";");
	if (commentSplit != string::npos) {
		// comment present, parse it out
		a_line = a_line.substr(0, commentSplit);
		return;
	}
	return;
}