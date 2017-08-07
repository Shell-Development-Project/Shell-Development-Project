#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "lexical.h"

string lexems(string testCmd)
{
	char nextSym = testCmd[0];
	// cout << nextSym;
	switch(nextSym)
	{
		case '|':	return "<PIPE>";
					break;

		case '<':	return "<REDIRECTION>";
					break;

		case '>':	return "<REDIRECTION>";
					break;

		case '&':	return "<AMP>";
					break;

		case '/':	return "<DIRECTORY>";
					break;

		case '"':	return "<usr_entered_string>";
					break;

		default:	return "<string>";
					break;
	}
}

int substrPos(string cmd, int it, int &strStartPos, int &strEndPos) 
{
	strStartPos = cmd.find(' ',it + 1);
	strEndPos = cmd.find(' ', strStartPos + 1);
	// cout << "strStartPos:" << strStartPos << endl;
	// cout << "strEndPos:" << strEndPos << endl;
	if (strStartPos == -1)								// If no further space is found, means that we have found all 
	{													// the tokens
		return -1;
	}
	if (strEndPos == -1 && strStartPos != -1)			// If space before the token is found, but not the space after
	{													// the token, this means that we are on the last token.
		strEndPos = cmd.length();						// In that case, make the variable- that takes the index value 
		return 0;										// space after a token- take the value of length of the string
	}													// i.e. 1 more than the index position of last character.
	return 0;
}
int cmdLexicalAnalysis(string cmd)
{
	int strStartPos, strEndPos, strLength, mark;		//strStartPos: Stores the index value of space before a token.
														// srtEndPos: Stores the index value of space after a token.
	string nextToken, tokenStream;						
	strLength = cmd.length();
	// cout << "Length:" << strLength << endl;
	tokenStream.append("<command_name>");
	for (int it = 0; it < strLength - 1; it++)
	{	
		// cout << "Iter:" << it << endl;
		mark = substrPos(cmd, it, strStartPos, strEndPos);	// Find the position of space characters 
															// before and after a token in the command
		// cout << "Mark:" << mark << endl;
		if (mark == -1)
			break;
		it = strStartPos;									// Move the iterator to the space preceding the next token 
		// cout << "Updated Iter:" << it << endl;
		nextToken = lexems(cmd.substr(strStartPos + 1, strEndPos - strStartPos - 1));	// Stores the string value of token type
		// cout << "nextToken:" << cmd.substr(strStartPos + 1, strEndPos - strStartPos - 1) << endl;
		if (nextToken == "<usr_entered_string>")
		{	
			it = cmd.find('"', it + 2);
			// cout << it;
			nextToken = "<string>";
		}
		tokenStream.append(nextToken);
		cout << "tokenStream" << tokenStream << endl;
	}
	return 0;
}

int cmdSyntaxAnalysis(string cmd)
{	
	string tokenStream;
	tokenStream = cmdLexicalAnalysis(cmd);
}
