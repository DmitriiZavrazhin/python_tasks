#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<regex.h>
#define defvalue(a) (a == 2 ? 1 : 0)

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
    return defvalue(mode);
  long long buffer = 0, result = defvalue(mode);
  while(fscanf(file, "%lld[ ]", &buffer) == 1)
    switch(mode)
      {
        case 2:
          result *= buffer;
          break;
      default:
          result += buffer;
      }
  fclose(file);
  return result;
}

long long calculate_testing_range(char* node, int mode)
{
  long long result = defvalue(mode), buffer = 0;
	char nextNode[200] = "";
	strcpy(nextNode, node);
	DIR *dir = opendir(node);
	if(!dir)
		return defvalue(mode);
	struct dirent* dirent = readdir(dir);
  
	while(dirent)
  {
    
      int len = strlen(nextNode);
      strcat(nextNode, "/");
      strcat(nextNode, dirent->d_name);
    
		if(dirent->d_type == DT_DIR)
    {
      int nextMode = strcmp(dirent->d_name, "add") == 0 ? 1 : strcmp(dirent->d_name, "mul") == 0 ? 2 : -1;
      if(nextMode > 0)
			buffer = calculate_testing_range(nextNode, nextMode);
		}
		else if(dirent->d_type == DT_REG && is_txt_file(dirent->d_name))
			buffer = calculate_file(nextNode, mode);
    nextNode[len] = '\0';
    switch(mode)
      {
        case 2:
          result *= buffer;
          break;
      default:
          result += buffer;
      }
    buffer = defvalue(mode);
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
