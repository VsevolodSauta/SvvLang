#define _GNU_SOURCE

#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int process_directory(char* dir_name);
int process_file(char* dir_name);

int entry_fits(struct dirent* entry)
{
	if(entry->d_type != DT_REG)
	{
		return 0;
	} else {
		char* extension = strrchr(entry->d_name, '.');
		if(extension == NULL)
		{
			return 0;
		};
		extension++;
		if((strcmp(extension, "c") == 0) || (strcmp(extension, "h") == 0))
		{
			return 1;
		} else {
			return 0;
		};
	};
};



int process_entry(struct dirent* entry)
{
	if(entry->d_type == DT_DIR)
	{
		if(entry->d_name[0] != '.')
		{
			return process_directory(entry->d_name);
		};
	} else {
		if(entry_fits(entry))
		{
			return process_file(entry->d_name);
		};
	};
	return 0;
};

int process_file(char* file_name)
{
	FILE* file = fopen(file_name, "r");
	int count = 0;

	while(!feof(file))
	{
		char ch = fgetc(file);
		if(ch == ';')
		{
			count++;
		};
	};
	return count;
};

int process_directory(char* dir_name)
{
	struct dirent* entry;
	DIR* directory;
	int count = 0;
	char* prev_dir;
	
	prev_dir = get_current_dir_name();
	chdir(dir_name);
	directory = opendir(".");
	while((entry = readdir(directory)) != NULL)
	{
		count += process_entry(entry);
	};
	closedir(directory);
	chdir(prev_dir);
	free(prev_dir);
	
	return count;
};

int main(void)
{
	printf("%d semicolons.\n", process_directory("."));
	return 0;
};
