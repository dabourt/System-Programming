/*
 * @Author: Tarek Dabour.
 * @Date: 9/10/2022
 * @Brief: To create and use the variables local or environ and add alot of API can handling any variable using.
 */

#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parser/parser.h"

#define _OK 	0
#define _NOT_OK 1

#define TRUE  1
#define FALSE 0

/*
 * @brief: Calculate the total number of current local variable in the current process. 
 * @para: [localv] to count the local variables until reach the NULL.
 * @return: number of the local variable
 */
unsigned int num_of_localv(char **localv);

/*
 * @brief: Add new local variable in the current process.
 * @para: [localv] to search from variable in the local variables, [buf] hold the new variable.
 * @return: Double pointer of localv.
 */
char** create_local_var(char **localv,char * buf); //

/*
 * @brief: To validate the user input is valid variable syntax.
 * @para: [buf] hold the user inpput.
 * @ret : TRUE if the user input is valid variable and FALSE if not.
 */
int is_var(char * buf);

/*
 * @brief: To extract the var name from the variable.
 * @para: [buf] hold the variable.
 * @ret : Pointer to chars contain the var name or NULL pointer if the buf contain invalid variable syntax.
 */
char* get_var(char * buf);

/*
 * @brief: To extract the value name from the variable.
 * @para: [buf] hold the variable.
 * @ret : Pointer to chars contain the value name or NULL pointer if the buf contain invalid variable syntax.
 */
char* get_value(char * buf);


/*
 * @brief: edit the value for existing variable.
 * @para: [update] hold the value, [localv] to search from variable in the local variables.
 * @ret : [void].
 * @note: if the variable not exist in local or environ the variable don't do anything.
 */
void edit_exist_var(char * update ,char ** localv);


/*
 * @brief: to searching from the variable in local or environ and return the value of this variable if exist.
 * @para: [var] contain the var which you want to search from it, [localv] conntain the local variable.
 * @ret : Pointer to chars contain the var name or NULL pointer if the buf contain invalid variable syntax.
 */
char * var_is_exist(char * var , char **localv);


/*
 * @brief: Chech the user input the variable name in his command or not.
 * @para: [buf] contain the variable name.
 * @ret : True if the buf contain the '$' before variable name like ($var) or FALSE if contain any special charcters or 
          begaining by number.
 */
int command_contain_var(char * buf);

/*
 * @brief: If the user input word precursor by '$' this mean replace the characters after $ is variable and this function 
 	   can replace the variable and '$' by his value if the variable is existing.
 * @para: [buf] contain the user input ,[localv] is contain the local variables.
 * @ret : Pointer to chars the contain the new strings after replace the variable by his value or NULL if the sring not
 	  contain the variable name or the variable is not existing.
 */
char* var_replacement(char * buf , char ** localv);


/*
 * @brief: To check if the input charcter is implement as the number from 0 to 9 or not.
 * @para: [input] contain char.
 * @ret : TRUE if the number or FALSE if not.
 */
int is_num(char input);

/*
 * @brief: To check if the input charcter is implement as the english charcter upper or lowe case or not.
 * @para: [input] contain char.
 * @ret : TRUE if the english charcter or FALSE if not.
 */
int is_en_char(char input);


/*
 * @brief: searching about variable name in the local variables.
 * @para: [var] contain the var which you want to search from it, [localv] conntain the local variable.
 * @ret : Pointer to chars contain the value of his variable name or NULL if the variable not exist.
 */
char * is_local_var(char ** localv , char * var);


/*
 * @brief: searching about variable name in the environ variables.
 * @para: [var] contain the var which you want to search from it.
 * @ret : Pointer to chars contain the value of his variable name or NULL if the variable not exist.
 */
char * is_environ_var(char * var);


#endif /* VARIABLE_H */
