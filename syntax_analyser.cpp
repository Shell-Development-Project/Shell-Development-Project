#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <boost/filesystem.hpp>			// -lboost_system: Write this while compiling, this prevents
										// the linker error.
#include <boost/algorithm/string/replace.hpp>

#include "syntax.h"

typedef std::pair <int, std::string> stackElement;
std::stack <stackElement> stack;

void constructTable(std::unordered_map <key, value>& table)
{	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SLR(1) TABLE CONSTRUCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	/* The table consists of 4 columns:

	1) Current Item: Indicates value at the top of the stack
	2) Next Symbol: Indicates the next token in the tokenStream
	3) Result: Indicates the state transition number for the canonical collection of LR(0) items represented by the DFA
	4) Action: Indicates the action to be performed- Shift, Reduce or Goto.
The above described table is an optimised version of the standard SLR(1) table and provides:
1) fast access of data items
	( With std::unordered_map, we can access data in O(1) time in the best case and O(n) in worst case )
2) less memory consumption
	(The standard table is a sparse table, but this table doesnot contain spaces, hence low memory utilization )

The following table is constructed making the canonical collection of LR(0) items and using the SLR(1) algorithm 
to traverse the Deterministic Finite Automaton.

The Shell Grammar used in this process is shown below:
___^^^^^^^^^^^^^^^____________________________________________________________________
	
	valid_string = unix_command PIPE unix_command || unix_command REDIRECTION
	filename || unix_command AMP || unix_command || special_command
	unix_command = command_name ARGS
	special_command = cd DIRECTORY || exit
	command_name = any valid executable/interpreted file name
	AMP = &
	ARG = string
	ARGS = ARG ARGS || ARG
	DIRECTORY = absolute_path || relative_path
	PIPE = |
	REDIRECTION = < || >
_______________________________________________________________________________________	
*/

	table[key(0,"<command_name>")] = value(8,'S');
	table[key(0,"<valid_string>")] = value(1,'G');
	table[key(0,"<unix_command>")] = value(2,'G');

	table[key(1,"<$>")] = value(1,'A');
	
	table[key(2,"<PIPE>")] = value(3,'S');
	table[key(2,"<REDIRECTION>")] = value(5,'S');
	table[key(2,"<AMP>")] = value(7,'S');
	table[key(2,"<$>")] = value(4,'R');
	
	table[key(3,"<command_name>")] = value(8,'S');
	table[key(3,"<unix_command>")] = value(4,'G');
	
	table[key(4,"<$>")] = value(1,'R');
	
	table[key(5,"<filename>")] = value(6,'S');
	
	table[key(6,"<$>")] = value(2,'R');
	
	table[key(7,"<$>")] = value(3,'R');
	
	table[key(8,"<string>")] = value(11,'S');
	table[key(8,"<ARG>")] = value(10,'G');
	table[key(8,"<ARGS>")] = value(9,'G');
	
	table[key(9,"<PIPE>")] = value(5,'R');
	table[key(9,"<REDIRECTION>")] = value(5,'R');
	table[key(9,"<AMP>")] = value(5,'R');
	table[key(9,"<$>")] = value(5,'R');
	
	table[key(10,"<string>")] = value(11,'S');
	table[key(10,"<PIPE>")] = value(7,'R');
	table[key(10,"<REDIRECTION>")] = value(7,'R');
	table[key(10,"<AMP>")] = value(7,'R');
	table[key(10,"<$>")] = value(7,'R');
	table[key(10,"<ARG>")] = value(10,'G');
	table[key(10,"<ARGS>")] = value(12,'G');
	
	table[key(11,"<PIPE>")] = value(8,'R');
	table[key(11,"<REDIRECTION>")] = value(8,'R');
	table[key(11,"<AMP>")] = value(8,'R');
	table[key(11,"<string>")] = value(8,'R');
	table[key(11,"<$>")] = value(8,'R');
	
	table[key(12,"<PIPE>")] = value(6,'R');
	table[key(12,"<REDIRECTION>")] = value(6,'R');
	table[key(12,"<AMP>")] = value(6,'R');
	table[key(12,"<$>")] = value(6,'R');

	table[key(0,"<special_command>")] = value(13,'G');
	table[key(0,"<cd>")] = value(14,'S');
	table[key(13,"<$>")] = value(9,'R');
	table[key(14,"<DIRECTORY>")] = value(15,'S');
	table[key(15,"<$>")] = value(10,'R');
	// auto ii = table.find(key(12,"<PIPE>"));
	// std::cout << ii->first.first
	// 		  << std::endl
	// 		  << ii->first.second
	// 		  << std::endl
	// 		  << ii->second.first
	// 		  << std::endl
	// 		  << ii->second.second
	// 		  << std::endl;
}

int reduceMove(int productionNo, std::unordered_map <key, value>& table)
{	
	int gotoState;
	switch(productionNo)
	{
		case 1:	for (int i = 0;i < 3; i++)
					stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<valid_string>"));
				break;
		case 2: for (int i = 0;i < 3; i++)
					stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<valid_string>"));
				break;
		case 3: for (int i = 0;i < 2; i++)
					stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<valid_string>"));
				break;
		case 4: stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<valid_string>"));
				break;
		case 5: for (int i = 0; i < 2; i++)
					stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<unix_command>"));
				break;
		case 6: for (int i = 0; i < 2; i++)
					stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<ARGS>"));
				break;
		case 7: stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<ARGS>"));
				break;
		case 8: stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<ARG>"));
				break;
		case 9: stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<valid_string>"));
				break;
		case 10: for (int i = 0; i < 2; i++)
					stack.pop();
				gotoState = stack.top().first;
				stack.push(stackElement(-1,"<special_command>"));
				break;
		default: throw productionNo;
	}
	auto ii = table.find(key(gotoState, stack.top().second));
	if (ii != table.end())
	{
		if (ii->second.second == 'G')
			stack.top().first = ii->second.first;
	}
return 0;
}

void parser(std::unordered_map <key, value>& table, std::vector <std::string>& tokenStream)
{	
	
	std::string nextSym;
	stack.push(stackElement(0,"<$>"));
	// std::cout << stack.top().first
	// 		  << stack.top().second;
	int tokenStreamLength = tokenStream.size();
	// std::cout << tokenStreamLength;
	try
	{
		for (int i = 0; i < tokenStreamLength; i++)
		{
			nextSym = tokenStream[i];
			// std::cout << "nextSym=" << nextSym <<std::endl;
			// nextSym = "<$>";
			auto ii = table.find(key(stack.top().first, nextSym));
			if (ii != table.end())
			{	
				// std::cout << "hello"<<std::endl;
				if (ii->second.second == 'S')
					stack.push(stackElement(ii->second.first, nextSym));;
				if (ii->second.second == 'A')
					std::cout << "ACCEPTED!!\n";
				if (ii->second.second == 'R')
				{
					reduceMove(ii->second.first, table);
					i--;	
				}
				// std::cout << "stack.top().first" << stack.top().first << std::endl;
				// std::cout << "stack.top().second"<< stack.top().second << std::endl;
			}
			else
			{
				throw nextSym;
			}
		}
	}
	catch (std::string e)
	{
		std::cout << "Syntax error: " << e << " unexpected" << std::endl;
	}
	catch (int e)
	{
		std::cout << "Syntax error: " << e << " the syntax used is not in accordance with the shell grammar." << std::endl;
	}
}