/*
* Austin Fouch
* CMPS361 Software Design
* Assembler Project
* Errors.cpp:
*	Manages error recording and displaying through an error message vector.
*/

#include "Errors.h"
// must initilize here or linker error
vector<string> Errors::m_errorMsgs;
/**/
/*
	Errors::InitErrorReporting() Errors::InitErrorReporting()

NAME
	
	void Errors::InitErrorReporting

SYNOPSIS

	void Errors::InitErrorReporting()

DESCRIPTION

	This function clears the error message vector, essentially initializing
	error reporting for this current of the program.

RETURNS

	void

*/
/**/
void Errors::InitErrorReporting()
{
	m_errorMsgs.clear();
	return;
}

/**/
/*
	Errors::RecordError() Errors::RecordError()
	
NAME

	void Errors::RecordError

SYNOPSIS
	
	void Errors::RecordError(string &a_emsg)
		
		a_emsg	-->	takes the error message as a string.	

DESCRIPTION
	
	This function pushes an error message into the error message vector.

RETURNS
	
	void

*/
/**/
void Errors::RecordError(string &a_emsg)
{
	m_errorMsgs.push_back(a_emsg);
	return;
}

/**/
/*
	Errors::DisplayErrors() Errors::DisplayErrors()
NAME

	void Errors::DisplayErrors

SYNOPSIS

	void Errors::DisplayErrors()

DESCRIPTION

	This function displays contents of the error message vector, if any.

RETURNS

	void

*/
/**/
void Errors::DisplayErrors()
{
	if (m_errorMsgs.empty())
	{
		cout << "Translation successful." << endl;
	}
	else
	{
		cout << "Translation unsuccessful." << endl;
		cout << "Errors:" << endl;
		for (auto it : m_errorMsgs)
			cout << it << endl;
	}

	return;
}