#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include <regex.h>

int is_txt_file(char *filename){
	char *regex = "^.+\\.txt$";
	regex_t regex_compiled;
	if(regcomp(&regex_compiled, regex, REG_EXTENDED))
		return 0;
	return regexec(&regex_compiled, filename, 0, NULL, 0) == 0;
}

long long calculate_file(char* filename, int mode)
{
  FILE *file = fopen(filename, "r");
  if(!file)
    return;
  long long buffer = 0, result = 0;
  while(fscanf(file, "%lld[ ]", &buffer) == 1)
    switch(mode)
      {
        case 1:
          result += buffer;
          break;
        case 2:
          result *= buffer;
          break;
      }
  fclose(file);
  return result;
}

long long calculate_testing_range(char* node, int mode)
{
  long long result = 0, buffer = 0;
  int nextMode = 0;
	char nextNode[200] = "";
	strcpy(nextNode, node);
	DIR *dir = opendir(node);
	if(!dir)
		return;
	struct dirent* dirent = readdir(dir);
  
	while(dirent)
  {
    nextMode = strcmp(dirent->d_name, "add") == 0 ? 1 : strcmp(dirent->d_name, "mul") == 0 ? 2 : -1;
		if(dirent->d_type == DT_DIR && nextMode > 0)
    {
			int len = strlen(nextNode);
			strcat(nextNode, "/");
			strcat(nextNode,dirent->d_name);
			buffer = calculate_testing_range(nextNode, nextMode);
      switch(mode)
      {
        case 1:
          result += buffer;
          break;
        case 2:
          result *= buffer;
          break;
      }
			nextNode[len] = '\0';
		}
		else if(dirent->d_type == DT_REG && is_txt_file(dirent->d_name)){
      int len = strlen(nextNode);
      strcat(nextNode, "/");
      strcat(nextNode,dirent->d_name);
			buffer = calculate_file(nextNode, mode);
      switch(mode)
      {
        case 1:
          result += buffer;
          break;
        case 2:
          result *= buffer;
          break;
      }
      nextNode[len] = '\0';
		}
		dirent = readdir(dir);
	}
	closedir(dir);
  return result;
}

int main()
{
  long long result = calculate_testing_range("/home/box/tmp", 0);
  FILE *file = fopen("/home/box/result.txt", "w");
  fprintf(file, "%lld", result);
  fclose(file);
}
