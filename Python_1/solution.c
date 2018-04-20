#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<regex.h>
#define MAX_PATH_LENGTH 100
#define defvalue(a) (a == 2 ? 1 : 0)
#define addtoresult(a, b, c)  {switch(a) {case 2: b *= c; break; default: b += c; }}

int is_txt_file(char *fileName)
{
    char *regex = "^.+\\.txt$";
    regex_t regex_compiled;
    if(regcomp(&regex_compiled, regex, REG_EXTENDED))
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
        addtoresult(mode, result, buffer)
    fclose(file);
    return result;
}

long long calculate_testing_range(char* node, int mode)
{
    long long result = defvalue(mode), buffer = defvalue(mode);
    char nextNode[MAX_PATH_LENGTH] = "";
    strcpy(nextNode, node);
    DIR* directory = opendir(node);
    if(!directory)
        return defvalue(mode);
    struct dirent* dirent = readdir(directory);
    while(dirent)
    {
        int nodeNameLength = strlen(nextNode);
        strcat(nextNode, "/");
        strcat(nextNode, dirent->d_name);
        if(dirent->d_type == DT_DIR)
        {
            int nextMode = -1;
            if(strcmp(dirent->d_name, "add") == 0)
                nextMode = 1;
            else if(strcmp(dirent->d_name, "mul") == 0)
                nextMode = 2;       
            if(nextMode > 0)
                buffer = calculate_testing_range(nextNode, nextMode);
        }
        else if(dirent->d_type == DT_REG && is_txt_file(dirent->d_name))
        {
            buffer = calculate_file(nextNode, mode);
        }
        nextNode[nodeNameLength] = '\0';
        addtoresult(mode, result, buffer)
        buffer = defvalue(mode);
        dirent = readdir(directory);
    }
    closedir(directory);
    return result;
}

int main()
{
    FILE* file = fopen("/home/box/result.txt", "w");
    fprintf(file, "%lld", calculate_testing_range("/home/box/tmp", 0));
    fclose(file);
}
