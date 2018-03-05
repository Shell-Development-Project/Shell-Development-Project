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
// #include "termcolor.hpp"
using namespace std;
/*
ANSI colour codes.
**Note that not all terminals support this; if colour sequences are not supported, garbage will show up.**

Example:

cout << "\033[1;31mbold red text\033[0m\n";
Here, \033 is the ESC character, ASCII 27. It is followed by [, then zero or more numbers separated by ;, 
and finally the letter m. The numbers describe the colour and format to switch to from that point onwards.

The codes for foreground and background colours are:
____________________________________

         foreground background

black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47
_____________________________________
Additionally, we can use these:
_________________________________________________________________

reset             0  (everything back to normal)
bold/bright       1  (often a brighter shade of the same colour)
underline         4
inverse           7  (swap foreground and background colours)
bold/bright off  21
underline off    24
inverse off      27
__________________________________________________________________

See the table on Wikipedia for other, less widely supported codes.
*/
#define ANSI_COLOR_RED     "\x1B[1;31m"
#define ANSI_COLOR_YELLOW  "\x1B[1;33m"
#define ANSI_COLOR_BLUE    "\x1B[1;34m"
#define ANSI_COLOR_RESET   "\x1B[1;0m"
#define ANSI_COLOR_WHITE   "\x1B[37m"
#define ANSI_COLOR_GREEN   "\x1B[1;32m"

int main()
{	
	string pathtoHome, username, hostname;
	username = string(getenv("USER"));		// If compiler is showing error: "basic_string::_M_construct null not valid"
											// that means Ubuntu isn't exporting the variable like it should,
										    // put "export HOSTNAME" in "/etc/bash.bashrc" and the code works.
	hostname = string(getenv("HOSTNAME"));  // it will export both the username and the hostname.
	pathtoHome = "/home/" + username;
	chdir (pathtoHome.c_str());
	static char* line_read = (char *) NULL;
	while(true)
	{	
	  	string prompt =  "\n"
						 +
						 username
	  					 // +
	  					 // ANSI_COLOR_RED
	  					 +
	  					 "@"
	  					 // +
	  					 // ANSI_COLOR_GREEN
	  					 + 
	  					 hostname
	  					 // +
	  					 // ANSI_COLOR_YELLOW
	  					 +
	  					 ":"
	  					 // + 
	  					 // ANSI_COLOR_BLUE
	  					 +
	  					 boost::algorithm::replace_all_copy(boost::filesystem::current_path().string(), pathtoHome, "~") 
	  					 // + 
	  					 // ANSI_COLOR_RESET
	  					 +
	  					 "!>> ";

		
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
			cout << e.what() << "\n";
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