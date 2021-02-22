#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define FILEPATH        "/home/roo/system-program/monitor/test"

int main()
{

	DIR *dirp;
	struct dirent *dirent;
	struct stat statbuf;
	struct tm tmbuf;
	char filename[1024];


	dirp = opendir(FILEPATH);

	if(dirp == NULL)
	{
		perror("opendir()-error\n");
		return -1;
	}

	
	while(dirent = readdir(dirp))
	{
		
		if(dirent->d_name[0] != '.')
		{

			snprintf(filename, sizeof(filename), "%s/%s", FILEPATH, dirent->d_name);
 			printf("name: %15s|, ", dirent->d_name);

			stat(filename, &statbuf);

			printf("size: %10ld|, ", statbuf.st_size);
			printf("time: %s", ctime((time_t *)&statbuf.st_mtim));
		}

	}

	closedir(dirp);
	return 0;
}



