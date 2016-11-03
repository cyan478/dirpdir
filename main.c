/*
You will write a program that will gather various information about a directory, 
specifically:
list all the files in the directory
specify which files are directories (if any)
show the total size of all the regular files the directory
note that you do not have to recursively go through any subdirectories to find their size for this part 
(unless you want to, but that is not a simple task)
Have the program scan the current directory
Possible enhancements:
Recursively list the files in any subdirectories, update the total to include the total size of subdirectories
Print out the size in a more readable format (like using KB, MB, GB for -byte prefixes)
*/

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

void listDir(DIR *dir, int type){
	struct dirent *file = readdir(dir);
	while (file){
		if (file->d_type == type)
			printf("\t%s\n", file->d_name);
		file = readdir(dir);
	}
}


int main(){
	char *path = ".";
	DIR *dir = opendir(path);

	printf("Statistics of directory: %s \n", path);

	printf("Size: %d Bytes\n", getSize(dir));

	printf("Directories: \n ");
	listDir(dir, DT_DIR);
	printf("Regular Files: \n ");
	listDir(dir,DT_REG);


	return 0;

}
