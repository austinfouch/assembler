/*
* Austin Fouch
* CMPS361 Software Design
* Assembler Project
* Errors.h:
*	Manages error recording and displaying through an error message vector.
*/

#ifndef _ERRORS_H
#define _ERRORS_H

#include "stdafx.h"

class Errors {

public:

	// Initializes error reports.
	static void InitErrorReporting();

	// Records an error message.
	static void RecordError(string &a_emsg);

	// Displays the collected error message.
	static void DisplayErrors();

	// checks error vector
	static inline bool isError() { return !m_errorMsgs.empty(); }

private:
	// static to allow them to be accessed anywhere
	static vector<string> m_errorMsgs;
};
#endif