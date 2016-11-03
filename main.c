#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int getSize(DIR *dir){
	struct dirent *file = readdir(dir);
	struct stat buf;
	int ans = 0;
	while (file){
		stat(file->d_name, &buf);
		ans += buf.st_size;
		file = readdir(dir);
	}
	closedir(dir);
	return ans;
}

void listDir(char * path, int type){
	DIR *dir = opendir(path);
	struct dirent *file = readdir(dir);
	while (file){
		if (file->d_type == type)
			printf("\t%s\n", file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
}

int main(){
	char *path = ".";
	DIR *dir = opendir(path);

	printf("Statistics of directory: %s \n", path);

	printf("Size: %d Bytes\n", getSize(dir));

	printf("Directories: \n ");
	listDir(path,DT_DIR);

	printf("Regular Files: \n ");
	listDir(path,DT_REG);

	return 0;

}
