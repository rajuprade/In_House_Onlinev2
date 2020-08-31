#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SHMSZ 100

main()
{
  char c;
  int shmid;
  key_t key;
  char *shm, *s;
  
  //v vl name our shared  memory segment 5678
   
   key = 5680;
   

 // int shmget (key_t key,size_t size,int shmflg);
  if( (shmid = shmget(key,SHMSZ,IPC_CREAT | 0666)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
   
   //void *shmat(int shmid,const void * shmaddr,int shmflg)
   //int shmdt(const void * shmaddr)
       if ( (shm = shmat(shmid,NULL,0)) == (char *) -1)
   //using shmat with shmaddr equal to NULL is the preferred ,portable way of attaching memory segment.
   //if shmaddr is NULL ,the system chooses a suitable (unused) address at which to attach the segment.
         {
           printf("shmat");
           exit(1);
         }
        //  s = shm;
          s = " Raj singh";
          
            strcpy(shm,s);
          fprintf(stderr," We wrote on the shared memory %s\n",shm);
              s = " Sheetal singh";
            strcpy(shm,s);
            while (*shm != '*')
             sleep(1);
             exit(0);
}   
       
   
