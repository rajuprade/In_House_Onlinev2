#include<stdio.h>

int main()
{
   int i = 10,j=0;
   
   for(j=1;j<20;j++)
   {
     printf("%d\n",j);
      if(j==i)
       {
         printf("%d %d\n",i,j);
         break;
        }
      printf("I am in for loop\n");
     }

    printf("I am outside for loop\n");
     return 0;
}
   

   
