#ifndef MBR_H
#define MBR_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>


typedef struct{
	uint8_t status;
	uint8_t first_CHS[3];
	uint8_t partition_type;
	uint8_t last_CHS[3];
	uint32_t LBA;
	uint32_t sector_count;
}PartitionEntry;

uint8_t is_MBR(uint8_t * buf);
uint8_t is_extended_MBR(PartitionEntry * table_entry);
uint8_t MPR_read_extended(PartitionEntry * table_entry ,int fd , char argv[]);
void MPR_print_partion_detals (PartitionEntry * table_entry_ptr , char argv[]);
void MPR_print_partition_row(PartitionEntry * table_entry_ptr , int i , char argv[]);
uint8_t is_protective_MBR(PartitionEntry * table_entry);

#endif
