/*
 * shm-client - client program to demonstrate shared memory.
 */

#include"server.h"


int main()
{
    int shmid1,shmid2,i;
    key_t key1,key2;
 
      cmd *c2;
      resp *r1;
      key1 = 5690;
      key2 = 5691; 
   
    if ((shmid1 = shmget(key1, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

   
    if ((c2 =(cmd *) shmat(shmid1, NULL, 0)) == (cmd *) -1) {
        perror("shmat");
        exit(1);
    }
    
      if( (shmid2 = shmget(key2,SHMSZ,0666)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (r1 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
          
          printf("we wrote on the socket %d %s %s %s\n",c2->seq,c2->timestamp,c2->system_name,c2->op_name);
       
        for(i=0;i<c2->number_param;i++)
        {
          printf("%s %s %s\n",c2->parameter_name[i],c2->Argument_Ch1[i],c2->Argument_Ch2[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
        // while(1)
        // {
          fprintf(stderr," Read on the shared memory segment %s\n",c2->system_name);
          sleep(10);
          strcpy(r1->system_name,"Sheetal singh");
         //}
        
       
      return 0;
}
