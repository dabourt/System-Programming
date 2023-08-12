#include "gpt.h"


void GPT_read_print(int fd , uint8_t argv[])
{
	uint8_t i_entry = 0;
	uint8_t i_sectors = 0;
	uint8_t buf[512];
	uint8_t ret;
	GPTHeader * GPT_header_ptr;
	GPTPartitionEntry * GPT_entry_ptr;
	
	ret = read(fd , buf , 512);
		
	GPT_header_ptr = (GPTHeader *) buf;
	
	lseek(fd , (GPT_header_ptr->firstEntryLBA)*512 , SEEK_SET);
	
	for(i_sectors = 0 ; i_sectors < 32 ; i_sectors++)
	{
		ret = read(fd , buf , 512);
		
		GPT_entry_ptr = (GPTPartitionEntry *) buf;
		
		for(i_entry = 0 ; i_entry < 4 ; i_entry++)
		{
			if(GPT_entry_ptr[i_entry].partitionType1 != 0 && GPT_entry_ptr[i_entry].partitionType2 != 0)
			{
				printf("%-5s%-5d %-10c %-10lu %-10lu %-10lu %-7uG    %lu\n",
					argv,
					i_entry +  i_sectors + 1 , 
					' ',
					GPT_entry_ptr[i_entry].firstLBA,
					GPT_entry_ptr[i_entry].lastLBA,
					GPT_entry_ptr[i_entry].lastLBA - GPT_entry_ptr[i_entry].firstLBA + 1,
					(uint32_t)(((uint64_t) (GPT_entry_ptr[i_entry].lastLBA - GPT_entry_ptr[i_entry].firstLBA + 1) * 512) / (1024 * 1024 * 1024)),
					GPT_entry_ptr[i_entry].partitionType1
				);
			}
			else
			{
			}
		}
	}
}
