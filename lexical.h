#ifndef LEXICAL_H_INCLUDED
#define LEXICAL_H_INCLUDED

#include <iostream>
using namespace std;

string lexems(string testCmd);
int cmdLexicalAnalysis(string cmd);
int cmdSyntaxAnalysis(string cmd);
void substrPos(string cmd,size_t &strStartPos, size_t &strEndpos);

#endif // LEXICAL_H_INCLUDED