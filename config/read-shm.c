#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ 10000

typedef struct
{
   int mode  ;
   int lta   ;
   double acq_bw;
   int final_bw;
   double edge_freq;
   int chan_max;
   int chan_num;
   int stokes ;
   int control;
   int fstop  ;
   int gaineq ;
   int beam1 ;
   int beam2 ;
   char bblo  ;
   char time ;
   char timestamp[26];
} setgpu;

int main()
{
    int shmid1;
    int i=0,j,k,m,flag=0;
    key_t key1;
    setgpu *gpu;
    key1 = 9100;

    printf("SHM\n");
     if( (shmid1 = shmget(key1,sizeof(setgpu),IPC_CREAT |0777)) < 0 )
     {
         printf("shmget");
         // exit(1);
     }

     if ( (gpu= (setgpu *)shmat(shmid1,NULL,0)) ==(setgpu *)-1)
     {
         printf("shmat");
         //exit(1);
     }
   printf("Shared memory attached\n");

//while(1)   {

    /* printing values ...*/
    fprintf(stderr,"{ Corrsel.def\n");
    fprintf(stderr,"GPU_MODE    = %d               /* 0 - Realtime, 1 - RawDump          */\n",gpu->mode);
    fprintf(stderr,"GPU_LTA     = %d               /* 8 - fixed value                    */\n",gpu->lta);
    fprintf(stderr,"GPU_ACQ_BW  = %lf           /* 16.666666 or 33.333333             */\n",gpu->acq_bw);
    fprintf(stderr,"GPU_FINAL_BW= %d              /* 0,4,8,16,32,64,128 As frac of Nyq, Val = OFF */\n",gpu->final_bw);
    fprintf(stderr,"GPU_EDGE_FRQ= %lf           /* Freq Entry in steps of Nyq, Val = 0 */\n",gpu->edge_freq);
    fprintf(stderr,"GPU_CHAN_MAX= %d            /* 256/512                            */\n",gpu->chan_max);
    fprintf(stderr,"GPU_CHAN_NUM= 0:%d:1           /* any range i:j:1;for i,j<chan_max   */\n",gpu->chan_max-1);
    fprintf(stderr,"GPU_STOKES  = %d               /* 2 Total_Intensity; 4 Full_Stokes   */\n",gpu->stokes);
    fprintf(stderr,"GPU_CNTRL   = %d               /* 0 -LOCAL, 1 -ONLINE, 2 -MANUAL     */\n",gpu->control);
    fprintf(stderr,"GPU_FSTOP   = %d               /* 1 - ON, 0 - OFF                    */\n",gpu->fstop);
    fprintf(stderr,"GPU_BEAM_1  = %d:1           /* 0-OFF,1-IA,2-PA,3-Volt:time res 1=30/2=60 */\n",gpu->beam1);
    fprintf(stderr,"GPU_BEAM_2  = %d:1           /* 0-OFF,1-PA,2-PA,3-Volt:time res 1=30/2=60 */\n",gpu->beam2);
    fprintf(stderr,"GPU_GAINEQ  = %d               /* 1 - ON, 0 - OFF                    */\n",gpu->gaineq);
    fprintf(stderr,"GPU_BB_LO   = 149000000.0:156000000.0          /* 32-149:156,16 -138:167,6-133:172   */\n",gpu->bblo);
    fprintf(stderr,"}Corrsel\n");
    fprintf(stderr,"*\n");
    fprintf(stderr,"END_OF_HEADER                    /*  VERSION RELEASED */\n");

    fprintf(stderr," Timestamp=> %s\n",gpu->timestamp);
    //fprintf(stderr," Timestamp=> %s",ctime(t1));

//     sleep(5);  }
     return 0;
}
