#include<stdio.h>
#include<malloc.h>
#include<time.h>

static char at_name[32][8] = {"C00","C01","C02","C03","C04","C05","C06","C08","C10","C11","C12","C13","C00","C14","E02"
           ,"E03","E04","E05","E06","S01","S02","S03","S04","S06","W01","W02","W03","W04","W05","W06"}; 
typedef struct
{
  int usernb;
  int sub_array;
  int num_in_sub;
  char ant_name[32][8];
  char timestamp[26];
  char system_name[20];
  char operation_name[20];
} MSG;

int main()
{
  int i=0,j,flag=0;
   MSG *Tx[4];  
   time_t *t1;
   
   for(i=0;i<4;i++)
   {
    Tx[i] = (MSG *)malloc(sizeof(MSG));
    }
   t1 = (time_t *)malloc((time_t)sizeof(time_t));
   time(t1);
   
    i=0;

   //for(i=0;i<4;i++)
         /* if(flag) 
      {
        //j=1;
       printf(" Value Of I is ****** [%d] *******\n",i);
       }
     else 
      {i=0;
       printf(" Value Of I is ****** [%d] *******\n",i); } */
  
  
   printf("Enter the user number for observation\n");
   scanf("%d",&Tx[0]->usernb);
  /* if(i)
       if(!(Tx[i]->usernb==Tx[--i]->usernb))
          fprintf(stderr,"Kindly Enter some another user number\n"); */
   printf("Create sub array number for observation\n");
   scanf("%d",&Tx[0]->sub_array);
   
   fprintf(stderr," You entered ******* %d ****** user number\n",Tx[i]->usernb);
   fprintf(stderr," You entered ******* %d ****** Created Sub array\n",Tx[i]->sub_array);

    printf("Enter number of Antenna You want in your sub array  for observation\n");
   scanf("%d",&Tx[0]->num_in_sub);
   printf(" ####### Number of antenna in sub array is %d\n",Tx[0]->num_in_sub);
   printf("Enter the Antenna names which you want in your sub Array\n");
 
    for(i=0;i<Tx[0]->num_in_sub;i++)
    {
      scanf("%s",Tx[0]->ant_name[i]);
    }
   ctime_r(t1,Tx[0]->timestamp);
   printf("Enter the system name which you want to communicate\n");
   scanf("%s",Tx[0]->system_name);
   printf("Enter the operation name which you want to communicate\n");
    scanf("%s",Tx[0]->operation_name);
  

   
    for(i=0;i<Tx[0]->num_in_sub;i++)
     {
       fprintf(stderr," You entered ******* %s ****** antenna for communication\n",Tx[0]->ant_name[i]);
     }
  fprintf(stderr," Timestamp s ******* %s ******\n",Tx[0]->timestamp);
  fprintf(stderr," You entered ******* %s ******* system for communication\n",Tx[0]->system_name);
  fprintf(stderr," You entered ********%s ******* operation name\n",Tx[0]->operation_name);
   //i--;

  /* printf("Do you want to enter again: 1=> YES 0=>NO\n");
   scanf("%d",&flag);
   if(flag)
          continue;
     else break; */
   

  return 0;
}
