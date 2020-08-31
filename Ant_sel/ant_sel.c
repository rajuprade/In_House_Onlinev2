#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#define MAX_LOOP 2
#define MAX_ANT 4

static char at_name[32][8] = {"C00","C01","C02","C03","C04","C05","C06","C08","C10","C11","C12","C13","C00","C14","E02"
           ,"E03","E04","E05","E06","S01","S02","S03","S04","S06","W01","W02","W03","W04","W05","W06"}; 
typedef struct
{
  int usernb;
  int sub_array[4];
  int num_in_sub;
  char ant_name[32][8];
  char system_name[20];
  char operation_name[20];
  char timestamp[26];
} MSG;

int main()
{
  int i=0,j,k,flag=0;
   MSG *Tx[4];  
   time_t *t1;
   
   for(i=0;i<MAX_LOOP;i++)
   {
    Tx[i] = (MSG *)malloc(sizeof(MSG));
    }
   t1 = (time_t *)malloc((time_t)sizeof(time_t));
   time(t1);
   
   
   // LOOP for taking USER INPUT 
  for(i=0;i<MAX_LOOP;i++)
  {
   printf("Enter the user number for observation\n");
   scanf("%d",&Tx[i]->usernb);
       
   printf("Create sub array number for observation\n");
   scanf("%d",&Tx[i]->sub_array[i]); 
   
   printf("Enter number of Antenna You want in your sub array  for observation\n");
   scanf("%d",&Tx[i]->num_in_sub); 
   printf("Enter the Antenna names which you want in your sub Array\n");
 
    for(j=0;j<Tx[i]->num_in_sub;j++)
    {
      scanf("%s",Tx[i]->ant_name[j]);
    }
             
 printf("Enter the system name which you want to communicate\n");
   scanf("%s",Tx[i]->system_name);
   printf("Enter the operation name which you want to communicate\n");
    scanf("%s",Tx[i]->operation_name); 
  } 

  // LOOP for Checking duplicate Antenna name 

       for(i=0;i<MAX_LOOP;i++)
       {
            for(j=0;j<MAX_ANT;j++)
              {
                for(k=0;k<MAX_ANT;k++)
                {
                 if((strcmp(Tx[i]->ant_name[j],Tx[i-1]->ant_name[k]))==0)
                 { // fprintf(stderr," DUPLICATE ENRTY OF ANTENNA\n");
                    fprintf(stderr,"DULICATE Antenna is %s You can not take this Antennas for your observation\n",Tx[i]->ant_name[j]);
                 }
                }
               /* else
                fprintf(stderr,"*********NO DUPLICATE ENRTY OF ANTENNA\n"); */
              }  
       }

     // LOOP for priting USER INPUT 
    for(i=0;i<MAX_LOOP;i++)
    {
      fprintf(stderr,"The user number for observation =>%d\n",Tx[i]->usernb);
      fprintf(stderr,"sub array number for observation=>%d\n",Tx[i]->sub_array[i]);
   
    fprintf(stderr,"The Antenna names sub Array\n");
 
     for(j=0;j<Tx[i]->num_in_sub;j++)
      {
        fprintf(stderr,"%s\n",Tx[i]->ant_name[j]);
      }
   fprintf(stderr,"\n\nThe system name for communicate=>%s\n",Tx[i]->system_name);
   fprintf(stderr,"The operation name =>%s\n",Tx[i]->operation_name);
    ctime_r(t1,Tx[i]->timestamp);
    fprintf(stderr," Timestamp=> %s\n",Tx[i]->timestamp);
  } 
  

  return 0;
}
