#include "myls.h"

uint8_t flag_long_list = 0;
uint8_t flag_hiden = 0;
uint8_t flag_reverse = 0;

uint32_t main(uint32_t argc, char *argv[])
{	
	result_t * result = (result_t *)malloc(sizeof(result_t));
	
	opt_set_flags(argc, argv);
	
	int ret;
	if((ret = current_pwd_check(argc , argv)) == 0)
	{
		argv[argc] = (uint8_t *)malloc(2);
		strcpy(argv[argc] , ".");
	}
	else
	{	                        }
	
	uint32_t i_dirs = 1;
	int i_files = 0;
	
	/*Save Current Working Directory in cwd variable*/
	char cwd[100] ;
	getcwd(cwd, 100);
	
	while(argv[i_dirs] != NULL) 
	{
		if(strcmp(argv[i_dirs], "SHELL=/bin/bash") != 0)
		{
			if(argv[i_dirs][0] == '-')
			{
				/*Skip*/
			}
			else
			{
				struct stat stat_file;
				if(stat(argv[i_dirs], &stat_file) >= 0){

					union mode_file mode_file_st;
					mode_file_st.mode_value = stat_file.st_mode;
					
					if(mode_file_st.fileType == 0x04)	// means is dir
					{
						DIR *dirptr = opendir(argv[i_dirs]);
						if(dirptr != NULL)
						{
							//printf("here\n");
							chdir(argv[i_dirs]);
						
							struct dirent * entry;
							while ((entry = readdir(dirptr)) != NULL)
							{								
								if(flag_hiden == 0 && entry->d_name[0] == '.')
								{
									/* Skip */
								}
								else
								{
									if(stat(entry->d_name, &stat_file) >= 0)
									{
										mode_file_st.mode_value = stat_file.st_mode;
										struct passwd * usr_info = getpwuid(stat_file.st_uid);
										struct group * grp_info = getgrgid(stat_file.st_gid);
										ascTime * modifed_time = time_handler(stat_file.st_mtime);

										result[i_files].file_type = fileType_btoa(((uint16_t)mode_file_st.fileType));
										
										result[i_files].owner_x = (mode_file_st.owner_x == 1)? ((mode_file_st.suid == 0)? 'x' : 's')  : '-';
										result[i_files].owner_w = (mode_file_st.owner_w == 1)? 'w' : '-';
										result[i_files].owner_r = (mode_file_st.owner_r == 1)? 'r' : '-';
										
										result[i_files].group_x = (mode_file_st.group_x == 1)? ((mode_file_st.sgid == 0)? 'x' : 's') : '-';
										result[i_files].group_w = (mode_file_st.group_w == 1)? 'w' : '-';
										result[i_files].group_r = (mode_file_st.group_r == 1)? 'r' : '-';
										
										result[i_files].others_x = (mode_file_st.others_x == 1)? ((mode_file_st.sticky == 0)? 'x' : 't') : '-';
										result[i_files].others_w = (mode_file_st.others_w == 1)? 'w' : '-';
										result[i_files].others_r = (mode_file_st.others_r == 1)? 'r' : '-';
										
										result[i_files].numlink = stat_file.st_nlink;
										
										result[i_files].owner_name = (uint8_t *)malloc(strlen(usr_info->pw_name));
										strcpy(result[i_files].owner_name , usr_info->pw_name);
													
										result[i_files].group_name = (uint8_t *)malloc(strlen(grp_info->gr_name));
										strcpy(result[i_files].group_name , grp_info->gr_name);
										
										result[i_files].bytes_size = stat_file.st_size;

										strcpy(result[i_files].month , modifed_time->manth);
										strcpy(result[i_files].dayNmanth , modifed_time->dayNmanth);
										strcpy(result[i_files].hours , modifed_time->hours);
										strcpy(result[i_files].mins , modifed_time->mins);
										
										result[i_files].dir_name = (uint8_t *)malloc(strlen(entry->d_name));
										strcpy(result[i_files].dir_name , entry->d_name);
										
										result[i_files].blks = stat_file.st_blocks;       /* Default block size = 1024 */
										
										i_files++;
										result = (result_t *)realloc(result,sizeof(result_t)*(i_files+1));
									}
								}
							}
						}
					}
					else
					{
						struct dirent * entry;
						if(stat(argv[i_dirs], &stat_file) >= 0)
						{
							mode_file_st.mode_value = stat_file.st_mode;
							struct passwd * usr_info = getpwuid(stat_file.st_uid);
							struct group * grp_info = getgrgid(stat_file.st_gid);
							ascTime * modifed_time = time_handler(stat_file.st_mtime);

							result[i_files].file_type = fileType_btoa(((uint16_t)mode_file_st.fileType));
							
							result[i_files].owner_x = (mode_file_st.owner_x == 1)? ((mode_file_st.suid == 0)? 'x' : 's')  : '-';
							result[i_files].owner_w = (mode_file_st.owner_w == 1)? 'w' : '-';
							result[i_files].owner_r = (mode_file_st.owner_r == 1)? 'r' : '-';
							
							result[i_files].group_x = (mode_file_st.group_x == 1)? ((mode_file_st.sgid == 0)? 'x' : 's') : '-';
							result[i_files].group_w = (mode_file_st.group_w == 1)? 'w' : '-';
							result[i_files].group_r = (mode_file_st.group_r == 1)? 'r' : '-';
							
							result[i_files].others_x = (mode_file_st.others_x == 1)? ((mode_file_st.sticky == 0)? 'x' : 't') : '-';
							result[i_files].others_w = (mode_file_st.others_w == 1)? 'w' : '-';
							result[i_files].others_r = (mode_file_st.others_r == 1)? 'r' : '-';
							
							result[i_files].numlink = stat_file.st_nlink;
							
							result[i_files].owner_name = (uint8_t *)malloc(strlen(usr_info->pw_name));
							strcpy(result[i_files].owner_name , usr_info->pw_name);
										
							result[i_files].group_name = (uint8_t *)malloc(strlen(grp_info->gr_name));
							strcpy(result[i_files].group_name , grp_info->gr_name);
							
							result[i_files].bytes_size = stat_file.st_size;

							strcpy(result[i_files].month , modifed_time->manth);
							strcpy(result[i_files].dayNmanth , modifed_time->dayNmanth);
							strcpy(result[i_files].hours , modifed_time->hours);
							strcpy(result[i_files].mins , modifed_time->mins);
							
							result[i_files].dir_name = (uint8_t *)malloc(strlen(argv[i_dirs]));
							strcpy(result[i_files].dir_name , argv[i_dirs]);
							
							result[i_files].blks = stat_file.st_blocks;       /* Default block size = 1024 */
														
							i_files=1;
						}							
					}
				}
				else
				{
					printf("ls: '%s' not File or Directory.\n",argv[i_dirs]);
				}
			}
		}
		else
		{
			break;
		}
		if(i_files > 0)
		{
			print_result(result, i_files, argv[i_dirs] , ret);
		}
		else
		{             
		}
		
		chdir(cwd);	
		i_files = 0;
		i_dirs++;
	}
	return 0;
}

