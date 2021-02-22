#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define FILEPATH        "/home"
#define MAX_INT         2147000000

struct tmp_ctime_file{

	char name[1024];

	int ctim;
};

int main()
{
	DIR *dirp;
	struct dirent *dirent;
	struct stat statbuf;
	struct tm tmbuf;
	char filename[1024];
	struct tmp_ctime_file max_file;
	struct tmp_ctime_file min_file;

	memset(&max_file, 0x0, sizeof(max_file));
	memset(&min_file, 0x0, sizeof(min_file));

	min_file.ctim = MAX_INT;

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

			stat(filename, &statbuf);
			if(max_file.ctim < statbuf.st_ctim.tv_sec)
			{
				strncpy(max_file.name, dirent->d_name, sizeof(dirent->d_name));
				max_file.ctim = statbuf.st_ctim.tv_sec;

				printf("max ctim: %d\n", max_file.ctim);
			}

			
			if(min_file.ctim > statbuf.st_ctim.tv_sec)
			{
				strncpy(min_file.name, dirent->d_name, sizeof(dirent->d_name));
				min_file.ctim = statbuf.st_ctim.tv_sec;

				printf("min ctim: %d\n", min_file.ctim);
			}
		}

	}

	printf("\n");

	printf("max)\n");
        printf("name: %10s| ", max_file.name);
 	printf("time: %d\n", max_file.ctim);

	printf("min)\n");
	printf("name: %10s| ", min_file.name);
	printf("time: %d\n", min_file.ctim);


	closedir(dirp);
	return 0;
}


