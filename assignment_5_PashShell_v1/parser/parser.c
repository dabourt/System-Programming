#include "parser.h"


void space_handler(char * buf)
{
	/*Remove End spaces */
	while(buf[strlen(buf)-1] == ' ')
	{
		buf[strlen(buf)-1] = '\0';
	}

	/*Remove bagin spaces */
	int i = 0;
	while(buf[0] == ' ')
	{
		while(buf[i] != '\0'){
			buf[i] = buf[i+1];
			i++;
		}
		i = 0;
	}
	
	/* Remove the spaces between the words */ 
	int j = 0;
	i = 0;
	while(buf[i] != '\0'){

		if(buf[i] == ' '){
			
			while(buf[i+1] == ' ')
			{
				j=i+1;
				while(buf[j] != '\0'){
					buf[j] = buf[j+1];
					j++;
				}
			}
		}
		i++;
	}
}

char **parser(char * buf){
	unsigned word_counter = 0 , i = 0 , j = 0 , char_counter = 0;
	
	space_handler(buf);
	
	/********************** To calculate the number of the word in buf. ********************/
	while(buf[i] != '\0'){
		if(buf[i] == ' ')
			word_counter++;
		i++;
	}
	word_counter++;
	/***************************************************************************************/
	/* Store words location */
	char** arr_of_words = (char**)malloc(word_counter * sizeof(char *));
	
	/************** store the words by knowing the location of the spaces. *****************/
	i = 0;
	while(buf[i] != '\0'){
		if(buf[i] == ' '){
			arr_of_words[j] = (char*)malloc(char_counter * sizeof(char));
			
			strncpy(arr_of_words[j] , buf+i-char_counter , char_counter);
			arr_of_words[j][char_counter] = '\0';	// Add the null termenal manualy
			
			char_counter = 0;
			j++;
		}
		else
		{
			char_counter++;
		}
		i++;
	}
	arr_of_words[j] = (char*)malloc(char_counter * sizeof(char));
	strncpy(arr_of_words[j] , buf+i-char_counter , char_counter);
	arr_of_words[j][char_counter] = '\0';            // Add the null termenal manualy
	/***************************************************************************************/
	arr_of_words[++j] = NULL; 		 // Add the null termenal manualy for the end of words
	
	return arr_of_words;
}