uint8_t fileType_btoa(uint16_t type)
{
	uint8_t ret;
	type = type<<12;
	switch (type){
		case 0140000:
			ret = 's';
			break;
		case S_IFLNK:
			ret = 'l';
			break;
		case S_IFREG:
			ret = '-';
			break;
		case S_IFBLK:
			ret = 'b';
			break;
		case S_IFDIR:
			ret = 'd';
			break;
		case S_IFCHR:
			ret = 'c';
			break;
		case S_IFIFO:
			ret = 'f';
			break;
		default:
			ret = '\0';
	}
	return ret;
}

ascTime * time_handler(const time_t time_val)
{
	ascTime * time_st = (ascTime *)ctime(&time_val);
	time_st->dayNweek[3] = '\0';
	time_st->manth[3] = '\0';
	time_st->dayNmanth[2] = '\0';
	time_st->hours[2] = '\0';
	time_st->mins[2] = '\0';
	time_st->secs[2] = '\0';
	time_st->year[4] = '\0';
	ascTime * ret_time_st = ((ascTime *)malloc(sizeof(time_st)));
	ret_time_st = time_st;
	return ret_time_st;
}

uint32_t current_pwd_check(int argc , char * argv[])
{
	uint32_t ret = 0;
	for(int i = 1 ; i < argc ; i++)
	{
		if(argv[i][0] != '-')
		{
			ret++;
		}
	}
	return ret;
}

void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}  
void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) 
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void opt_set_flags(int argc, char **argv)
{
	uint32_t opt;
	while ((opt = getopt(argc, argv, "lar")) != -1) {
		switch (opt) 
		{
		case 'l':
		   flag_long_list = 1;
		   break;
		case 'a':
		   flag_hiden = 1;
		   break;
		case 'r':
		   flag_reverse = 1;
		default: 
		   /* '?' */
		}
	}
}

