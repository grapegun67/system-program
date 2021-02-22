#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define FILEPATH        "/home/roo/system-program/monitor/test"

/*
 * void parsing(int ii, char **tmp_name, struct dirent **namelist)
 * {
 *         int index = 0;
 *
 *  
 *  *tmp_name = (char *)malloc(sizeof(char) * 1024);
 *  
 *  memset(*tmp_name, 0x00, sizeof(char) * 1024);
 *  
 *  while( namelist[ii]->d_name[index] != '.' )
 *  
 *  {       
 *  
 *  *tmp_name[index] = namelist[ii]->d_name[index];
 *  
 *  index++;
 * 
 * }
 *
 *
 *
 *
 * 
 * *tmp_name[index] = '\0';
 * 
 * }
 * 
 * 
 *
 * */

int main()
{
	struct dirent **namelist;
	int result, index;
	char buf_name[1024];
	char tmp_name[1024];

	memset(buf_name, 0x00, sizeof(buf_name));
	memset(tmp_name, 0x00, sizeof(tmp_name));


	result = scandir(FILEPATH, &namelist, 0, alphasort);
        if(result < 0)
	
		perror("scandir()-error\n");
	else
	{
		while(result--)
		{
			/* parsing start */
			index = 0;

			while( namelist[result]->d_name[index] != '.' )
			{
				tmp_name[index] = namelist[result]->d_name[index];
				index++;
			}

			tmp_name[index] = '\0';
			
			/* parsing end */

			
			if( strcmp(buf_name, tmp_name) != 0 && namelist[result]->d_name[0] != '.' ) /* 다르면 */
			{
				strncpy(buf_name, tmp_name, sizeof(buf_name));

				/* output latest file */
				printf("%s\n", namelist[result]->d_name);

			}

			/* free heap-memory */
			free(namelist[result]);
	
		}
	
		free(namelist);
	}

	return 0;
}






