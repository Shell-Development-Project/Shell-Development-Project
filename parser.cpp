#include <iostream>
#include <vector>
#include <string>
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

int cmdSyntaxAnalysis(string cmd)
{	
	std::vector <std::string> tokenStream;
	std::unordered_map <key, value> table;
	
	cmdLexicalAnalysis(cmd, tokenStream);
	constructTable(table);
	tokenStream.push_back("<$>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<string>");
	// tokenStream.push_back("<unix_command>");
	parser(table, tokenStream);
return 0;
}
