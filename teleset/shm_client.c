/*
 * shm-client - client program to demonstrate shared memory.
 */

#include"shm.h"
#include"user1.h"
printcmd(cmd *c1)
{
   int i;

       printf("===============================================================================================\n");
       printf("***********************************TELEDISP*******************************************************\n");
       printf("===============================================================================================\n");
       printf("############################ COMMAND SENT FROM SERVER #################\n\n");
       printf("===============================================================================================\n");
       printf("SEQ => %d\t TIMESTAMP =>%s\t SYSTEM NAME => %s\t OPERATION NAME=> %s\n\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("PARAMETER NAME=> %s\tARGUMENT CH1=> %s\tARGUMENT CH2=> %s\n\n",c1->parameter_name[i],c1->Argument_Ch1[i],c1->Argument_Ch2[i]);
        } 
       printf("===============================================================================================\n\n");
       // printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
}

printresp(resp *r1)
{
   int i;
 //  printf(" Size of Response Struct is ######## %d\n",sizeof(resp));
 //        printf("$$$$$$$$$$$$$$$$$ got from Client\n");
         printf("\n===============================================================================================\n");
         printf("######################### RESPONSE RECIEVED ROM CLIENT #################\n\n");
         printf("===============================================================================================\n");
         printf("RESPONSE TYPE => %d\nSEQUENCE=> %d\nTIMESTAMP=> %s\nSYSTEM NAME=> %s\n",r1->response_type,r1->seq,r1->timestamp,r1->system_name);
          printf("===============================================================================================\n"); 
          printf("##########################MONITORING SUMMARY###############################\n");
          printf("===============================================================================================\n");
         for(i=0; i<32;i++)
          {
             printf("%s\t",r1->Mon_sum[i]);
          }
 
          printf("\n===============================================================================================\n"); 
          printf("\n###################################   MONITORING RAW ##########################################\n");
          printf("\n==================================================================================================================\n");
        for(i=0; i<64;i++)
          {
             printf("%s\t",r1->Mon_raw[i]);
          }
          printf("\n==============================================================================================================\n"); 
          printf("################################### RESPONSE MESSAGES FROM MCM  ###############################\n");
          printf("\n===============================================================================================\n");
         for(i=0; i<r1->num_resp_msg;i++)
          {
            printf("RESPONSE MESSAGES FROM MCM=> %s\n",r1->response_message[i]);
          }
        printf("\n===============================================================================================\n");
}
int main()
{
    int shmid1,shmid2, shmid3;;
    key_t key1,key2,key3;
     int i=0,j,k,m,flag=0;
      cmd *c2,*c1;
      resp *r2,*r1;
       setdata *s1;
      
      c1 = (cmd *)malloc(sizeof(cmd));
      r1 = (resp *)malloc(sizeof(resp));
      key1 = 5800;
      key2 = 5801;
      key3 = 9100; 
   
   if ((shmid1 = shmget(key1, SHMSZ1,0777)) < 0) {
        perror("shmget");
        exit(1);
    }

   /*  if ((shmid1 = shmget(key1,0,0)) < 0) {
        printf("shmget");
        exit(1);
    }*/

    if ((c2 =(cmd *) shmat(shmid1,NULL, 0)) == (cmd *) -1) {
        printf("shmat");
        exit(1);
    }
    
   if( (shmid2 = shmget(key2,SHMSZ2,0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }

       /* if( (shmid2 = shmget(key2,0,0)) < 0 )
       {
         printf("shmget");
         exit(1);
       } */
       if ( (r2 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }

     printf("SHM\n");
     if( (shmid3 = shmget(key3,sizeof(setdata),IPC_CREAT |0777)) < 0 )
       {
         printf("shmget");
        // exit(1);
       }
   
       if ( (s1= (setdata *)shmat(shmid3,NULL,0)) ==(setdata *)-1)
            {
               printf("shmat");
               //exit(1);
            }
        // strcpy(c2->system_name,"RAJ SINGH");
        // fprintf(stderr," Read on the shared memory segment %s\n",c2->system_name);
        //  fprintf(stderr," Read on the shared memory segment %s\n",r2->system_name);
       /* c1= c2;
        r1=r2; */
       while(1)
       {
            printf("================================================================================\n");
            printf("\t\t\tUSER INOFRAMTION OF ONLINE PROGRAM\n");
    //  printf("=======================================================================\n");
       for(i=0;i<MAX_LOOP;i++)
       {
           // printf("InISIED  FOR LOOP Shared memory attached\n"); 
         printf("=============================================================================\n");
       fprintf(stderr,"\tUSER NUMBER =>%d\t\t",s1->Tx[i].usernb);
       fprintf(stderr,"Timestamp=>%s\n",s1->Tx[i].timestamp);
       printf("=============================================================================\n");
     //   printf("Shared memory attached\n");
        for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"SUB ARRAY NUMBER=>%d\t\t",s1->Tx[i].s_a[k].sub_num);
             
           fprintf(stderr,"SELECTED ANTENNA=>");
           for(j=0;j<s1->Tx[i].s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\t",s1->Tx[i].s_a[k].ant_name[j]);
           }
    printf("\n==============================================================================\n");          
         } 
     
   //  fprintf(stderr," Timestamp=> %s\n",c1->Tx[i].timestamp);
 
    }

         
          printresp(r2);
         //sleep(2);
        // printcmd(c2);
         sleep(2);
        // printresp(r2);
         printcmd(c2);
       }
        
       /*  while(1)
        {
          fprintf(stderr," Read on the shared memory segment %s\n",c2->system_name);
          fprintf(stderr," Read on the shared memory segment %s\n",r2->system_name);
        }*/ 

         
        
       
      return 0;
}
