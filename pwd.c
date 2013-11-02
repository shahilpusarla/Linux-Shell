#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
char cwd[256];
if((getcwd(cwd,sizeof(cwd))) != NULL)
printf("The current Working directory is %s\n",cwd);
exit(0);
return 0;
}
