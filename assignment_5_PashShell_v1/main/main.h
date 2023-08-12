#ifndef MAIN_H
#define MAIN_H

/******************************************** Includes *********************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../parser/parser.h"
#include "../variable/variable.h"
#include "../builtin_commands/command_managment.h"

/*************************************** MACROS Definetion *****************************************/
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#endif
