/**/
/*
*	Austin Fouch
*	CMPS361 Software Design
*	Assembler Project
*	FileAccess.cpp:
*		Acesses the file for reading/parsing
*/
/**/

#include "stdafx.h"
#include "FileAccess.h"

/**/
/*
	FileAccess::FileAccess() FileAccess::FileAccess()
NAME

	FileAccess::FileAccess

SYNOPSIS

	FileAccess::FileAccess(int argc, char *argv[]);

		argc	--> number of arguments within the command line
		argv	-->	arguments stored in array

DESCRIPTION

	This function attempts to open the file passed via command line.
	If the file cannot be opened, program is exited.
*/
/**/
FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2) {
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}
	// Open the file.  One might question if this is the best place to open the file.
	// One might also question whether we need a file access class.
	m_sfile.open(argv[1], ios::in);

	// If the open failed, report the error and terminate.
	if (!m_sfile) {
		cerr << "Source file could not be opened, assembler terminated."
			<< endl;
		exit(1);
	}
}

/**/
/*
	FileAccess::~FileAccess() FileAccess::~FileAccess()

NAME

	FileAccess::~FileAccess

SYNOPSIS

	FileAccess::~FileAccess();

DESCRIPTION

	This function closes the file.
*/
/**/
FileAccess::~FileAccess()
{
	// Not that necessary in that the file will be closed when the program terminates.
	m_sfile.close();
}

/**/
/*
	FileAccess::GetNextLine() FileAccess::GetNextLine()

NAME

	FileAccess::GetNextLine

SYNOPSIS

	bool FileAccess::GetNextLine(string &a_buff);

		a_buff	--> line within the file

DESCRIPTION

	This function reads a line from the file. If EOF, nothing is read.

RETURNS

	Returns true if line successfully read.
	Returns false if EOF.
*/
/**/
bool FileAccess::GetNextLine(string &a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof()) {

		return false;
	}
	getline(m_sfile, a_buff);

	// Return indicating success.
	return true;
}

/**/
/*
	FileAccess::Rewind() FileAccess::Rewind()
NAME

	FileAccess::Rewind

SYNOPSIS

	void FileAccess::Rewind();

DESCRIPTION
	
	This function cleans file flags and goes back to the begining of the file.

RETURNS

	void
*/
/**/
void FileAccess::rewind()
{
	// Clean all file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}
