#include "command_handler.h"


unsigned char check_command(const unsigned char * usr_command ,const unsigned char * shell_command){
	return strcmp(usr_command, shell_command);
}

void clear_end_space(unsigned char *modi_str)
{
	while(modi_str[strlen(modi_str)-1] == ' ')
	{
		modi_str[strlen(modi_str)-1] = '\0';
	}
}

void command_fact (void){
	int num;
	printf("Enter a number: ");
	scanf("%d",&num);
	long long ret = get_factorial(num);
	if(ret > 0){
		printf("Resalt is: %llu\n",ret);
	}
	else{
		printf("Invalid\n");
	}
	getchar();
}

void command_fib  (void){
	int num;
	printf("Enter a number: ");
	scanf("%d",&num);
	printf("sequance is: ");
	print_fibonacci_seq(num);
	getchar();
}

void command_rand (void){
	printf("%d\n",get_random_num());
}
