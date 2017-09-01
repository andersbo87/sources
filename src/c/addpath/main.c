//
//  main.c
//  addtopath
//
//  Created by Anders Bolt-Evensen on 18.03.11.
//  Copyright 2011 Høgskolen i Østfold. All rights reserved.
//
/*
    addtopath is supposed to install a given Aqua app to the /Applications
    directory, as well as putting an executable file that can be run
    from a terminal to open the installed application.
    The terminal based executable is supposed to be put in the /usr/bin directory
    and will therefore require administrator privilegies.
 */
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <struct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <regex.h>
#include <errno.h>
#include <err.h>
#include <readline/readline.h>

#define FALSE 0
#define TRUE !FALSE
enum {
    WALK_OK = 0,
    WALK_BADPATTERN,
    WALK_NAMETOOLONG,
    WALK_BADIO,
};
#define WS_NONE 0
#define WS_RECURSIVE 1 << 0
//#define WS_RECURSIVE(1 << 0)
#define WS_DEFAULT WS_RECURSIVE
//#define WS_FOLLOWLINK(1 << 1)/* follow symlinks */
#define WS_FOLLOWLINK 1 << 1
//#define WS_DOTFILES(1 << 2)/* per unix convention, .file is hidden */
#define WS_DOTFILES 1 << 2
//#define WS_MATCHDIRS(1 << 3)/* if pattern is used on dir names too */
#define WS_MATCHDIRS 1 << 3

int genereateExectuableFileInUsrBinDirectoryForOtherApps(const char *sourceFile, const char *appName, int recurse);
int StrToLwrOtherApps(const char* mainstring, char *output);
int copyToApplicationsFolder(const char *sourceAppName, const char *destinationAppName);
int searchForApp(char *pathname, const char *appName, int nr);

char *definatePathName;
int color_support = 0;

int checkIfExecutableAlreadyExists(char name)
{
    int res = 0;
    struct stat fileattrib;
    char *c = getenv("PATH");
    char *pch = strtok(c, ":");
    res = stat(pch, &fileattrib);
    return res;
}

