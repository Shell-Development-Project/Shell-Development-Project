/*input
 
*/
///-------------------------------------------------------------------------------------
/*
	AUTHOR:		Akash Agarwal
				1405231007-Computer Science Department
				IET LUCKNOW
	LIFE MOTTO:	while(!(suceed=try()))
*/
///--------------------------------------------------------------------------------------

//Predefined #INCLUDES 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

//User Defined #INCLUDES
#include "lexical.h"

using namespace std;

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