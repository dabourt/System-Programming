/*
 * @Author: Tarek Dabour.
 * @Date: 11/10/2022
 * @Brief: To create builtin command in and use the variable APIs to simulate the export command , set command and unset command in bash.
 */
#ifndef COMMAND_MANAGMENT_H
#define COMMAND_MANAGMENT_H

#include <stdio.h>
#include <stdlib.h>
#include "../variable/variable.h"


#define TRUE 1
#define FULSE 0

typedef enum{
	COMMAND_NONE,
	COMMAND_EXIT,
	COMMAND_EXPORT,
	COMMAND_SET,
	COMMAND_UNSET
}builtin_command;

builtin_command command_handler(char * command , char ** argv , char ** localv);
/*
 * @brief: checking if the user enter 'exit'
 * @para: [void].
 * @return: FALSE if the user input anything without 'exit'.
 */
int command_exit(void);


/*
 * @brief: used for add new or local variable to environ, you can and any number of variable in one line -> export x y z=hallo 
 * @para: [argv] to extract variables , [localv] to search from variable in the local variables.
 * @return: TRUE or FALSE
 */
int command_export(char ** argv , char ** localv);

/*
 * @brief: to print all local variable in current process. 
 * @para: [localv] to print all the local variables.
 * @return: TRUE or FALSE if the localv point to NULL.
 */
int command_set(char ** localv);

/*
 * @brief: to remove any variables (local , environ), -> unset x y z. 
 * @para: [localv] to search from variable in the local variables.
 * @return: TRUE or FALSE if the variables not existing.
 */
int command_unset(char ** argv , char ** localv);

#endif