int walk_recur(char *dname, regex_t *reg, int spec)
{
    //printf("Hei.\n");
    struct dirent *dent;
    DIR *dir;
    struct stat st;
    char fn[FILENAME_MAX];
    int res = WALK_OK;
    long len = strlen(dname);
    if (len >= FILENAME_MAX - 1)
        return WALK_NAMETOOLONG;
    
    strcpy(fn, dname);
    fn[len++] = '/';
    
    if (!(dir = opendir(dname))) {
        warn("can't open %s", dname);
        if (dir) closedir(dir);
        return WALK_BADIO;
    }
    
    errno = 0;
    char *s;
    char ns[MAXPATHLEN];
    while ((dent = readdir(dir))) {
        if (!(spec & WS_DOTFILES) && dent->d_name[0] == '.')
            continue;
        if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
            continue;
        
        strncpy(fn + len, dent->d_name, FILENAME_MAX - len);
        if (lstat(fn, &st) == -1) {
            warn("Can't stat %s", fn);
            res = WALK_BADIO;
            //if (dir) closedir(dir);
            continue;
        }
        
        /* don't follow symlink unless told so */
        if (S_ISLNK(st.st_mode) && !(spec & WS_FOLLOWLINK))
            continue;
        
        /* will be false for symlinked dirs */
        if (S_ISDIR(st.st_mode)) {
            /* recursively follow dirs */
            if ((spec & WS_RECURSIVE))
                walk_recur(fn, reg, spec);
            
            if (!(spec & WS_MATCHDIRS)) continue;
        }
        
        /* pattern match */
        if (!regexec(reg, fn, 0, 0, 0))
        {
            long length;
            if((length = strlen(fn)) > 3 && !strcmp(fn + length - 4, ".app"))
            {
                int i;
                //puts(fn);
                s = strrchr(strchr(fn, '/'), '/');
                s += 1;
                
                strcpy(ns, fn);
                for(i = 0; s[i] != '\0'; i++);
                s[--i] = '\0';
                s[--i] = '\0';
                s[--i] = '\0';
                s[--i] = '\0';
                //genereateExectuableFileInUsrBinDirectoryForOtherApps(s, ns, 1);
                int err = 0;
                //the idea of fileWithoutExtension is to store the appName without the .c extension
                char *fileWithoutExtension; 
                fileWithoutExtension = (char *)s;//initializing string for use later on
                char fileContent[10000] ="";//creating an empty string
                strcat(fileContent, "#include <stdlib.h>\n #include <stdio.h>\n #include <signal.h>\n #include <unistd.h>\n #include <sys/types.h>\n #include <sys/wait.h>\n #include <fcntl.h>\n #include <semaphore.h>\n #include <string.h>\n int i = 0;\n int fd = 0;\nchar *strdup(const char *str)\n{\n    long n = strlen(str) + 1;\n    char *dup = malloc(n * sizeof(char));\n    if(dup)\n    {\n        strcpy(dup, str);\n    }\n    return dup;\n}\n void handler(int sig)\n {\n    pid_t pid;\n    pid = wait(NULL);\n    fprintf(stdout, \"Pid %d exited.\\n\", pid);\n }\n int main(int argc, const char **argv)\n {\n    signal(SIGCHLD, handler);\n    int defout = dup(2);\n    fd=open(\"/dev/console\", O_RDWR|O_CREAT);\n    dup2(fd, 2);\n    if(i == 0)\n    {\n        if(!fork())\n        {\n            close(fd);\n            close(defout);\n            return 0;\n        }\n        else\n        {\n            //fprintf(stdout, \n                          //\"Parent pid is %d\\n\"\n                          //\"If ");
                strcat(fileContent,fileWithoutExtension);
                strcat(fileContent, " freezes or stops responding, type kill -9 %d.\\n\",getpid(), getpid());\n            char * argvlist[3];\n            argvlist[0] = strdup(\"");
                strcat(fileContent, ns);
                strcat(fileContent, "/Contents/MacOS/");
                strcat(fileContent, fileWithoutExtension);
                strcat(fileContent, "\");\n            argvlist[1] = (char*)argv[1];\n            argvlist[2] = NULL;\n            execvp(argvlist[0], argvlist);\n            dup2(defout, 2); // redirect output back to stderr\n            close(fd);\n            close(defout);\n        }\n    }\n   i++;\n    printf(\"Status: %d\\n\", i);\n    getchar();\n    return 0;\n}");
                //c = appName;
                char directoryName[450] = "/private/tmp/";
                strcat(directoryName, s);
                strcat(directoryName, ".c"); //applying the .c extension to "c"
                FILE *file = fopen(directoryName, "wb");
                
                fprintf(file, "%s", fileContent); //prints content of fileContent to file
                fclose(file); //closes the file
                int nr = fork(); //creates a new process
                if(nr == 0)
                {
                    fprintf(stdout, 
                            "\033[22;33m %s: \n"
                            "\033[22;32m Compiling %s...\033[00;00m\n",ns,directoryName);
                    char *argList[5];
                    argList[0] = strdup("cc");
                    argList[1] = strdup(directoryName);
                    char installfile[1000] = "/usr/local/bin/";
                    StrToLwrOtherApps(fileWithoutExtension, fileWithoutExtension);
                    char *res = fileWithoutExtension;
                    char *p1 = res;
                    char *p2 = res;
                    p1 = res;
                    //the following while loop removes any whitespaces from the generated executable file:
                    while(*p1 != 0) 
                    {
                        if(ispunct(*p1) || isspace(*p1)) {
                            ++p1;
                        }
                        else
                            *p2++ = *p1++; 
                    }
                    *p2 = 0; 
                    strcat(installfile, fileWithoutExtension);
                    argList[2] = strdup("-o");
		    if(access(installfile, F_OK) != -1)
		    {
		      fprintf(stderr, "The file %s already exists.\n", installfile);
		      return 1;
		    }
                    argList[3] = strdup(installfile);
                    argList[4] = NULL;
                    err = execvp(argList[0], argList);
                }
                waitpid(nr, NULL, 0);
                remove(directoryName);
            }
            else
            {
                printf("Nei.\n");
            }
        }
    }
    //sourcefiles = s, ... = ns
    
    if (dir) closedir(dir);
    return res ? res : errno ? WALK_BADIO : WALK_OK;
}

