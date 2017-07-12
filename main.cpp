#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int cmdLexicalAnalysis(string cmd)
{
	size_t pos;
	string testCmd, tokenStream;
	testCmd = cmd;
	pos = testCmd.find(' ');
	// cout << "pos=" << pos << endl;
	testCmd = testCmd.erase(0,pos + 1);
	// cout << "testcmd=" << testCmd << endl;
	tokenStream.append("<unix_command>");
	// cout << "tokenstream=" << tokenStream << endl;
}

int cmdSyntaxAnalysis(string cmd)
{	
	string tokenStream;
	tokenStream = cmdLexicalAnalysis(cmd);
}

int main()
{	
	string cmd;
	while(cmd != "exit")
	{	
		cout << "$>> " << flush;
		getline(cin,cmd);
		cmdSyntaxAnalysis(cmd);
	}
	return 0;
}