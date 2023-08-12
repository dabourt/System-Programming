#include "variable.h"

extern char **environ;


unsigned int num_of_localv(char **localv)
{
	int num_of_lvars = 0;
	//printf("localv in %d\n",localv);
	while(localv[num_of_lvars] != NULL)
	{
		num_of_lvars++;
	}
	return num_of_lvars;
}

char** create_local_var(char **localv ,char * buf)
{
	char * var = var_is_exist(get_var(buf) , localv);
	if(var != NULL)	/* Meaning the variable is exist */
	{
		free(var);
		edit_exist_var(buf , localv);
	}
	else
	{
		unsigned int num_of_vars = num_of_localv(localv);
		if(localv == NULL ){
			localv = (char**)calloc(2,sizeof(char*));
			num_of_vars = 1;
		}
		else
		{
			num_of_vars++;
			localv = (char**)realloc(localv,sizeof(char*)*num_of_vars+1);
		}
		localv[num_of_vars-1] = (char*)calloc(strlen(buf),1);
		localv[num_of_vars] = NULL;
		
		strcpy(localv[num_of_vars-1] , buf);
	}
	return localv;
}


int is_var(char * buf)
{
	int ret = FALSE;
	int i = 0;
	
	space_handler(buf);
	
	if( is_en_char(buf[i]) || buf[i] == '_')	/* To limit the variable by begined by string only */
	{
		while(((buf[i] != '\0') && (buf[i] != ' ')) && (is_en_char(buf[i]) || is_num(buf[i]) || (buf[i] == '_') || buf[i] == '='))
		{
			if((buf[i] == '=') && (i != 0))
			{
				ret = TRUE;
				break;
			}
			else
			{
				/* contanue */
			}
			i++;
		}
	}
	return ret;
}


char* get_var(char * buf)
{
	char * var = NULL;
	if(is_var(buf))
	{
		int i = 0;
		while(buf[i] != '=')
		{
			i++;
		}
		var = (char *)malloc(i+1);
		strncpy(var,buf,i);
		var[i] = '\0';
	}
	else
	{
		var = NULL;
	}
	return var;
}

char* get_value(char * buf)
{
	char * value = NULL;
	if(is_var(buf))
	{
		int count = 0;
		while(buf[count] != '=')
		{
			count++;
		}
		count++;
		
		int value_count = 0;
		while(buf[count] != '\0'){
			count++;
			value_count++;
		}
		
		value = (char *)malloc(value_count+1);
		strncpy(value , buf+count-value_count , value_count+1);
		value[value_count] = '\0';
	}
	else
	{
		value = NULL;
	}
	return value;
}



void edit_exist_var(char * update ,char ** localv)
{
	char * temp_var = NULL;
	unsigned int counter = 0;
	if(localv[0] != NULL)
	{		/* must validate the localv pointer is point to any local vars */

		while(localv[counter] != NULL)
		{
			if(strcmp(get_var(localv[counter]) , get_var(update)) == _OK)
			{
				localv[counter] = (char *)realloc(localv[counter],strlen(update));
				strcpy(localv[counter] , update);
				break;
			}
			else
			{
				/* ret_value = NULL; */
			}
			counter++;
		}
	}
	else if(localv[counter] == NULL && environ != NULL) /* If the var is not exist in local list is exist in eniron list */
	{
		setenv(get_var(update) , get_value(update) , 1);
	}
	else /* The variable not exist */
	{  /* Nothing */  }
}



char * var_is_exist(char * var , char **localv)
{
	int counter = 0;
	char * temp = NULL;
	char * ret_value = NULL;
	if(localv != NULL)
	{
		while(localv[counter] != NULL)
		{
			temp = get_var(localv[counter]);
			if(strcmp(temp , var) == _OK)
			{
				ret_value = get_value(localv[counter]);
				break;
			}
			else
			{
				/* ret_value = NULL; */
			}
			counter++;
		}
	}
	if(ret_value == NULL)
	{
		counter = 0;
		while(environ[counter] != NULL)
		{
			temp = get_var(environ[counter]);
			if(strcmp(temp , var) == _OK)
			{
				ret_value = get_value(environ[counter]);
				break;
			}
			else
			{
				/* ret_value = NULL; */
			}
			counter++;
		}
	}
	//free(var);
	return ret_value;
}
int command_contain_var(char * buf)
{
	int ret = FALSE;
	if(buf == NULL)
	{
		printf("****Segmantation Fault*****\n");
	}
	else
	{
		int counter = 0;
		while(buf[counter] != '\0')
		{
			if(buf[counter] == '$')
			{	
				ret = TRUE;
				break;
			}
			counter++;
		}
	}
	return ret;
}

char * var_replacement(char * buf , char ** localv)
{
	int counter = 0;
	int var_counter = 0;
	char sec_one[300] = {'\0'};
	char sec_two[300] = {'\0'};
	char var[300] = {'\0'};
	char * var_;
	while(buf[counter] != '\0')
	{
		if(buf[counter] == '$')
		{	
			strncpy(sec_one , buf , counter);
			sec_one[counter] = '\0';
			
			var_counter = counter+1;
			while(buf[var_counter] != ' ' && buf[var_counter] != '\0')
			{
				var_counter++;
			}
			strncpy(var , buf+counter+1 , var_counter-counter-1);
			
			var[var_counter-counter-1] = '\0';
			
			if(buf[var_counter] != '\0')
			{
				strncpy(sec_two , buf+var_counter , strlen(buf+var_counter));
				sec_two[strlen(buf+var_counter)] = '\0';
			}
			else
			{
				sec_two[0] = '\0';
			}
			var_ = var_is_exist(var , localv);

			if(var_ != NULL)
			{
				var_ = strcat(strcat(sec_one,var_) , sec_two);
				strcpy(buf,var_);
				counter = -1;
			}
			else
			{
				printf("No variable with this name '%s'.\n",var);
			}
		}
		counter++;
	}
	return var_;
}



int is_num(char input)
{
	int ret = FALSE;
	if((input >= '0') && (input <= '9'))
	{
		ret = TRUE;
	}
	return ret;
}

int is_en_char(char input)
{
	int ret = FALSE;
	if(((input > 64) && (input < 91)) || ((input > 96) && (input < 123)))
	{
		ret = TRUE;
	}
	return ret;
}


/*
 *
 *
 * @return : NULL if the variable is not exist and the address of the value of the variable you passed for it. 
 */
char * is_local_var(char ** localv , char * var)
{
	int counter = 0;
	char * temp = NULL;
	char * ret_value = NULL;
	if(localv != NULL)
	{
		while(localv[counter] != NULL)
		{
			temp = get_var(localv[counter]);
			if(strcmp(temp , var) == _OK)
			{
				ret_value = get_value(localv[counter]);
				break;
			}
			else
			{
				/* ret_value = NULL; */
			}
			counter++;
		}
	}
	return ret_value;
}

char * is_environ_var(char * var)
{
	int counter = 0;
	char * temp = NULL;
	char * ret_value = NULL;
	if(ret_value == NULL)
	{
		counter = 0;
		while(environ[counter] != NULL)
		{
			temp = get_var(environ[counter]);
			if(strcmp(temp , var) == _OK)
			{
				ret_value = get_value(environ[counter]);
				break;
			}
			else
			{
				/* ret_value = NULL; */
			}
			counter++;
		}
	}
	return ret_value;
}


