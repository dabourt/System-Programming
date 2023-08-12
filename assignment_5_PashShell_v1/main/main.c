#include "main.h"


int main ()
{				
 	char **argv = {NULL};
 	char **localv = (char**)malloc(sizeof(char*));
 	localv[0]=NULL;
 	char buf[500];
 	int ret = _OK;
  	while (1)
	{
	 	printf (GRN "dabour@ " MAG "femto shell " CYN ">> " RESET);
		fgets (buf, 100, stdin);
	 	buf[strlen (buf) - 1] = 0;
	  	if (buf[0] != 0)
		{	
		
			if(command_contain_var(buf) == TRUE)
			{
				if(var_replacement(buf , localv) == NULL)
				{
					ret = _NOT_OK;		/* Variable not exist */
				}
				else
				{
					ret = _OK;		/* Variable exist */
				}
			}
			else
			{  /* Continue */  
				ret = _OK;
			}
			
			if(ret == _OK)
			{
				free(argv);
				argv = parser(buf);
				
				if(strcmp(argv[0], "exit") == _OK)
				{
					return 0;
				}
				else if(strcmp(argv[0], "unset") == _OK)
				{
					command_unset(argv , localv);
				}
				else if(strcmp(argv[0], "set") == _OK)
				{
					command_set(localv);
				}
				else if(strcmp(argv[0], "export") == _OK)
				{
					command_export(argv , localv);
				}
				else if(is_var(buf))
				{
					localv = create_local_var(localv , buf);
				}
				else
				{
					int ret_pid = fork ();	
					if(ret_pid < 0)
					{
						printf("Faild in fork function\n");
					}	
					else if (ret_pid == 0)						/* Child Section Code. */ 
					{
						//printf("%d\n",strcmp(argv[0],argv[0]));
					  	int ret_state = execvp (argv[0], argv);
						return ret_state;
					
					}
			  		else if (ret_pid > 0)						/* Parant Section Code. */
					{
						int wstate;
						wait(&wstate);
						if (WEXITSTATUS(wstate) == 255)				/* Check about the child return state. */
						{
							printf ("\"%s\" not command in my_shell\n",buf);
						}
					}
				}
			}
		}
		else
		{
			/* contanue */
		}
	}
  	return 0;
}









