gpt_src=./my_fdisk_src/gpt_handler/gpt.c
mbr_src=./my_fdisk_src/mbr_handler/mbr.c
my_fdisk_src=./my_fdisk_src/my_fdisk.c

myfdisk: $(my_fdisk_src) $(gpt_src) $(mbr_src)
	gcc $(my_fdisk_src) $(gpt_src) $(mbr_src) -o myfdisk 
