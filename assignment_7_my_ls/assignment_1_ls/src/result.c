#include "result.h"

extern uint8_t flag_long_list;
extern uint8_t flag_hiden;
extern uint8_t flag_reverse;

void print_result(result_t * result, int num_result, uint8_t * dir , int num_of_dirs)
{
	static uint32_t	function_counter = 0;
	function_counter++;
	
	if(num_of_dirs > 1)
	{
		printf("%s:\n",dir);	
	}
	else{     }
	if(flag_long_list == 1)
	{
		printf("total %d\n", total_blks(result, num_result)/2);
	}
	else{}
	
	if(flag_reverse == 0)
	{
		for(int i = 0 ; i < num_result; i++){
			if(flag_long_list == 1)
			{
				printf("%c%c%c%c%c%c%c%c%c%c %*d %*s %*s %*d %s %s %s:%s %s\n", 
				result[i].file_type,
				result[i].owner_r,
				result[i].owner_w,
				result[i].owner_x,
				
				result[i].group_r,
				result[i].group_w,
				result[i].group_x,
				
				result[i].others_r,
				result[i].others_w,
				result[i].others_x,
				
				get_max_length_in_column(result, LINKS_COLUMN_INDEX , num_result),
				result[i].numlink,
				
				get_max_length_in_column(result, OWNER_COLUMN_INDEX , num_result),
				result[i].owner_name,
				get_max_length_in_column(result, GROUP_COLUMN_INDEX , num_result),
				result[i].group_name,
				
				get_max_length_in_column(result, BYTES_COLUMN_INDEX , num_result),
				result[i].bytes_size,
				
				result[i].month,
				result[i].dayNmanth,
				
				result[i].hours,
				result[i].mins,
				
				result[i].dir_name);
			}
			else if(flag_long_list == 0)
			{
				printf("%*s ", 
				get_max_length_in_column(result, DIRNAME_COLUMN_INDEX , num_result),
				result[i].dir_name);
			}
			else{
			
			}
		}
	}
	else if(flag_reverse = 1)
	{
		for(int i = num_result-1 ; i >= 0; i--){
			if(flag_long_list == 1)
			{
				printf("%c%c%c%c%c%c%c%c%c%c %*d %*s %*s %*d %s %s %s:%s %s\n", 
				result[i].file_type,
				result[i].owner_r,
				result[i].owner_w,
				result[i].owner_x,
				
				result[i].group_r,
				result[i].group_w,
				result[i].group_x,
				
				result[i].others_r,
				result[i].others_w,
				result[i].others_x,
				
				get_max_length_in_column(result, LINKS_COLUMN_INDEX , num_result),
				result[i].numlink,
				
				get_max_length_in_column(result, OWNER_COLUMN_INDEX , num_result),
				result[i].owner_name,
				get_max_length_in_column(result, GROUP_COLUMN_INDEX , num_result),
				result[i].group_name,
				
				get_max_length_in_column(result, BYTES_COLUMN_INDEX , num_result),
				result[i].bytes_size,
				
				result[i].month,
				result[i].dayNmanth,
				
				result[i].hours,
				result[i].mins,
				
				result[i].dir_name);
			}
			else if(flag_long_list == 0)
			{
				printf("%*s ", 
				get_max_length_in_column(result, DIRNAME_COLUMN_INDEX , num_result),
				result[i].dir_name);
			}
			else
			{
			
			}
		}
	}
	else
	{
	
	}
	
	if(flag_long_list == 0 || (num_of_dirs > 1 && (function_counter < num_of_dirs)))
	{
		printf("\n");
	}
	else
	{
	
	}
}

uint32_t get_max_length_in_column(result_t * result_table , result_columns colomn_index , uint32_t rows)
{
	uint8_t max_length = 0;
	int tmp_len;
	switch(colomn_index)
	{
		case LINKS_COLUMN_INDEX:
			for(uint32_t i = 0 ; i < rows ; i++)
			{
				if(max_length < intlen(result_table[i].numlink))
				{
					max_length = result_table[i].numlink;
				}
			}
			break;
		case OWNER_COLUMN_INDEX:
			for(uint32_t i = 0 ; i < rows ; i++)
			{
				tmp_len = strlen(result_table[i].owner_name);
				if(max_length < tmp_len)
				{
					max_length = tmp_len;
				}
			}
		break;
		case GROUP_COLUMN_INDEX:
			for(uint32_t i = 0 ; i < rows ; i++)
			{
				tmp_len = strlen(result_table[i].group_name);
				if(max_length < tmp_len)
				{
					max_length = tmp_len;
				}
			}
		break;
		case BYTES_COLUMN_INDEX:
			for(uint32_t i = 0 ; i < rows ; i++)
			{
				tmp_len = intlen(result_table[i].bytes_size);
				if(max_length < tmp_len)
				{
					max_length = tmp_len;
				}
			}
		break;
		case DIRNAME_COLUMN_INDEX:
			for(uint32_t i = 0 ; i < rows ; i++)
			{
				tmp_len = strlen(result_table[i].dir_name);
				if(max_length < tmp_len)
				{
					max_length = tmp_len;
				}
			}
		break;
		default:
	}
	
	
	return max_length;	
}


uint32_t intlen(uint32_t integer)
{
	uint32_t length = 1;
	while((int)((integer / pow(10,length))) > 0)
	{
		length++;
	}
	return length;
}

uint32_t total_blks(result_t * table, uint32_t rows)
{
	uint32_t blks = 0;
	
	for(uint32_t i = 0 ; i < rows ; i++)
	{	
		blks += table[i].blks;
	}
	return blks;
}
