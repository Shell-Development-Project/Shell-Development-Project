#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <boost/filesystem.hpp>			// -lboost_system: Write this while compiling, this prevents
										// the linker error.
#include <boost/algorithm/string/replace.hpp>
#include "lexical.h"
#include "processctrl.h"
using namespace std;
// https://stackoverflow.com/questions/8389033/implementation-of-multiple-pipes-in-c
#define STDIN 0
#define STDOUT 1

pid_t callFork()
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		throw -1;
	}
return pid;
}
int executeCommand(char **const ptrToArrayofStrings, int& flag)
{	
	if (flag != 1)
	{
		pid_t pid = callFork();
		if (pid == 0)	// child
		{	
			// cout << ptrToArrayofStrings[0] << ptrToArrayofStrings[1] << ptrToArrayofStrings[2] << ptrToArrayofStrings[3];
			execvp(ptrToArrayofStrings[0], ptrToArrayofStrings);
			exit(0);
		}
	}
	else
	{
		execvp(ptrToArrayofStrings[0], ptrToArrayofStrings);
		exit(0);
	}
	// Parent
	//wait for child
	wait(NULL);
return 0;
}
int piping(vector<string>& commandList4Pipe)
{	
	int vectorSize = commandList4Pipe.size();
	// // cout << "vectorSize" << vectorSize;
	int pipeFDSize = (vectorSize - 1) * 2;
	int pipes[pipeFDSize];
	pid_t forkArr[vectorSize];
	for (int i = 0; i < pipeFDSize; i += 2)
		pipe(pipes + i);
	for (int i = 0; i < vectorSize; i++)
	{
		if ((forkArr[i] = fork()) < 0)
		{
			perror("Pipes Fork error");
			throw -1;
		}
		if (forkArr[i] == 0)
		{	// child

			if (i != 0)	/* child gets input from the previous command, if it's not the first command */
            	if(dup2(pipes[((i - 1) * 2)], STDIN) < 0)
            		cout << "1st dup error";
            	
            if (i != vectorSize -1)	/* child outputs to next command, if it's not the last command */
            	if(dup2(pipes[(i * 2) + 1], STDOUT) < 0)
            		cout << "2nd dup error";

			for (int i = 0; i < pipeFDSize; i++)
				close(pipes[i]);
			std::vector <string> tokenstream;
			std::vector <char*> tokens;
			int pipeCount2, flag = 1;
			string cmd = commandList4Pipe.at(i);
			// cout << cmd << endl;
			cmdLexicalAnalysis(cmd, tokenstream, tokens, pipeCount2);
			// for(int i=0;i<tokenstream.size();i++)
			// 	cout << "tokenstream: "<< tokenstream[i];
			// cout << endl;
			// for(int i=0;i<tokens.size();i++)
			// 	cout << "tokens: "<< tokens[i];
			processctrl(cmd, tokens, pipeCount2, flag);
			exit(0);
		}	
	}
	// Parent
	for (int i = 0; i < pipeFDSize; i++)
		close(pipes[i]);
	for (int i = 0; i < (vectorSize - 1); i++)
		wait(NULL);
return 0;
} 

int processctrl(string cmd, vector <char*>& tokens, int& pipeCount, int& flag)
{	
	int pos = 0;
	char *ptrToCharPtr[1024];
	int index = 0;
	// cout << pipeCount;
	if (pipeCount)
	{	// cout << "in here";
		vector<string> pipeVector;
		while ((pos = cmd.find("|", index)) != -1)
		{
			string subString = cmd.substr(index, pos - index - 1);
			// cout << subString <<"hello";
			pipeVector.push_back(subString);
			index = pos + 2;
		}
		if (pos == -1)
			pos = cmd.length();
		// cout << cmd.substr(index, pos - index) << "hello";
		pipeVector.push_back(cmd.substr(index, pos - index));
		// for (int i = 0; i < pipeVector.size(); i++)
			// cout << pipeVector[i];
		piping(pipeVector);
	}
	else
	{	
		int vectorSize = tokens.size();
		int count = 0;
		for (int i = 0; i < vectorSize; i++)
		{		
			if (strcmp(tokens[i],"&&") == 0)	// || (flag = strcmp(tokens[i],"|")) == 0
			{	
				// cout << "In && or  |\n";
				ptrToCharPtr[count++] = NULL;
				// if (flag == 0)
				// {
				// 	commandList4Pipe.push_back(ptrToCharPtr);
				// 	cout << **ptrToCharPtr;
				// }
				
				executeCommand(ptrToCharPtr, flag);
				count = -1;
			}
			ptrToCharPtr[count++] = tokens[i];
		}
		ptrToCharPtr[count++] = NULL;
		executeCommand(ptrToCharPtr, flag);
	}
return 0;
}