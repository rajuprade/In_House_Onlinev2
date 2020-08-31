#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
int main()
{
    pid_t pid;
    
     pid=fork();
      if(pid == 0)
        for(;;){
       fprintf(stderr," I m the CHILD ===>\n"); }
       else
        for(;;)
        {
       fprintf(stderr," ######### I m PARENT ===>\n"); }
    return 0;
}
