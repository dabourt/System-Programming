#include <stdio.h>
#include "command_handler.h"

int main(){
    char ch;
	unsigned char usr_command[100] = {'\0'};
	printf("Hallo in my shell >> \n Enter 'exit' if you want leave \n");
	while(1){
		printf("$enter anything in your mind >> ");
		gets(usr_command);
		clear_end_space(usr_command);
		if(check_command(usr_command , "exit") == _OK){
			printf("$Good Bye Bro.\n");
			break;
		}
		else if(check_command(usr_command , "fact") == _OK){
			command_fact();
		}
		else if(check_command(usr_command , "fib") == _OK){
			command_fib();
		}
		else if(check_command(usr_command , "rand") == _OK){
			command_rand();
		}
		else{
			printf(" You said : %s\n",usr_command);
		}
		
	}
	return 0;
}
