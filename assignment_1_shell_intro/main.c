#include <stdio.h>
#include <string.h>

unsigned char check_exit(const unsigned char * str){
	unsigned char ret = 0;
	unsigned char * target_str = "exit";
	if(strlen(target_str) == strlen(str)){
		ret = 1;
		for(int i = 0; i < strlen(target_str); i++){
			if(target_str[i] != str[i]){
				ret = 0;
				break;	
			}
		}
	}
	return ret;
}

int main(){
	unsigned char str[100] = {'\0'};
	printf("Hallo in my shell >> \n Enter 'exit' if you want leave \n");
	while(1){
		printf("$enter anything in your mind >> ");
		gets(str);
		if(!check_exit(str)){

			printf(" You said : %s\n",str);
		}
		else{
			printf("$Good Bye Bro.\n");
			break;
		}
	}
	return 0;
}
