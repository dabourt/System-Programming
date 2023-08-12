#include "mbr.h"

uint8_t is_MBR(uint8_t * buf)
{
	if(buf[510] == 0x55 && buf[511] == 0xAA)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t is_extended_MBR(PartitionEntry * table_entry)
{
	for (int i = 1 ; i <= 4 ; i++ )
	{
		if(table_entry[i].partition_type == 0x05)
		{
			return i;
		}
		else
		{
			
		}
	}
	return 0;
}

uint8_t MPR_read_extended(PartitionEntry * table_entry , int fd ,char argv[])
{
	uint8_t buf[512];
	int ret;
	int i = 4;
	PartitionEntry * table_entry_ptr;
	uint32_t LBA_base = table_entry->LBA;
	uint32_t LBA_offset = 0;
	lseek(fd , (table_entry->LBA)*512 , SEEK_SET);
	
	while (1)
	{

		ret = read(fd , buf , 512);
	
		table_entry_ptr = (PartitionEntry *) &buf[446];
		
		table_entry_ptr[0].LBA += LBA_base + LBA_offset;
		
		LBA_offset =  table_entry_ptr[1].LBA;
		
		MPR_print_partition_row(table_entry_ptr , i++ , argv);
		
		if(table_entry_ptr[1].partition_type != 0)
		{
			lseek(fd , (table_entry_ptr[1].LBA +  table_entry[0].LBA)*512 , SEEK_SET); 
		}
		else
		{
			break;
		}
	}
	return 1;
}

void MPR_print_partion_detals (PartitionEntry * table_entry_ptr , char argv[])
{	
	int i = 0;
	for (i = 0 ; i < 4 ; i++)
	{
		if(table_entry_ptr[i].partition_type != 0)
		{
			MPR_print_partition_row(&table_entry_ptr[i] , i , argv);
		}
		else
		{
			/* free */
		}
	}
}

void MPR_print_partition_row(PartitionEntry * table_entry_ptr , int i , char argv[])
{
	printf("%-5s%-5d %-10X %-10u %-10u %-10u %-7uG    %-10X\n",
		argv,
		i + 1 ,
		table_entry_ptr->status,
		table_entry_ptr->LBA,
		table_entry_ptr->LBA + table_entry_ptr->sector_count - 1,
		table_entry_ptr->sector_count,
		(uint32_t)(((uint64_t) table_entry_ptr->sector_count * 512) / (1024 * 1024 * 1024)),
		table_entry_ptr->partition_type
	);
}


uint8_t is_protective_MBR(PartitionEntry * table_entry)
{
	if(table_entry[0].partition_type == 0xEE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
