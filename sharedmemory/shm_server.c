#include"server.h"
int main()
{
  
  int shmid1,shmid2;
  key_t key1,key2;
   cmd *c1,*c2;
   resp *r1; 
   key1 = 5690;
   key2 = 5691;
   c2 = (cmd *)malloc(sizeof(cmd));
  if( (shmid1 = shmget(key1,SHMSZ,IPC_CREAT | 0666)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (c1 = (cmd *)shmat(shmid1,NULL,0)) == (cmd *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
        
     if( (shmid2 = shmget(key2,SHMSZ,IPC_CREAT | 0666)) < 0 )
       {
         printf("shmget");
         exit(1);
       } 
    
      if ( (r1 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         } 
         
         // while(1)
          //{
          //  strcpy(c1->system_name,"Raj singh");
            //  a1->ant_num =1;
            // fprintf(stderr," Antenna Number is %d\n",a1->ant_num);
              strcpy(c1->system_name,"back_end");
              //fprintf(stderr," system name  %s\n",a1->c1->system_name);
              strcpy(c1->op_name,"set");      
                       c1->number_param=8;

                       strcpy(c1->parameter_name[0],"lo");
                       strcpy(c1->parameter_name[1],"attn");
                       strcpy(c1->parameter_name[2],"filter");
                       strcpy(c1->parameter_name[3],"lpf");
                       strcpy(c1->parameter_name[4],"source");
                       strcpy(c1->parameter_name[5],"ant_ns");
                       strcpy(c1->parameter_name[6],"drct_mxr");
                       strcpy(c1->parameter_name[7],"channel");

                       strcpy(c1->Argument_Ch1[0],"1600000");
                       strcpy(c1->Argument_Ch1[1],"10");
                       strcpy(c1->Argument_Ch1[2],"8");
                       strcpy(c1->Argument_Ch1[3],"0");
                       strcpy(c1->Argument_Ch1[4],"siggen");
                       strcpy(c1->Argument_Ch1[5],"antenna");
                       strcpy(c1->Argument_Ch1[6],"direct");
                       strcpy(c1->Argument_Ch1[7],"1");
    
                       strcpy(c1->Argument_Ch2[0],"1600000"); 
                       strcpy(c1->Argument_Ch2[1],"12");
                       strcpy(c1->Argument_Ch2[2],"6");
                       strcpy(c1->Argument_Ch2[3],"1");
                       strcpy(c1->Argument_Ch2[4],"synthesizer");
                       strcpy(c1->Argument_Ch2[5],"noise");
                       strcpy(c1->Argument_Ch2[6],"mixer");
                       strcpy(c1->Argument_Ch2[7],"2");
                      // fprintf(stderr," Antenna Number is %d\n",a1->ant_num);
           // 
            c2=c1;
           fprintf(stderr," copied from c1 c2->system_name=> %s\n",c2->system_name);
             sleep(10);
            fprintf(stderr," Read on the shared memory segment %s\n",r1->system_name);
           //}
           
              return 0;
}   
       
   
