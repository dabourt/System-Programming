
#include <stdio.h>

void print_fibonacci_seq(unsigned int num){
	unsigned int i;
	unsigned long long prev = 0;
	unsigned long long current = 1;
	unsigned long long new = prev + current;
	
	printf("0 ");
	if(num > 0){
		printf(", 1 ");
		
		for(i = 1; i < num ; i++){
			printf(", %llu ",new);
			prev = current;
			current = new;
			new = prev + current;
		}
	}
	printf("\n");
}
