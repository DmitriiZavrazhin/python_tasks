#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<regex.h>
#define defvalue(a) (a == 2 ? 1 : 0)
#define addbuffer(a, b, c) switch(a) {\
                           case 2:  b *= c; break;\
                           default: b += c;}


int is_txt_file(char *fileName){
	char *regex = "^.+\\.txt$";
	regex_t regex_compiled;
	if(regcomp(&regex_compiled, regex, REG_EXTENDED) == 0)
		return 0;
	return regexec(&regex_compiled, fileName, 0, NULL, 0) == 0;
}

long long calculate_file(char* fileName, int mode)
{
  FILE *file = fopen(fileName, "r");
  if(!file)
    return defvalue(mode);
  long long buffer = 0, result = defvalue(mode);
  while(fscanf(file, "%lld[ ]", &buffer) == 1)
    switch(a) {
      case 2:  b *= c; break;
      default: b += c;}
  fclose(file);
  return result;
}

long long calculate_testing_range(char* node, int mode)
{
  long long result = defvalue(mode), buffer = defvalue(mode);
	char nextNode[200] = "";
	strcpy(nextNode, node);
	DIR *dir = opendir(node);
	if(!dir)
		return defvalue(mode);
	struct dirent* dirent = readdir(dir);
  
	while(dirent)
  {
    
      int nodeNameLength = strlen(nextNode);
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
    nextNode[nodeNameLength] = '\0';
    switch(a) {
      case 2:  b *= c; break;
      default: b += c;}
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
