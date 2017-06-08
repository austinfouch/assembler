/*
* Austin Fouch
* CMPS361 Software Design
* Assembler Project
* Emulator.cpp:
*	Implements the emulator for the VC3600
*/

#include "stdafx.h"
#include "Emulator.h"

/**/
/*
	Emulator::InsertMemory() Emulator::InsertMemory()

NAME

	bool Emulator::InsertMemory - inserts information into VC3600 memory

SYNOPSIS

	bool Emulator::InsertMemory(int a_location, int a_contents);

		a_location	--> the location of where the contents will be stored
		a_contents	--> the contents to be stored

DESCRIPTION

	The function inserts data into the VC3600 memory.

RETURNS

	Returns true upon successful memory insertion,
	Returns false if the insertion failed
*/
/**/
bool Emulator::InsertMemory(int a_location, int a_contents) 
{
	if (a_location > MEMSZ) 
	{
		// location is not in memory
		return false;
	}
	m_memory[a_location] = a_contents;
	return true;
}

/**/
/*
	Emulator::RunProgram() Emulator::RunProgram()

NAME

	bool Emulator::RunProgram - runs the instructions stored in memory

SYNOPSIS

	bool Emulator::RunProgram()

DESCRIPTION
	
	The function exectues the instructions in memory.

RETURNS

	Returns true upon successful running.
	Returns false upon unsuccessful running.

*/
/**/
bool Emulator::RunProgram() {
	
	int currentLocation = 0;	// current loc in memory
	currentLocation = m_memory[currentLocation];
	while (currentLocation < MEMSZ) 
	{
		string contents = to_string(m_memory[currentLocation]);
		string opCode = "";
		string location = "";
		unsigned it = 0;

		// Get contents of the memory location :: Opcode | Location
		if (stoi(contents) > 99999) {

			//opcode is between 10 and 13
			for (; it < 2; ++it) opCode = opCode + contents[it];
			for (; it < contents.size(); ++it) location = location + contents[it];
		}
		else {
			for (; it < 1; ++it) opCode = opCode + contents[it];
			for (; it < contents.size(); ++it) location = location + contents[it];

		}

		int opCodeVal = stoi(opCode);
		int locationVal = stoi(location);

		// Switch statement determining what instruction was at the location and executing the command
		switch (opCodeVal) {
		case 0:
			m_acceumulator = m_acceumulator + m_memory[locationVal];
			break;
		case 1:
			m_acceumulator = m_acceumulator - m_memory[locationVal];
			break;
		case 2:
			m_acceumulator = m_acceumulator * m_memory[locationVal];
			break;
		case 3:
			if (m_memory[locationVal] == 0) 
			{
				cout << "ERROR:: DIVISION BY ZERO" << endl;
				exit(1);
			}
			else m_acceumulator = m_acceumulator / m_memory[locationVal];
			break;
		case 4:
			m_acceumulator = m_memory[locationVal];
			break;
		case 5:
			m_memory[locationVal] = m_acceumulator;
			break;
		case 6:
			Read(locationVal);
			break;
		case 7:
			cout << m_memory[locationVal] << endl;
			break;
		case 8:
			currentLocation = locationVal;
			continue;
		case 9:
			if (m_acceumulator < 0) 
			{
				currentLocation = locationVal;
				continue;
			}
			break;
		case 10:
			if (m_acceumulator == 0) 
			{
				currentLocation = locationVal;
				continue;
			}
			break;
		case 11:
			if (m_acceumulator > 0) 
			{
				currentLocation = locationVal;
				continue;
			}
			break;
		case 12:
			return true;
			break;
		default:
			cout << "OpCode does not exist" << endl;
			return false;
		}

		currentLocation++;
	}
	return false;
}

/**/
/*
Emulator::Read() Emulator::Read()

NAME
void Emulator::Read

SYNOPSIS
void Emulator::Read(int a_location);

a_location,	the integer value of the current location

DESCRIPTION
The function is responsible for error checking read input from
the user, and storing it in the accumulator.

RETURNS
((void))

*/
/**/
void Emulator::Read(int a_location) {
	string input;
	bool isAlpha = true;
	while (isAlpha) {
		cout << "? ";
		cin >> input;
		for (auto it = input.begin(); it != input.end(); ++it) {
			if (isdigit(*it)) {
				isAlpha = false;
				continue;
			}
			else if (*it == '-' && it == input.begin()) {
				continue;
			}
			else {
				isAlpha = true;
				cout << "Error :: Input is not integer." << endl;
				break;
			}
		}
	}
	int value = stoi(input);
	m_memory[a_location] = value;
}