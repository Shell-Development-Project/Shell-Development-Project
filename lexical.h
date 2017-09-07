#ifndef LEXICAL_H_INCLUDED
#define LEXICAL_H_INCLUDED

#include <iostream>
using namespace std;

string lexems(string testCmd);
int cmdLexicalAnalysis(string cmd, std::vector <std::string> &tokenStream, std::vector <char*> &tokens, int& pipeCount);
int cmdSyntaxAnalysis(string cmd);
int substrPos(string cmd, int it, int &strStartPos, int &strEndpos);
int validateDir(string dir);
int validateCmd(string cmd);

#endif // LEXICAL_H_INCLUDED