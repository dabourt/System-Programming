#include <stdlib.h>
#include <time.h>


int get_random_num(void){
	srand(time(NULL));
	return rand();
}
