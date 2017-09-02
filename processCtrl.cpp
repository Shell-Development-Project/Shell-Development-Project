#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <boost/filesystem.hpp>			// -lboost_system: Write this while compiling, this prevents
										// the linker error.
#include <boost/algorithm/string/replace.hpp>
using namespace std;

int processctrl(string cmd, vector <char*>& tokens)
{	
	char *ptrToCharPtr[1024];
	int count = 0, vectorSize = tokens.size();
	
	for (int i = 0; i < vectorSize; i++)
		ptrToCharPtr[count++] = tokens[i];
	ptrToCharPtr[count++] = NULL;
	char **const ptrToArrayofStrings = ptrToCharPtr;

	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		throw -1;
	}
	if (pid == 0)	// child
	{
		execvp(ptrToArrayofStrings[0], ptrToArrayofStrings);
		exit(0);
	}
	
	// Parent
	//wait for child
	wait(NULL);
return 0;
}