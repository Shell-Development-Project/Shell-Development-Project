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
#include <readline/readline.h>
#include <readline/history.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>
//User Defined #INCLUDES

#include "lexical.h"

using namespace std;

int main()
{	
	string pathtoHome, username, hostname;
	username = string(getenv("USER"));
	hostname = string(getenv("HOSTNAME"));
	pathtoHome = "/home/" + username;
	chdir (pathtoHome.c_str());
	static char* line_read = (char *) NULL;
	while(true)
	{	
		// cout << username
		// 	 << "@"
		// 	 << hostname 
		// 	 << ":"
		// 	 << boost::algorithm::replace_all_copy(boost::filesystem::current_path().string(), pathtoHome, "~") 
		// 	 << "!>> " 
		// 	 << flush;
		// getline(cin,cmd);
	  	/*Get a line from the user. */
	  	// if (line_read == EOF)
	  	// 	break;
	  	string prompt = "\n"
						 +
						 username
	  					 +
	  					 "@"
	  					 + 
	  					 hostname
	  					 +
	  					 ":"
	  					 + 
	  					 boost::algorithm::replace_all_copy(boost::filesystem::current_path().string(), pathtoHome, "~") 
	  					 + 
	  					 "!>>";

		
	  	line_read = readline (prompt.c_str());

	  	if (! line_read || strcmp(line_read,"exit") == 0)
	  	{
	  		cout << endl;
	  		break;
	  	}

	  	/* If the line has any text in it, save it on the history. */
	  	if (line_read && *line_read)
	   		add_history (line_read);
		try
		{	
			string cmd(line_read);
			cmdSyntaxAnalysis(cmd);
		}
		catch (const std::exception& e)
		{
			cout <<e.what() << "\n";
		}
	}
	return 0;
}


// /* A static variable for holding the line. */
// static char *line_read = (char *)NULL;

// /* Read a string, and return a pointer to it.  Returns NULL on EOF. */
// char *
// rl_gets ()
// {
//   /* If the buffer has already been allocated, return the memory
//      to the free pool. */
//   if (line_read)
//     {
//       free (line_read);
//       line_read = (char *)NULL;
//     }

//   /* Get a line from the user. */
//   line_read = readline ("");

//   /* If the line has any text in it, save it on the history. */
//   if (line_read && *line_read)
//     add_history (line_read);

//   return (line_read);
// }