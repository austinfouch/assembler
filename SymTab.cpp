//
//		Implementation of the symbol table class.
//

#include "SymTab.h"
#include "stdafx.h"
/**/
/*
	SymbolTable::AddSymbol() SymbolTable::AddSymbol()

NAME

	void SymbolTable::AddSymbol

SYNOPSIS

	void AddSymbol( char *a_symbol, int a_loc );

		a_symbol	-->	symbol, which is an operand or label, parsed from the 
						line, key in the symbol table map.
		a_loc		-->	location of instruction, value in the symbol table map.

DESCRIPTION

	This function will place the symbol "a_symbol" and its location "a_loc"
	in the symbol table.

RETURN

	void
*/
/**/
void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) 
	{
		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
	return;
}

/**/
/*
	SymbolTable::DisplaySymbolTable() SymbolTable::DisplaySymbolTable()

NAME

	void SymbolTable::DisplaySymbolTable

SYNOPSIS

	void SymbolTable::DisplaySymbolTable();

DESCRIPTION

	This function displays the symbol table.

RETURNS

	void
*/
/**/
void SymbolTable::DisplaySymbolTable() 
{
	int symbolIndex = 0;
	printf("Symbol # \tSymbol\tLocation\n");
	for (auto it : m_symbolTable) 
	{
		cout << symbolIndex << "\t\t " << it.first << "\t " << it.second << endl;
		symbolIndex++;
	}
	cout << "________________________________________________________" << endl;
	return;
}

/**/
/*
	SymbolTable::LookupSymbol() SymbolTable::LookupSymbol()

NAME

	bool SymbolTable::LookupSymbol

SYNOPSIS

	bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)

		a_symbol	-->	represents the string key for the symbol
		a_loc		-->	location of the instruction

DESCRIPTION

	This function is responsible for telling us whether the symbol
	was previously defined in the symbol table or not.

RETURNS

	boolean value, true when the symbol was found, false otherwise.
	Returns value of the location within a_loc if it exists.
	Returns undefined symbol in a_loc otherwise
*/
/**/
bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc) 
{
	
	auto it = m_symbolTable.find(a_symbol);
	if (it != m_symbolTable.end()) 
	{
		a_loc = it->second;
		return true;
	}
	else 
	{
		return false;
	}
}