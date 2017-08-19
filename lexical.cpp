#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <boost/filesystem.hpp>			// -lboost_system: Write this while compiling, this prevents
										// the linker error.
#include <boost/algorithm/string/replace.hpp>

#include "lexical.h"

int validateCmd(string cmd)
{
	if (cmd == "cd")
	{
		return 1;
	}
	boost::filesystem::path pathToBin("/bin/" + cmd);
	cout << "path=" << pathToBin << "\n";
	if (boost::filesystem::exists(pathToBin))
	{
		cout << "valid command";
	}
	else
		cout << "invalid command";
	return 0;
}

int validateDir(string dir)
{
	// replace(dir.begin(), dir.end(), '~', "/home/akash");	//Cannot use std::replace() because, it replaces char with another char
															//here we have to replace character with string
	boost::filesystem::path path(dir);
	// cout << "current path:" << boost::filesystem::current_path() <<endl; // Shows the current working directory
	string username, pathToHome;
	// getlogin_r (username, LOGIN_NAME_MAX);	// we did not use getlogin_r because it is a C function
												// and requires username to be of type: (char*)
	username = string(getenv("USER"));	// getenv() is a C++ func. and gets the value of environment variable mentioned in
										// the argument. Since the return type is char*, we convert it to type string
	pathToHome = "/home/" + username;	// make a path to home directory so as to replace it with ~ sign.
	// cout << pathToHome;

	string path2 = boost::algorithm::replace_all_copy(path.string(),"~",pathToHome); 	// Since ~(home directory) is
																						// not a valid argument for chdir()

	// cout << "changed path=" << path2 << "\n";
	if (boost::filesystem::exists(path2))
	{
		// cout << "exists";
		chdir (path2.c_str());		//chdir() is defined in <unistd.h>
		// cout << "changed current path:" << boost::filesystem::current_path() <<endl;
	}
	else
		cout << "cd: "<< dir << ": No such file or directory";
}

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

		case '"':	return "<usr_entered_string>";
					break;

		default:	return "<string>";
					break;
	}
}

int substrPos(string cmd, int it, int &strStartPos, int &strEndPos)
{
	if (it == -1)											// if iterator is at the beginning of the command string
	{
		strStartPos = -1;
		strEndPos = cmd.find(' ', it + 1);
	}
	else
	{
		strStartPos = cmd.find(' ', it);
		strEndPos = cmd.find(' ', strStartPos + 1);
		// cout << "strStartPos:" << strStartPos << endl;
		// cout << "strEndPos:" << strEndPos << endl;
		if (strStartPos == -1)								// If no further space is found, means that we have found all
		{													// the tokens
			return -1;
		}
		if (strEndPos == -1 && strStartPos != -1)			// If space before the token is found, but not the space after
		{													// the token, this means that we are on the last token.
			strEndPos = cmd.length();						// In that case, make the variable- that takes the index value
															// space after a token- take the value of length of the string
															// i.e. 1 more than the index position of last character.

			if (strEndPos - strStartPos == 1)				// if we've reached the end of the string and the last character
				return -1;									// entered by the user is blank: ' '.

			return 0;
		}
	}
	return 0;
}
int cmdLexicalAnalysis(string cmd, string &tokenStream)
{
	int strStartPos, strEndPos, strLength, mark, commandTurn = 1, dirArg = 0;//strStartPos: Stores the index value of space before a token.
														// srtEndPos: Stores the index value of space after a token.
	string token, subString;
	strLength = cmd.length();
	// cout << "Length:" << strLength << endl;
	// tokenStream.append("<command_name>");
	for (int it = -1; it < strLength - 1; it++)
	{
		// cout << "Iter:" << it << endl;
		mark = substrPos(cmd, it, strStartPos, strEndPos);	// Find the position of space characters
															// before and after a token in the command
		// cout << "Mark:" << mark << endl;
		if (mark == -1)
			break;
		it = strStartPos;									// Move the iterator to the space preceding the next token
		// cout << "Updated Iter:" << it << endl;
		subString = cmd.substr(strStartPos + 1, strEndPos - strStartPos - 1);
		token = lexems(subString);	// Stores the string value of token type
		// cout << "token:" << cmd.substr(strStartPos + 1, strEndPos - strStartPos - 1) << endl;

		if (token == "<usr_entered_string>")
		{
			it = cmd.find('"', it + 2) - 1;
			// cout << it;
			token = "<string>";
		}
		if (dirArg == 1)
		{
			token = "<DIRECTORY>";
			while (cmd[strEndPos - 1] == '\\')		// when the file or directory name consists of spaces.
			{
				subString.erase(strEndPos - strStartPos - 2);	// erase backslash(\) character from path string.
                                                                    // bool::filesystem::exists() does not require the use of
															// backslash(\) to check the existence of file or directory
															// it is the feature of the shell.
				it ++;				// move the iterator by one space to help finding the next two spaces in the string using substrPos()
				substrPos(cmd, it, strStartPos, strEndPos);
				subString = subString + " " + cmd.substr(strStartPos + 1, strEndPos - strStartPos - 1);
																	// Take the next substring and add it to the
																	// previous substring to treat them as
																	// one space separated directory path.
				it = strStartPos;		// reset the position of the iterator, so that at the very end when, blackslash(\)
										// is not found, we DO NOT repeat the substring already taken in consideration
										// and unwillingly add it to the tokenstream as a <string>
			}
			validateDir(subString);
			dirArg = 0;
		}
		if (commandTurn == 1)
		{
			token = "<command_name>";					// This converts the token type of string at the beginning of the
														// command or just after the PIPE operator to <command_name>
			commandTurn = 0;							// commandTurn helps to ensure whether or not, the next token
														// needs to be of type <command_name> or not.
			/* Now, since we know that the token has to be a unix command, we need to validate it.
			The subString variable already contains the token value, just send it to validateCmd() to check the
			validity of the <command_name>*/
			dirArg = validateCmd(subString);
			if (dirArg == 1)
				token = "<cd>";
		}
		if (token == "<PIPE>")
			commandTurn++;

		tokenStream.append(token);
		cout << "tokenStream" << tokenStream << endl;
	}
	return 0;
}