int walk_dir(char *dname, char *pattern, int spec)
{
    regex_t r;
    int res;
    if (regcomp(&r, pattern, REG_EXTENDED | REG_NOSUB))
        return WALK_BADPATTERN;
    res = walk_recur(dname, &r, spec);
    regfree(&r);
    
    return res;
}

/* Here is the function declaration "StrToLwr" for converting upper case characters in a string to lower case characters. 
 The function takes two arguments. Both are char type pointers. 
 First one is the actual string passed to it for conversion. 
 The second argument will send the result back to the calling program. 
 The function will convert only UPPERCASE CHARACTERS to lowercase characters. Every other character will remain as it is*/
int StrToLwrOtherApps(const char* mainstring, char *output)
{
	long Len = strlen(mainstring); // Len will contain the length of the passed string.
	int i;
    // Now we will move from the 0th character in the string till its length and we will check if its a UPPERCASE character,
    // and then change it to lowercase characters.
	for(i = 0; i < Len; i++) 
	{
		// If the ASCII code of the character i.e. integer value of the character is less than 65, 
        // then copy the character as it is into the result string. 
        // It means that the character is not in the range of upper case characters
		if( (int)mainstring[i] < 65) 
		{	
			output[i] = mainstring[i];
		}
        // If the ASCII code of the character i.e. integer value of the character 
        //is between 65 and 90, 
        // then its a UPPERCASE CHARACTER and let's convert it into the lowercase. 
        // By adding 32 in the ASCII number of the character, the character will be converted to 
        //lowercase. 
        // Such as, the ASCII code of UPPERCASE A is 65 and the ASCII code of lowercase a is 97. 
        // If we add 32 to UPPERCASE A, its ASCII code will become 97 and the character is changed 
        //from UPPERCASE to lowercase
		if( (int)mainstring[i] >= 65 && (int)mainstring[i] <= 90) 
		{	
			output[i] = (char)mainstring[i] + 32;
		}
        // If the ASCII code of the character i.e. integer value of the character 
        //is between 92 and 122, 
        // then copy the character as it is into the result string. 
        // It means that the character is not in the range of upper case characters.
        // This is the range for lowercase characters
		if( (int)mainstring[i] >= 97 && (int)mainstring[i] <= 122) 
		{	
			output[i] = (char)mainstring[i];
		}
        //If the ASCII code of the character i.e. integer value of the character 
        //is greater than 122, 
        // then copy the character as it is into the result string. 
        // It means that the character is not in the range of upper case characters. 
        // This range contains the graphicalASCII characters.
		if( (int)mainstring[i] > 122) 
		{	
			output[i] = mainstring[i];
		}
	}
	output[i] = '\0'; // Null terminating the string to show the end of the string
    //return genereateExectuableFileInUsrBinDirectory(output);
    //printf("output: %s\n", output);
    return 0;
}

int searchForOtherApp(char *filename)
{
    printf("It doesn't look like %s is located in the application folder.\n"
           "In the prompt below, type the path to %s.\n"
           "If you don't know the exact path to the application,\n"
           "type 'find / -name \"%s\"' in the shell\n", filename, filename, filename);
    char read[365];
    printf("Type the path in which %s is stored, i.e. /Applications/Utilities: ",filename);
    fgets(read, 95, stdin);
	if(read[strlen(read) -1] == '\n')
	{
		read[strlen(read) -1] = '\0';
	}
    long len_filename = strlen(filename);
    long len_read = strlen(read);
    if(len_filename + len_read >= 164)
    {
        fprintf(stderr, "\033[22;31m The entered pathname is too long.\033[00;00m\n");
        return 1;
    }
    else
    {
        //strcat(read,filename);
        definatePathName = read;
        //searchForApp(read, filename, 1);
        
        int count, i;
        struct direct **files;
        int file_select2();
        count = scandir(read, &files, file_select2, alphasort);
        if(count <= 0)
        {
            fprintf(stderr, "\033[22;31m No such file: %s\033[00;00m\n", filename);
            exit(1);
        }
        char name[MAXPATHLEN] = "";
        for(i = 1; i < count +1; i++)
        {
            if(strcmp(files[i-1]->d_name, filename) == 0)
            {
                strcpy(name, files[i-1]->d_name);
                strcat(read, name);
                int i;
                for(i = 0; filename[i] != '\0'; i++);
                filename[--i] = '\0';
                filename[--i] = '\0';
                filename[--i] = '\0';
                filename[--i] = '\0';
                genereateExectuableFileInUsrBinDirectoryForOtherApps(filename, read, 0);
                return 0;
            }
        }
    }
    return 0;
}


