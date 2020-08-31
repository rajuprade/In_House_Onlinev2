#include"user.h"

write_shm(setdata *set)
{
  int shmid1;
  int i=0,j,k,m,flag=0;
  key_t key1;
   setdata *c1;
  // printf("I am in shm\n");
   key1 = 9001;
     if( (shmid1 = shmget(key1,sizeof(setdata),IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
        // exit(1);
       }
    
       if ( (c1 = (setdata *)shmat(shmid1,NULL,0)) ==(setdata *)-1)
            {
           printf("shmat");
           //exit(1);
         }
      memcpy(c1,set,sizeof(setdata));
      //  c1= set;
     // sleep(30);
      fprintf(stderr,"successfully copied in SHM\n");
  
      for(i=0;i<MAX_LOOP;i++)
     {
       fprintf(stderr,"usernb is %d\n",c1->Tx[i]->usernb);
        for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"Sub ARRAy Number %d\n",c1->Tx[i]->s_a[k].sub_num);
           
           fprintf(stderr,"The Antenna names in your sub Array\n");
           for(j=0;j<c1->Tx[i]->s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\n",c1->Tx[i]->s_a[k].ant_name[j]);
           }
             
         } 
       
     fprintf(stderr," Timestamp=> %s\n",c1->Tx[i]->timestamp);
 
     } 
    //shmdt(c1);      
}

int main()
{
  int i=0,j,k,m,flag=0;
   setdata *set;  
   set = (setdata *)malloc(sizeof(setdata));
   time_t *t1;
    for(i=0;i<MAX_LOOP;i++)
   {
    set->Tx[i] = (user *)malloc(sizeof(user));
    } 
    t1 = (time_t *)malloc((time_t)sizeof(time_t));
   time(t1);
   
   
   // LOOP for taking USER INPUT 
  for(i=0;i<MAX_LOOP;i++)
  {
     printf("Enter usernb\n");
     scanf("%d",&set->Tx[i]->usernb); 
    for(k=0;k<MAX_LOOP;k++)
    {
      printf("Enter Sub ARRAy Number\n");
      scanf("%d",&set->Tx[i]->s_a[k].sub_num); 
      printf("Enter number of Antenna You want in your sub array  for observation\n");
      scanf("%d",&set->Tx[i]->s_a[k].num_in_sub); 
      printf("Enter the Antenna names which you want in your sub Array\n");
        for(j=0;j<set->Tx[i]->s_a[k].num_in_sub;j++)
       {
         scanf("%s",set->Tx[i]->s_a[k].ant_name[j]);
       }
             
   }
   ctime_r(t1,set->Tx[i]->timestamp); 
  // fprintf(stderr," Timestamp=> %s\n",set->Tx[i]->timestamp);
 }
write_shm(set);
  // LOOP for Checking duplicate Antenna name 

   /*   for(i=0;i<MAX_LOOP;i++)
       {
            for(m=0;m<MAX_LOOP;m++)
            {
              for(j=0;j<MAX_ANT;j++)
                {
                   for(k=0;k<MAX_ANT;k++)
                   {
                    if((strcmp(set->Tx[i]->s_a[m].ant_name[j],set->Tx[i]->s_a[m+1].ant_name[k]))==0)
                     { 
                        fprintf(stderr,"DULICATE Antenna is sub array %s\n",set->Tx[i]->s_a[m].ant_name[j]);
                      }
                    }
                  } 
               } 
           } */

     // LOOP for priting USER INPUT 

    
 /*   for(i=0;i<MAX_LOOP;i++)
   {
     fprintf(stderr,"usernb is %d\n",set.Tx[i]->usernb);
       for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"Sub ARRAy Number %d\n",set.Tx[i]->s_a[k].sub_num);
           
           fprintf(stderr,"The Antenna names in your sub Array\n");
           for(j=0;j<set.Tx[i]->s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\n",set.Tx[i]->s_a[k].ant_name[j]);
           }
             
         } 
  
     
     fprintf(stderr," Timestamp=> %s\n",set.Tx[i]->timestamp);
 
    }*/

  return 0;
}
