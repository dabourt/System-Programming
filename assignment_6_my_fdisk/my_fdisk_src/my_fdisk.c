#include "my_fdisk.h"

int main(int argc, char **argv)
{
	uint8_t buf[512];
	int fd = open(argv[1] , O_RDONLY);
	int ret = read(fd , buf , 512);
	if(ret >= 0)
	{
		if(is_MBR(buf))
		{
			PartitionEntry * table_entry_ptr = (PartitionEntry *) &buf[446];
			printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
			"Device" , "Boot" , "Start", "End" , "Sectors" , "Size" , "Type");
			
			if(is_protective_MBR (table_entry_ptr))
			{
				GPT_read_print(fd , argv[1]);
			}
			else
			{
				MPR_print_partion_detals(table_entry_ptr , argv[1]);
			
				uint8_t ex_parti_num = is_extended_MBR(table_entry_ptr);
				
				if(ex_parti_num)
				{
					MPR_read_extended(table_entry_ptr+ex_parti_num , fd , argv[1]);
				}
			}
		}
		else
		{
			printf("'%s' is not MBR formated.\n",argv[1]);
		}
	}
	else
	{
		printf("'%s' not exist.\n",argv[1]);
	}	
	return 0;
}