int searchForApp(char *pathname, const char *appName, int nr)
{
    int count, i;
    struct direct **files;
    int file_select2();
    count = scandir(pathname, &files, file_select2, alphasort);
    if(count <= 0)
    {
        fprintf(stderr, "\033[22;31m No such file: %s\033[00;00m\n", pathname);
        exit(1);
    }
    char newPath[MAXPATHLEN] = "";//"\"";
    strcat(newPath, appName);
    if(nr == 0)
    {    
        strcat(newPath, ".app");
    }//strcat(newPath, "\"");
    char pn[MAXPATHLEN] = "/Applications/";
    char name[MAXPATHLEN] = "";
    for(i = 1; i < count +1; i++)
    {
        if(strcmp(files[i-1]->d_name, newPath) == 0)
        {
            //fprintf(stdout, "Found %s\n", files[i-1]->d_name);
            strcpy(name, files[i-1]->d_name);
            strcat(pn, name);
            int i;
            for(i = 0; name[i] != '\0'; i++);
            name[--i] = '\0';
            name[--i] = '\0';
            name[--i] = '\0';
            name[--i] = '\0';
            genereateExectuableFileInUsrBinDirectoryForOtherApps(name, pn, 0);
        }
    }
    if(nr != 0)
    {
        fprintf(stderr, "\033[22;31m Couldn't find %s.\033[00;00m\n", appName);
        return 2;
    }
    searchForOtherApp(newPath);
    return 0;
}

