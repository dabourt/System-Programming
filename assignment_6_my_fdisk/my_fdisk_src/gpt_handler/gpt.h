#ifndef GPT_H
#define GPT_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

typedef struct{
	uint8_t signature[8];
	uint32_t revision;
	uint32_t headerSize;
	uint32_t headerCRC32;
	uint32_t reserved;
	uint64_t primaryLBA;
	uint64_t backupLBA;
	uint64_t firstUsableLBA;
	uint64_t lastUsableLBA;
	uint64_t uniqueGUID1;
	uint64_t uniqueGUID2;
	uint64_t firstEntryLBA;
	uint32_t numberOfEntries;
	uint32_t sizeOfEntry;
	uint32_t entriesCRC32;
}GPTHeader;

typedef struct{
	uint64_t partitionType1;
	uint64_t partitionType2;
	uint8_t uniquePartirionGUID[16];
	uint64_t firstLBA;
	uint64_t lastLBA;
	uint64_t flags;
	uint8_t partitionName[72];
}GPTPartitionEntry;


void GPT_read_print(int fd , uint8_t argv[]);


#endif
