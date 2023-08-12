#ifndef __RESULT_H__
#define __RESULT_H__

/* Standerd libraries */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/* result_t: struct to  save all result to get the ls output */
typedef struct{
	uint8_t file_type;
	
	uint8_t owner_x;
	uint8_t owner_w;
	uint8_t owner_r;
	
	uint8_t group_x;
	uint8_t group_w;
	uint8_t group_r;
	
	uint8_t others_x;
	uint8_t others_w;
	uint8_t others_r;
	
	uint32_t numlink;
	
	uint8_t * owner_name;
	uint8_t * group_name;
	
	uint32_t bytes_size;
	
	uint8_t month[4];
	uint8_t dayNmanth[3];
	uint8_t hours[3];
	uint8_t mins[3];
	
	uint8_t * dir_name;
	
	uint32_t blks;
}result_t;

typedef enum{
	LINKS_COLUMN_INDEX,
	OWNER_COLUMN_INDEX,
	GROUP_COLUMN_INDEX,
	BYTES_COLUMN_INDEX,
	DIRNAME_COLUMN_INDEX
}result_columns;

void print_result(result_t * result, int num_result ,uint8_t * dir , int num_of_dirs);
uint32_t get_max_length_in_column(result_t * result_table , result_columns colomn_index , uint32_t rows);
uint32_t intlen(uint32_t integer);
uint32_t total_blks(result_t * table, uint32_t rows);

#endif
