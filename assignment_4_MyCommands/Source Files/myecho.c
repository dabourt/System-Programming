#include <stdio.h>

int main(int argc , char * argv[]){
	int str_countr = 0;
	if(argc > 1){
		for(str_countr = 1; str_countr < argc; str_countr++){
			printf("%s ",argv[str_countr]);
		}
		printf("\n");
	}
	else{
		printf("You didn't enter anything\n");
	}
	return 0;
}
