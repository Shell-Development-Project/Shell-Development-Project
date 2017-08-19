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
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>
//User Defined #INCLUDES

#include "lexical.h"

using namespace std;

int main()
{	
	string cmd, pathtoHome, username, hostname;
	username = string(getenv("USER"));
	hostname = string(getenv("HOSTNAME"));
	pathtoHome = "/home/" + username;
	chdir (pathtoHome.c_str());
	while(cmd != "exit")
	{	
		cout << username
			 << "@"
			 << hostname 
			 << ":"
			 << boost::algorithm::replace_all_copy(boost::filesystem::current_path().string(), pathtoHome, "~") 
			 << "<!!> " 
			 << flush;
		getline(cin,cmd);
		cmdSyntaxAnalysis(cmd);
	}
	return 0;
}