#include "command_managment.h"

static int unset(char * var , char ** localv);

builtin_command command_handler(char * command , char ** argv , char ** localv)
{
	builtin_command ret = COMMAND_NONE;
	if(strcmp(command, "exit") == _OK)
	{
		ret = COMMAND_EXIT;
	}
	else if(strcmp(command, "export") == _OK)
	{
		ret = COMMAND_EXPORT;
	}
	else if(strcmp(command, "SET") == _OK)
	{
		ret = COMMAND_SET;
	}
	else if(strcmp(command, "unset") == _OK)
	{
	//	int command_unset(command , argv , localv);
		ret = COMMAND_UNSET;
	}
	else
	{
		ret = COMMAND_NONE;
	}
}
int command_export(char ** argv , char ** localv)
{
	int ret = FALSE;
	int arg_counter = 0;
	char * value;
	while(argv[arg_counter] != NULL)
	{
		if(is_var(argv[arg_counter]) == TRUE) // NEW Variable like -> export x=hallo
		{
			if(var_is_exist(get_var(argv[arg_counter]) , localv) == NULL)
			{
				setenv(get_var(argv[arg_counter]) , get_value(argv[arg_counter]) , 0);
			}
			else
			{
				if(is_local_var(localv , get_var(argv[arg_counter])) != NULL)
				{
					unset(argv[arg_counter] , localv);
					setenv(get_var(argv[arg_counter]) , get_value(argv[arg_counter]) , 0);
				}
				else	// is env
				{
					setenv(get_var(argv[arg_counter]) , get_value(argv[arg_counter]) , 1);
				}
			}
			ret = TRUE;
		}
		else	// x already existing and local -> export x
		{
			value = var_is_exist(argv[arg_counter] , localv);
			if(value != NULL)
			{
				if(is_local_var(localv , argv[arg_counter]) != NULL)
				{
					unset(argv[arg_counter] , localv);
					setenv(argv[arg_counter] , value , 0);
					ret = TRUE;
					
				}
				else	// is env
				{
					/* Nothing */
				}
			}
			else
			{
				/* Nothing */
			}
		}
		arg_counter++;
	}
	return ret;
}

int command_set(char ** localv)
{
	int ret = FALSE;
	int i = 0;
	if(localv[i] != NULL)
	{
		while(localv[i] != NULL){
			printf("%s\n",localv[i]);
			i++;
		}
		ret = TRUE;
	}
	return ret;
}


int command_unset(char ** argv , char ** localv)
{
	int ret = TRUE;
	int arg_counter = 1;
	
	while(argv[arg_counter] != NULL)
	{
		ret &= unset(argv[arg_counter] , localv);
		arg_counter++;
	}
	return ret;
}

static int unset(char * var , char ** localv)
{
	int ret = FALSE;
	if(is_local_var(localv , var) != NULL)
	{
		int counter = 0;
		char * temp = NULL;
		while(localv[counter] != NULL)
		{
			if(strcmp(var , get_var(localv[counter])) == _OK)
			{
				while(localv[counter+1] != NULL)
				{				
					localv[counter] = (char *)realloc(localv[counter] , strlen(localv[counter+1]));
					strcpy(localv[counter] , localv[counter+1]);
					counter++;				
				}
				free(localv[counter+1]);
				localv[counter] = NULL;
				break;
			}
			counter++;
		}
		ret = TRUE;
	}
	else if(is_environ_var(var) != NULL)
	{
		unsetenv(var);
	}
	else
	{
		ret = FALSE;	
	}
	return ret;
}
