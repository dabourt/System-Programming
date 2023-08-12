#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define PATH_LEN 200

int main(int argc, char *argv[]){
	char dir_path[PATH_LEN] = {'\0'};
	char *ret;
	ret =  getcwd(dir_path , PATH_LEN);
	if(ret != NULL){
		printf("%s\n",dir_path);
	}
	return 0;
}
