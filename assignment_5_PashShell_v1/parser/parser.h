#ifndef PARSER_H
#define PARSER_H

/******************************************** Includes *********************************************/
#include <stdlib.h>
#include <string.h>
/************************************* Functions Declarations **************************************/

/*
 * @brief: Parser remove all addition spaces in the user input and seperat the input into words and 
 	   save the result in argv. 
 * @para: [buf] contain the command from the user.
 * @return: variables in double pointer.
 */
char **parser(char * buf);

/*
 * @brief: Remove all spaces from the input. 
 * @para: [buf] contain the command from the user.
 * @return: void and the result saved in buf again.
 */
void space_handler(char * buf);

#endif
