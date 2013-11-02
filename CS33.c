//MY redirection is implemented only for particular case
//">" must be in second place
//ls -l > a does not work .It will siplay error
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
char error_message[30] = "An error has occurred \n";

int input(char *line,char **argv1,int argc1);
void execute(char **argv1,int len,char *s);
void change_dir(char **argv1);
void commands();
int main (int argc,char *argv[])
{
int argc1,out;
char s[100];
getcwd(s,sizeof(s));
while(1)
{
pid_t pid2;
int status2;
char line[200];
char *argv1[64];
printf("CS33 >");
if(argv[1] != NULL && strcmp(argv[1],"batch") == 0)
{
int fd=open("batch",O_RDONLY | S_IRUSR | S_IWUSR,9080);
dup2(fd,0);
while(1)
{
if(gets(line) == '\0')
exit(0);
printf("\n%s\n",line);
int len=input(line,argv1,argc1);
if(strcmp(argv1[0],"exit") == 0)
  {
  exit(0);
  }
   else if(strcmp(argv1[0],"cd") == 0)
   {
   change_dir(argv1);
   }
    else
    {
    execute(argv1,len,s);
    }
}
dup2(0,fd);
close(fd);
}

else
{
gets(line);
int len=input(line,argv1,argc1);
if(strcmp(argv1[0],"exit") == 0)
  {
  exit(0);
  }
   else if(strcmp(argv1[0],"cd") == 0)
   {
   change_dir(argv1);
   }
    else
    {
    execute(argv1,len,s);
    }
}
}
return 0;
}

int input(char *line, char **argv1,int argc1)
{
argc1 = 0;
//printf("\n%c",*line);
     while (*line != '\0') {  
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';
                       *argv1++ = line;
                ++argc1;
           //printf("%s",argv1);       
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
           {
               line++;
            }
     }
     *argv1 = '\0';
return argc1;
}
void  execute(char **argv1,int len,char *x)
{
char s[300];
 pid_t  pid;
     int status;
        if ((pid = fork()) < 0) {          
          write(STDERR_FILENO, error_message, strlen(error_message));
          exit(0);
     }
     else if (pid == 0) {
    
            
                         
                         if(argv1[1] != NULL && strcmp(argv1[1],">") == 0)
                           {
                           
                          if(argv1[2]!=NULL && len == 3)
                               {
                                 int fd=open(argv1[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR ,909);
                                  dup2(fd,1); 
                                     argv1[1] = NULL; 
                                if (execvp(*argv1, argv1) < 0) {
                                write(STDERR_FILENO, error_message, strlen(error_message)); 
                                exit(0);
                                            }
                                   dup2(1,fd);
                                    close(fd);
                                }
                               else
                               write(STDERR_FILENO, error_message, strlen(error_message)); 
                             }

else
 {
 if(strcmp(*argv1,"pwd")==0)
               {
           char *p=strcat(x,"/mydir/pawd");
               execvp(p,argv1);
                }
              else
              {    
          if (execvp(*argv1, argv1) < 0) {
                   write(STDERR_FILENO, error_message, strlen(error_message)); 
               exit(0);
              }
           }
   }
}
     else {                           
          while (wait(&status) != pid)     
                ;
             }
} 
void change_dir(char **argv1)
{ 
 if(argv1[1] == NULL)
   {
   if(chdir( getenv("HOME") ) < 0 )
    write(STDERR_FILENO, error_message, strlen(error_message));
   }
  else if(strcmp(argv1[1]," ") == 0 || strcmp(argv1[1],"  ") == 0 || strcmp(argv1[1],"~") == 0)
   {
      if(chdir( getenv("HOME") ) < 0)
    write(STDERR_FILENO, error_message, strlen(error_message));
    }
  else
      {
     if(chdir(argv1[1]) < 0)
     write(STDERR_FILENO, error_message, strlen(error_message));
      }
}
