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

		default:	return "<string>";
					break;
	}
}

void substrPos(string cmd, size_t &strStartPos, size_t &strEndPos)
{
	strStartPos = cmd.find(' ');
	strEndPos = cmd.find(' ', strStartPos + 1);
	string::iterator it = distance(cmd.begin(), cmd.find(' '));
	cout << "Distance= " << it;

	// if (strEndpos == -1)
	// {
	// 	strEndpos = cmd.end();
	// }
	// if (strStartpos == -1)
	// {
	// 	strStartpos = cmd.end();
	// }
}

int cmdLexicalAnalysis(string cmd)
{
	size_t strStartPos, strEndPos;
	string  tokenStream, nextToken;
	tokenStream.append("<command_name>");
	for (string::iterator it = cmd.begin(); it != cmd.end(); it++)
	{
		substrPos(cmd, strStartPos, strEndPos);
		cout << "strStartpos=" << strStartPos<< endl;
		cout << "strEndpos=" << strEndPos<< endl;
		// it = distance(cmd.begin(), strStartPos + 1);
		nextToken = lexems(cmd.substr(strStartPos + 1, strEndPos - strStartPos));
		cout << "Subtring: "<< cmd.substr(strStartPos + 1, strEndPos - strStartPos) << endl;
		tokenStream.append(nextToken);
		cout << "tokenStream=" << tokenStream << endl;
	}
	// for (int it = testCmd.begin(); it != testCmd.end(); it++)
	// {	
	// 	if(it == -1)
	// 		break;
	// 	pos = testCmd.find(' ');
	// 	it = pos + 1;
	// 	testCmd = testCmd.erase(0,pos + 1);
	// 	cout << "testCmd=" << testCmd << endl;
	// 	nextToken = lexems(testCmd);
	// 	tokenStream.append(nextToken);
	// }
	// cout << "tokenstream=" << tokenStream << endl;
	// cout << "testCmd=" << testCmd << endl;


}

int cmdSyntaxAnalysis(string cmd)
{	
	string tokenStream;
	tokenStream = cmdLexicalAnalysis(cmd);
}
