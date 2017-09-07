#ifndef PROCESSCTRL_H_INCLUDED
#define PROCESSCTRL_H_INCLUDED

#include <iostream>

pid_t callFork();
int executeCommand(char **const ptrToArrayofStrings);
int pipeFunction(char **const ptrToArrayofStrings, int pipes[], int pipeCount, int& keepsTrackofPIPEpos);
int processctrl(std::string cmd, std::vector <char*>& tokens, int& pipeCount, int& flag);

#endif // PROCESSCTRL_H_INCLUDED

// #ifndef PROCESSCTRL_H_INCLUDED
// #define PROCESSCTRL_H_INCLUDED

// #include <iostream>

// int processctrl(std::string cmd, std::vector <char*>& tokens);

// #endif // PROCESSCTRL_H_INCLUDED