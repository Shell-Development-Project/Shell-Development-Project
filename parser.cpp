#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <boost/filesystem.hpp>			// -lboost_system: Write this while compiling, this prevents
										// the linker error.
#include <boost/algorithm/string/replace.hpp>

#include "lexical.h"
#include "syntax.h"
#include "processctrl.h"

int cmdSyntaxAnalysis(string cmd)
{	
	std::vector <std::string> tokenStream;
	std::vector <char*> tokens;
	std::unordered_map <key, value> table;
	int flag = 0;
	
	cmdLexicalAnalysis(cmd, tokenStream, tokens);
	constructTable(table);
	if(! tokenStream.empty())
		tokenStream.push_back("<$>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<unix_command>");
	flag = parser(table, tokenStream);
	if (flag == 1)
	{	
		try
		{
			processctrl(cmd, tokens);
		}
		catch(int x)
		{
			std::cout << "Fork Error" << std::endl;
		}
	}
return 0;
}
