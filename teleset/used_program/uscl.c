/*
 * shm-client - client program to demonstrate shared memory.
 */

#include"user1.h"


int main()
{
    int shmid1;
    int i=0,j,k,m,flag=0;
    key_t key1;
    setdata *c1;
    key1 = 9100;
    printf("SHM\n");
     if( (shmid1 = shmget(key1,sizeof(setdata),IPC_CREAT |0777)) < 0 )
       {
         printf("shmget");
        // exit(1);
       }
   
       if ( (c1= (setdata *)shmat(shmid1,NULL,0)) ==(setdata *)-1)
            {
               printf("shmat");
               //exit(1);
            }
    // c1 = (setdata *)malloc(sizeof(setdata));
     /* for(i=0;i<MAX_LOOP;i++)
       {
         c1->Tx[i] = (user *)malloc(sizeof(user));
       } */
     /* for(i=0;i<MAX_LOOP;i++)
       {
          if ( (c1->Tx[i]= (user *)shmat(shmid1,NULL,0)) ==(user *)-1)
            {
              printf("shmat");
          
            }
       } */
    //  memcpy(c1,c1,sizeof(setdata));
      
  // printf("Shared memory attached\n");

while(1)
  {
     sleep(2);
   // fprintf(stderr,"usernb is %d\n",c1->Tx[0]->usernb);
    printf("================================================================================\n");
    printf("\t\t\tUSER INOFRAMTION OF ONLINE PROGRAM\n");
  //  printf("=======================================================================\n");
     for(i=0;i<MAX_LOOP;i++)
     {
       // printf("InISIED  FOR LOOP Shared memory attached\n"); 
       printf("=============================================================================\n");
       fprintf(stderr,"\tUSER NUMBER =>%d\t\t",c1->Tx[i].usernb);
       fprintf(stderr,"Timestamp=>%s\n",c1->Tx[i].timestamp);
       printf("=============================================================================\n");
     //   printf("Shared memory attached\n");
        for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"SUB ARRAY NUMBER=>%d\t\t",c1->Tx[i].s_a[k].sub_num);
             
           fprintf(stderr,"SELECTED ANTENNA=>");
           for(j=0;j<c1->Tx[i].s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\t",c1->Tx[i].s_a[k].ant_name[j]);
           }
    printf("\n==============================================================================\n");          
         } 
     
   //  fprintf(stderr," Timestamp=> %s\n",c1->Tx[i].timestamp);
 
    }
 } 
       
      return 0;
}
