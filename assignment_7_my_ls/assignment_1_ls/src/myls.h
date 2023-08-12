#ifndef __MYLS_H__
#define __MYLS_H__

/* To use directory function */
#include <sys/types.h>
#include <dirent.h>

/* Standerd libraries */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/* To read file stat */ 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

/* To get user and group passwd and id usrid */
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "result.h"

/* mode_file to store and handle file permision and type */
union mode_file{
	struct{
		uint16_t others_x:1;
		uint16_t others_w:1;
		uint16_t others_r:1;
		
		uint16_t group_x:1;
		uint16_t group_w:1;
		uint16_t group_r:1;
		
		uint16_t owner_x:1;
		uint16_t owner_w:1;
		uint16_t owner_r:1;
		
		uint16_t sticky:1;
		uint16_t sgid:1;
		uint16_t suid:1;
		
		uint16_t fileType:4;
	};
	uint16_t mode_value;
};
/* ascTime: Struct can stored the time fields as string */
typedef struct{
	uint8_t dayNweek[4];
	uint8_t manth[4];
	uint8_t dayNmanth[3];
	uint8_t hours[3];
	uint8_t mins[3];
	uint8_t secs[3];
	uint8_t year[5];
}ascTime;

uint8_t fileType_btoa(uint16_t type);
ascTime * time_handler(const time_t time_val);
uint32_t current_pwd_check(int argc , char * argv[]);

void itoa(int n, char s[]);
void reverse(char s[]);
void opt_set_flags(int argc, char **argv);

#endif
