![image](https://user-images.githubusercontent.com/29279664/32775331-1fe0b5e2-c955-11e7-8d1b-2c8ec03d724c.png)
# Abstract
    Most useful interaction with a UNIX system occurs through the shell. Using a series of easy to remember and 
    simple commands, one can navigate the UNIX file system and issue commands to perform a wide variety of tasks. 
    Even though it may appear simple, the shell encapsulates many significant components of the operating system. 
# Introduction
    This project aims to create a command line interface that provides almost every functionality provided by the
    BASH and look forward to implementing minute tweaks and quick fixes that can influence its performance in terms
    of memory utilization, execution time and error handling. Moreover, the implementation methods make use of new 
    styles and libraries.
    This includes implementation of concepts of Compiler Design (lexical analysis, syntax analysis, error handling)
    amalgamated with the concepts of process creation and control in Unix Systems. 
    The project aims to make the shell more memory-efficient by making use of C++ Boost:: Filesystem Library that 
    enables Directory Traversal and implementation of Change Directory command (cd) in the Unix Environment. Also, 
    a new method of constructing SLR (1) parsing table has been improvised, this reduces the wastage of memory 
    caused using conventional Sparse Matrix Method.
    Hence, the newly developed shell has been named BISHOP (Boost Implemented OPerational SHell).

<h1> Implementation Details</h1>

# Environment:
    The shell maintains many variables which allow the user to maintain settings and easily navigate the filesystem.
    Two of these that are particularly important are the current working directory and the PATH. As its name implies,
    the current working directory variable keeps track of the user's current directory. The kernel searches in the
    directories specified by the PATH variable starting with the leftmost directory first.    
    Bishop’s environment uses Boost filesystem Library to check the user’s pwd (Present Working Directory) and 
    execute cd (change Directory) command effectively. Also, the program code makes use of C’s readline library 
    for text completion functionalities originally provided in the BASH.

# Command Analysis:
    Bishop parses the user input command by performing SLR (1) syntax analysis. The LR (k)-method uses two tables,
    which describe the behavior of a push-down automaton, used during the parsing process. These two tables, 
    called action table and goto table, are sparse tables. Moreover, the data in them are not homogeneous in 
    structure since both item numbers and right sides of productions are stored.
    I referred a paper which proposes: a new parsing table structure, which is dense and homogeneous; a parsing
    algorithm; and an algorithm for generation of this table, based on the SLR (1)-method.

![image](https://user-images.githubusercontent.com/29279664/30530025-b3a76f54-9c60-11e7-8004-eb885140cced.png)

The proposed parsing table structure has 4 attributes:
-	CurrentItem - the LR (0)-Item on the top the of stack
-	NextSymbol - the next symbol from the input queue
-	Result - an integer whose meaning depends on the value of the attribute Action
-	Action - if action is ‘S’, then Result contains the number of a LR(0)-Item; if action is ‘R’, then Result contains the number of a production; if action is ‘A’, then the input queue is recognized as true.

# Pipelining:
    UNIX provides a variety of useful programs for use (grep, ls, echo, to name a few).
    Like instructions in C++, these programs tend to be quite effective at doing one specific thing 
    (Such as grep: searching text, ls: printing directories, and echo: printing text to the console).
    However, programmers/OS users would like to accomplish large tasks consisting of many individual 
    operations. Doing such requires using results from previous steps in order to complete a larger 
    problem. Bishop supports this through the pipe operation (represented by the character |) just 
    like the BASH using Unix System calls (dup2(int oldfd, int newfd)). 
    A pipe in between two commands causes the standard output of one to be redirected into the standard
    input of another. An example of this is provided below, using the pipe operation to search for all 
    processes with the name under root user:
                                          ps auxx | grep “root” 
# Process Control:
    Bishop uses the conventional methods of process creation and execution in Unix/Linux (fork () and execvp ()
    system calls) aided by different implementation techniques like C++ STL (Standard Template Library) classes:
    std::string and std::vector.
- fork ():
Every other process in the system is brought to life through a call to the fork () system call. A process calling fork is copied by the kernel. At this point, the process that called fork is known as the parent, and the newly created process is known as the child since the parent process caused the child to be created. The newly created process is essentially exactly the same as the parent, even having the exact same variables and open _les. Fork is unique in that it is called once by the parent process and returns twice (to the parent and child separately).
To the parent, fork returns the process id (PID) of the newly created child. To the child, fork returns 0. If the call fails entirely, -1 is returned to the parent, and no child is created.

For more information about fork, see its manpage by calling man 2 fork.

- exec ():
UNIX provides a function, known as exec, which allows programmer to change a process's address space in order to run an entirely new program. Running an exec command deletes the existing text, data, and stack segments of the existing process and replaces them with those of a new program.
The system call interface provides a total of six different variations of the exec function which differ only on how they handle input arguments. This means that only one system call (usually execve ()) is actually required to be implemented. The other functions are stubs which perform necessary preparations and then eventually call execve.

Bishop uses execvp (const char *file, char *const argv[]) system call as it maintains a vector of command input strings.

# References:
-	Linux Lectures by Dr. B Frazer
https://www.youtube.com/watch?v=9seb8hddeK4&index=2&t=7s&list=LLDUlQqsRbRzlDdJlyERjLBw
-	Pipes Lectures
https://www.youtube.com/watch?v=uHH7nHkgZ4w
-	Machine Problem 4: The UNIX Shell, PDF- Texas A&M University
-	Stevens, W. Richard. Advanced Programming in the UNIX Environment
-	Linux System Programming: Talking Directly to the Kernel and C Library, Author: Robert Love
-	Parsing table structure and algorithm for the LR(k) parsing Method
    BY: ILTSCHEV, V[elko] I[vanov]
    [New LR Parsing method.pdf](https://github.com/Akashi96/High-Performance-Linked-Lists/files/1309805/New.LR.Parsing.method.pdf)
# Necessary Installations:
- C++ Boost Library:
  <h6>sudo apt-get install libboost-all-dev</h6>
- C Readline Library:
  <h6>sudo apt-get install libreadline6 libreadline6-dev</h6>
  



