# A simple Makefile to make the process of compilation easier for the user :-)
# With this makefile, instead of writing the cumbersome command for the whole project compilation into a single binary,
# simply write (on the terminal),~~

# make a : TO complile the project files
# make run: TO run the compiled binary files
# make clean: TO delete all the built binary files.

#~~~~~~~~~~~~~~~~~~VARIABLES~~~~~~~~~~~~~~~~~~~~~~~~~#
CC = g++ -std=c++11	
# -std=c++11 This flag provides C++11 support in the g++ compiler
CFLAGS = -c -Wall	
# argument Wall is used for giving warnings

#~~~~~~~~~~~~~~~~~COMMANDS~~~~~~~~~~~~~~~~~~~~~~~~~~~#
a: all
run: all
	./all
all: main.o parser.o lexical.o syntax_analyser.o
	$(CC) main.o parser.o lexical.o syntax_analyser.o -o all -lboost_system -lboost_filesystem
main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp
parser.o: parser.cpp
			$(CC) $(CFLAGS) parser.cpp
lexical.o: lexical.cpp
			$(CC) $(CFLAGS) lexical.cpp
syntax_analyser.o: syntax_analyser.cpp
			$(CC) $(CFLAGS) syntax_analyser.cpp
clean:
		rm -rf *o all