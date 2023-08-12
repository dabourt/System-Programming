#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char * argv[]){
	char buf[2] = {'\0','\0'};
	int read_count;
	int src_fd;
	int dest_fd;

	if((src_fd = open(argv[1], O_RDONLY)) >= 0 )
	{
		dest_fd = open(argv[2], O_CREAT | O_WRONLY, 0644);
		while((read_count = read(src_fd , buf , 1)) > 0)
		{	

			write(dest_fd, buf , 1);
		}

		close(src_fd);
		close(dest_fd);
		remove(argv[1]);
	}
	else if(argv[1] == NULL)
	{
		printf("No argumant pass : Syntax ==>  mv [source] [destination]\n");
	}
	else
	{
		printf("move : cannot stat '%s': No such file or directory\n", argv[1] );
	}
	return 0;
}
