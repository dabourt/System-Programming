#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string.h>
#include <mymath.h>

#define _OK 	0
#define _NOT_OK 1

unsigned char check_command(const unsigned char * usr_command ,const unsigned char * shell_command);

void clear_end_space(unsigned char *modi_str);

void command_fact (void);
void command_fib  (void);
void command_rand (void);

#endif
