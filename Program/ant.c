#include<stdio.h>
#include<malloc.h>
#include<time.h>

typedef struct
{
  char ant_name[20];
  char timestamp[26];
  char system_name[20];
  char operation_name[20];
} MSG;

int main()
{
   MSG *Tx;  
   time_t *t1;
   Tx = (MSG *)malloc(sizeof(MSG));
   t1 = (time_t *)malloc((time_t)sizeof(time_t));
   time(t1);
   printf("Enter the Antenna name which you want to communicate\n");
   scanf("%s",Tx->ant_name);
   ctime_r(t1,Tx->timestamp);
   printf("Enter the system name which you want to communicate\n");
   scanf("%s",Tx->system_name);
   printf("Enter the operation name which you want to communicate\n");
    scanf("%s",Tx->operation_name);
  #ifdef DEBUG
  fprintf(stderr," You entered ******* %s ****** antenna for communication\n",Tx->ant_name);
  fprintf(stderr," Timestamp s ******* %s ******\n",Tx->timestamp);
  fprintf(stderr," You entered ******* %s ******* system for communication\n",Tx->system_name);
  fprintf(stderr," You entered ********%s ******* operation name\n",Tx->operation_name);
  #endif
  return 0;
}