int filterAppContentsInVolumesDirectory(const char *appName)
{
    int err = 0;
    char pathname[MAXPATHLEN] = "/Volumes/";
    strcat(pathname, appName);
    strcat(pathname, "/");
    int count, i;
    struct direct **files;
    int file_select();
    count = scandir(pathname, &files, file_select, alphasort);
    fprintf(stdout, "%s\n", pathname);
    if(count <= 0)
    {
        fprintf(stdout, "Directory is empty\n");
        return 1;
        //exit(1);
    }
    for(i = 1; i < count +1; i++)
    {
        char name[MAXPATHLEN] = "";//files[i-1]->d_name;
        strcpy(name, files[i-1]->d_name);
        strcat(pathname, name);
        char destname[MAXPATHLEN] = "/Applications/";
        strcat(destname, name);
        if(strcmp(name, appName) == 46)
        {
            fprintf(stdout, "About to copy %s\n", appName);
            copyToApplicationsFolder(pathname, destname);
        }
        else
        {
            printf("%d\n", strcmp(name, appName));
        }
        searchForApp("/Applications/", appName, 0);
    }
    return err;
}
int file_select3(struct direct *entry)
{
    if ((strcmp(entry->d_name, ".app") == 0))
        return (TRUE);
    else
        return (FALSE);
}
int file_select2(struct direct *entry)
{
    if ((strcmp(entry->d_name, ".") == 0) ||(strcmp(entry->d_name, "..") == 0 || (strcmp(entry->d_name, ".localized") == 0)|| (strcmp(entry->d_name, ".DS_Store") == 0)))
        return (FALSE);
    else
        return (TRUE);
}
int file_select(struct direct *entry)
{
    char *ptr;
    char *rindex(const char *s, int c);
    if((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
    {
        return (FALSE);
    }
    /*check for filename extensions */
    ptr = rindex(entry->d_name, '.');
    if((ptr != NULL) && ((strcmp(ptr, ".c") == 0) || (strcmp(ptr, ".h") == 0) || strcmp(ptr, ".o") == 0 || strcmp(ptr, ".app") == 0 || strcmp(ptr, "/") == 0))
    {
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}

int copyToApplicationsFolder(const char *sourceAppName, const char *destinationAppName)
{
    //do something...
    int i = 0;
    int process = fork();
    if(process == 0)
    {
        char *argv[5];
        argv[0] = strdup("cp");
        argv[1] = strdup("-R");
        argv[2] = strdup(sourceAppName);
        argv[3] = strdup(destinationAppName);
        argv[4] = NULL;
        i = execvp(argv[0], argv);
        if(i != 0)
        {
            fprintf(stderr, "\033[22;31m There was an error copying %s to %s.\nExiting...\033[00;00m", sourceAppName, destinationAppName);
            exit(i);
        }
    }
    else
    {
        return process;
    }
    waitpid(process, NULL, 0);
    return i;
}

int checkIfFileExists(char *fileName, char *sourceFile)
{
    char *fileWithoutExtension; 
    char newFileName[100];
    //newFileName = strcat(fileName, strcat("/Contents/MacOS/", fileWithoutExtension));
    strcat(newFileName,fileName);
    strcat(newFileName, "/Contents/MacOS/");
    strcat(newFileName, sourceFile);
    fileWithoutExtension = (char *)sourceFile;
    struct stat buf;
    int i = stat (newFileName, &buf );
    /* File found */
    if ( i == 0 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int genereateExectuableFileInUsrBinDirectoryForOtherApps(const char *sourceFile, const char *appName, int recurs)
{
    int err = 0;
    //the idea of fileWithoutExtension is to store the appName without the .c extension
    char *fileWithoutExtension; 
    fileWithoutExtension = (char *)sourceFile;//initializing string for use later on
    char fileContent[10000] ="";//creating an empty string
    char *newAppName = (char *)appName;
    //struct stat buf;
    int i = checkIfFileExists(newAppName,fileWithoutExtension);
    /* File found */
    if ( i == 0 )
    {
        strcat(fileContent, "#include <stdlib.h>\n #include <stdio.h>\n #include <signal.h>\n #include <unistd.h>\n #include <sys/types.h>\n #include <sys/wait.h>\n #include <fcntl.h>\n #include <semaphore.h>\n #include <string.h>\n int i = 0;\n int fd = 0;\nchar *strdup(const char *str)\n{\n        long n = strlen(str) + 1;\n    char *dup = malloc(n * sizeof(char));\n    if(dup)\n    {\n        strcpy(dup, str);\n    }\n    return dup;\n}\n void handler(int sig)\n {\n    pid_t pid;\n    pid = wait(NULL);\n    fprintf(stdout, \"Pid %d exited.\\n\", pid);\n }\n int main(int argc, const char **argv)\n {\n    signal(SIGCHLD, handler);\n    int defout = dup(2);\n    fd=open(\"/dev/console\", O_RDWR|O_CREAT);\n    dup2(fd, 2);\n    if(i == 0)\n    {\n        if(!fork())\n        {\n            close(fd);\n            close(defout);\n            return 0;\n        }\n        else\n        {\n            //fprintf(stdout, \n                          //\"Parent pid is %d\\n\"\n                          //\"If ");
        strcat(fileContent,fileWithoutExtension);
        strcat(fileContent, " freezes or stops responding, type kill -9 %d.\\n\",getpid(), getpid());\n            char * argvlist[3];\n            argvlist[0] = strdup(\"");
        strcat(fileContent, appName);
        strcat(fileContent, "/Contents/MacOS/");
        strcat(fileContent, fileWithoutExtension);
        strcat(fileContent, "\");\n            argvlist[1] = (char *)argv[1];\n            argvlist[2] = NULL;\n            execvp(argvlist[0], argvlist);\n            dup2(defout, 2); // redirect output back to stderr\n            close(fd);\n            close(defout);\n        }\n    }\n   i++;\n    printf(\"Status: %d\\n\", i);\n    getchar();\n    return 0;\n}");
        char directoryName[450] = "/private/tmp/";
        strcat(directoryName, sourceFile);
        strcat(directoryName, ".c"); //applying the .c extension to "c"
        FILE *file = fopen(directoryName, "wb");
        
        fprintf(file, "%s", fileContent); //prints content of fileContent to file
        fclose(file); //closes the file
        int nr = fork(); //creates a new process
        if(nr == 0)
        {
            fprintf(stdout, 
                    "\033[22;33m %s: \n"
                    "\033[22;32m Compiling %s...\033[00;00m\n",appName,directoryName);
            char *argList[5];
            argList[0] = strdup("cc");
            argList[1] = strdup(directoryName);
            char installfile[1000] = "/usr/local/bin/";
            StrToLwrOtherApps(fileWithoutExtension, fileWithoutExtension);
            char *res = fileWithoutExtension;
            char *p1 = res;
            char *p2 = res;
            p1 = res;
            //the following while loop removes any whitespaces from the generated executable file:
            while(*p1 != 0) 
            {
                if(ispunct(*p1) || isspace(*p1)) {
                    ++p1;
                }
                else
                    *p2++ = *p1++; 
            }
            *p2 = 0; 
            strcat(installfile, fileWithoutExtension);
            argList[2] = strdup("-o");
	    if(access(installfile, F_OK) != -1)
	    {
	      fprintf(stderr, "The file %s exists.\n", installfile);
	      return -1;
	    }
            argList[3] = strdup(installfile);
            argList[4] = NULL;
            err = execvp(argList[0], argList);
        }
        waitpid(nr, NULL, 0);
        //remove(directoryName);
        if(recurs == 0)
        {
            fprintf(stdout, "\033[01;32m Done.\033[00;00m\n");
            exit(0);
        }
    }
    
    else
    {
        StrToLwrOtherApps(sourceFile, (char*)sourceFile);
        strcat(fileContent, "#include <stdlib.h>\n #include <stdio.h>\n #include <signal.h>\n #include <unistd.h>\n #include <sys/types.h>\n #include <sys/wait.h>\n #include <fcntl.h>\n #include <semaphore.h>\n #include <string.h>\n int i = 0;\n int fd = 0;\nchar *strdup(const char *str)\n{\nlong n = strlen(str) + 1;\n    char *dup = malloc(n * sizeof(char));\n    if(dup)\n    {\n        strcpy(dup, str);\n    }\n    return dup;\n}\n void handler(int sig)\n {\n    pid_t pid;\n    pid = wait(NULL);\n    fprintf(stdout, \"Pid %d exited.\\n\", pid);\n }\n int main(int argc, const char **argv)\n {\n    signal(SIGCHLD, handler);\n    int defout = dup(2);\n    fd=open(\"/dev/console\", O_RDWR|O_CREAT);\n    dup2(fd, 2);\n    if(i == 0)\n    {\n        if(!fork())\n        {\n            close(fd);\n            close(defout);\n            return 0;\n        }\n        else\n        {\n            //fprintf(stdout, \n                          //\"Parent pid is %d\\n\"\n                          //\"If ");
        strcat(fileContent,fileWithoutExtension);
        strcat(fileContent, " freezes or stops responding, type kill -9 %d.\\n\",getpid(), getpid());\n            char * argvlist[3];\n            argvlist[0] = strdup(\"");
        strcat(fileContent, appName);
        strcat(fileContent, "/Contents/MacOS/");
        strcat(fileContent, fileWithoutExtension);
        strcat(fileContent, "\");\n            argvlist[1] = (char *)argv[1];\n            argvlist[2] = NULL;\n            execvp(argv[0], argv);\n            dup2(defout, 2); // redirect output back to stderr\n            close(fd);\n            close(defout);\n        }\n    }\n   i++;\n    if(i == 1)\n    {\n        printf(\"");
        strcat(fileContent, appName);
        strcat(fileContent, "/Contents/MacOS/");
        strcat(fileContent, fileWithoutExtension);
        strcat(fileContent, ": no such file or directory.\\n\");\n    }\n    printf(\"Status: %d\\n\", i);\n    getchar();\n    return 0;\n}");
    //c = appName;
        char directoryName[450] = "/private/tmp/";
        strcat(directoryName, sourceFile);
        strcat(directoryName, ".c"); //applying the .c extension to "c"
        FILE *file = fopen(directoryName, "wb");
        
        fprintf(file, "%s", fileContent); //prints content of fileContent to file
        fclose(file); //closes the file
        int nr = fork(); //creates a new process
        if(nr == 0)
        {
            fprintf(stdout, 
                    "\033[22;33m %s: \n"
                    "\033[22;32m Compiling %s...\033[00;00m\n",appName,directoryName);
            char *argList[5];
            argList[0] = strdup("cc");
            argList[1] = strdup(directoryName);
            char installfile[1000] = "/usr/local/bin/";
            StrToLwrOtherApps(fileWithoutExtension, fileWithoutExtension);
            char *res = fileWithoutExtension;
            char *p1 = res;
            char *p2 = res;
            p1 = res;
            //the following while loop removes any whitespaces from the generated executable file:
            while(*p1 != 0) 
            {
                if(ispunct(*p1) || isspace(*p1)) {
                    ++p1;
                }
                else
                    *p2++ = *p1++; 
            }
            *p2 = 0; 
            strcat(installfile, fileWithoutExtension);
            argList[2] = strdup("-o");
	    if(access(installfile, F_OK) != -1)
	    {
	      fprintf(stdout, "The file %s already exists.\n", installfile);
	      return -1;
	    }
            argList[3] = strdup(installfile);
            argList[4] = NULL;
            err = execvp(argList[0], argList);
        }
        waitpid(nr, NULL, 0);
        //remove(directoryName);
        if(recurs == 0)
        {
            fprintf(stdout, "\033[01;32m Done.\033[00;00m\n");
            exit(0);
        }
    }
    long fileWithoutExtensionLength = strlen(fileWithoutExtension);
    int counter = 0;
    for(counter = 0; counter < fileWithoutExtensionLength; counter++)
    {
        fileWithoutExtension[i] = '\0';
    }
    return err;
}

void changeLocalBashProfilePermissions(void)
{
    char *home = getenv("HOME");
    int nr = fork();
    if(nr == 0)
    {
        char *s[4];
        s[0] = strdup("chmod");
        s[1] = strdup("u+x");
        s[2] = strdup(home);
        s[3] = NULL;
        execvp(s[0], s);
    }
    waitpid(nr, NULL, 0);
}

void changeLocalBashProfileOwner(void)
{
    char *home = getenv("HOME");
    char *user = getlogin();
    printf("User: %s\n", user);
    int nr = fork();
    if(nr == 0)
    {
        char *s[4];
        s[0] = strdup("chown");
        s[1] = strdup(user);
        s[2] = strdup(home);
        s[3] = NULL;
        execvp(s[0], s);
    }
    waitpid(nr, NULL, 0);
    changeLocalBashProfilePermissions();
}

void checkForLocalBashProfile(void)
{
    char *home = getenv("HOME");
    if(access(strcat(home, "/.bash_profile"), F_OK) == -1)
    {
        FILE *file = fopen(home, "wb");
        fprintf(file, "export PATH=/usr/cocoa/bin:$PATH");
        fclose(file);
        changeLocalBashProfileOwner();
        fprintf(stdout, 
                "The file %s has been created.\n"
                "***PLEASE RUN \"source %s\" to add /usr/cocoa/bin"
                "to the end of your existing PATH variable.***\n",home, home);
    }
}

void checkIfUsrCocoaBinDirectoryExists(void)
{
    struct stat st;
    if(!stat("/usr/cocoa",&st) == 0)
	{
        if(mkdir("/usr/cocoa", S_IRWXU|S_IXGRP|S_IRGRP|S_IXOTH|S_IROTH) != 0)
        {
            fprintf(stderr, "\033[22;31m Could not create the /usr/cocoa/ directory "
                    "(error code %d):\033[00;00m\n", errno);
            perror("/usr/");
        }
	}
    if(!stat("/usr/cocoa/bin",&st) == 0)
	{
        if(mkdir("/usr/cocoa/bin", S_IRWXU|S_IXGRP|S_IRGRP|S_IXOTH|S_IROTH))
        {
            fprintf(stderr, "\033[22;31m Could not create the /usr/cocoa/bin directory "
                    "(error code %d):\033[00;00m\n", errno);
            perror("/usr/cocoa/");
        }
	}
}

int askUserConfirmation()
{
    int res = 0;
    char ans;
    fprintf(stdout, "Your terminal type does not seem to support colors."
           "This might have some undesired results. Are you sure you want to continue? (y/n)");
    sleep(10);
    scanf("%s", &ans);
    if(ans == 'y')
    {
        res = 0;
    }
    else if(ans == 'n')
    {
        res = 0;
    }
    else
    {
        //printf("Please answer y for yes or n for no.\n");
        askUserConfirmation();
    }
    return res;
}

int main (int argc, const char * argv[])
{
    int err = 0;
    //check if the user is root:
    if(getuid() != 0)
    {
        fprintf(stderr, 
                "\033[22;31m %s must be run as root.\n"
                "This is because %s is going to install "
                "%s to /usr/bin/%s,\n"
                "and needs root privilegies to do so.\033[00;00m\n", 
                argv[0], argv[0], argv[1], argv[1]);
    }
    checkForLocalBashProfile();
    checkIfUsrCocoaBinDirectoryExists();
    char c = *argv[1];
    if(strcmp(&c, "-") == 0)
    {
        if(strcmp(argv[1], "-r") != 0)
        {
            fprintf(stderr,"Invalid option.\n");
            exit(1);
        }
    }
    if(argc <= 1)
    {
        fprintf(stderr, "\033[22;31m You must provide a parameter.\033[00;00m\n");
        err = 1;
        exit(err);
    }
    else if(argc == 2)
    {
        if(strcmp(argv[1], "-r") == 0)
        {
            fprintf(stderr, 
                    "\033[22;31m It seems like there is an error:\n"
                    "When providing the -r option, you need to type a parameter\n"
                    "e.g. / to add applications from that directory and "
                    "its subdirectories.\033[00;00m\n");
            err = 1;
            exit(err);
        }
        else
        {
            searchForApp("/Applications/", argv[1], 0);
        }
    }
    else if(argc == 3)
    {
        if(strcmp(argv[1], "-r") == 0)
        {
            if(strcmp(argv[1], "-r") == 0)
            {
                //int r = walk_dir((char *)argv[2], "$*.app", WS_DEFAULT | WS_MATCHDIRS);
                int r = walk_dir((char *)argv[2], ".app$", WS_MATCHDIRS);
                switch(r) {
                    case WALK_OK:
                        break;
                    case WALK_BADIO:
                        fprintf(stderr, "\033[22;31m IO error\033[00;00m\n");
                        return 1;
                    case WALK_BADPATTERN:
                        fprintf(stderr, "\033[22;31m Bad pattern\033[00;00m\n");
                        return 1;
                    case WALK_NAMETOOLONG:
                        fprintf(stderr, "\033[22;31m Filename too long\033[00;00m\n");
                        return 1;
                    default:
                        fprintf(stderr, "\033[22;31m Unknown error?\033[00;00m\n");
                }
            }
        }
        else
        {
            if(strcmp(argv[2], "-r") == 0)
            {
                fprintf(stderr, 
                        "\033[22;31m It seems like there is an error:\n"
                        "The -r option cannot be specified twice.\n"
                        "In addition, the -r optinon must be typed before the directory to"
                        "be scanned.\033[00;00m\n");
                err = 1;
                exit(err);
            }
            else
            {
                err = filterAppContentsInVolumesDirectory(argv[2]);
                exit(err);
            }
        }
    }
    else if(argc >= 4)
    {
        fprintf(stderr, "\033[22;31m You have entered too many parameters.\033[00;00m\n");
        err = 1;
        exit(err);
    }
    fprintf(stdout, "\033[01;32m Done.\033[00;00m\n");
    return err;
}

