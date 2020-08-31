#include"user1.h"
 
//when using gcc compiler you need to "gcc -lm main.c" in order to link it to the math library//
 
// Opens the file and reads in the stream //

write_shm(setdata *set)
{
  int shmid1;
  int i=0,j,k,m,flag=0;
  key_t key1;
   setdata *c1;
  // printf("I am in shm\n");
   key1 = 9100;
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
       fprintf(stderr,"usernb is %d\n",c1->Tx[i].usernb);
        for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"Sub ARRAy Number %d\n",c1->Tx[i].s_a[k].sub_num);
           
           fprintf(stderr,"The Antenna names in your sub Array\n");
           for(j=0;j<c1->Tx[i].s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\n",c1->Tx[i].s_a[k].ant_name[j]);
           }
             
         } 
       
     fprintf(stderr," Timestamp=> %s\n",c1->Tx[i].timestamp);
 
     } 
    shmdt(c1);      
}


void load_data(char fname[200])
{
   
   setdata *set;  
   set = (setdata *)malloc(sizeof(setdata));
   time_t *t1;
  /*  for(i=0;i<MAX_LOOP;i++)
   {
    set->Tx[i] = (user *)malloc(sizeof(user));
    } */
    t1 = (time_t *)malloc((time_t)sizeof(time_t));
   time(t1);
   int user_number[4];//declare array (random number)
   int sub_array[4];
   int j,i,number_of_ant[10]; 
   char ant_name[10][10],name[10];
   int num;
   char ch, file_name[25];
    int bytes_read;
    int nbytes = 100;
    char *my_string;
    char buffer[20];
    my_string = (char *) malloc (nbytes + 1); 
  FILE *fp = fopen(fname, "r");
  FILE *fp2 = fopen("/home/raj/Desktop/Ant_sel/Results", "w"); //opens up a file called "Results"
                                                           // and allows writing//
     
    if (fp == NULL) //checks for the file
    { printf("\n Can’t open %s\n",fname);
        exit;
    }   
 
//reads in the data to an array, analyzes, and the prints the array
 
   while( ( ch = fgetc(fp) ) != EOF )
    {
     if(ch =='#')
      {
        bytes_read = getline (&my_string, &nbytes,fp);
        bzero(my_string,(nbytes+1));
       }
      else
        {
           {
                 // printf("%c",ch);
                  fprintf(fp2,"%c",ch);
                  printf("%s",buffer);
                  bzero(buffer,20);
              }
              
          }  
       } 
      fclose(fp2);
      FILE *f3 = fopen("/home/raj/Desktop/Ant_sel/Results", "r");    
              for(j =0; j < 1; j++) //repeats for max number of columns
              {   
                 for(i=0;i<1;i++)
                 {
                  fscanf(f3, "%d", &num);
                  // user_number[i] = num;
                     set->Tx[i].usernb=num;
                  //fprintf(stderr,"User number is %d\n",user_number[i]);
                    fprintf(stderr,"User number is %d\n",set->Tx[i].usernb);
                 }
               }    
              for(j = 1; j < 2; j++) //repeats for max number of columns
               { 
                  for(i=0;i<1;i++)
                 {  
                   fscanf(f3, "%d", &num);
                  /* sub_array[i] = num;
                   fprintf(stderr,"sub array is %d\n",sub_array[i]);*/
                    set->Tx[i].s_a[i].sub_num=num;
                    fprintf(stderr,"sub array is %d\n",set->Tx[i].s_a[i].sub_num);
                  } 
                }   
             for(j = 2; j < 3; j++) //repeats for max number of columns
                {  
                    for(i=0;i<1;i++)
                   {   
                     fscanf(f3, "%d", &num);
                    /* number_of_ant[i]= num;
                     fprintf(stderr," Number of Antenna is %d\n",number_of_ant[i]);*/
                     set->Tx[i].s_a[i].num_in_sub=num;
                     fprintf(stderr," Number of Antenna is %d\n",set->Tx[i].s_a[i].num_in_sub);
                   }
                 }   
              for(j = 3; j < 4; j++) //repeats for max number of columns
                    {   
                       for(i=0;i<4;i++)
                       {
                         fscanf(f3, "%s", name);
                         /*strcpy(ant_name[i],name);
                        fprintf(stderr," Name of antenna is Ant_name[%d]=>%s\n",i,ant_name[i]); */
                         strcpy(set->Tx[0].s_a[0].ant_name[i],name);
                          fprintf(stderr," Name of antenna is Ant_name[%d]=>%s\n",i,set->Tx[0].s_a[0].ant_name[i]);
                      }
                    } 
           write_shm(set);
/*for(j = 0; j < 5; j++) //repeats for max number of columns
  {
    for (i=0; i< 7; i++)
      { num = data[i][j];
    fprintf(fp2, "%d ", num);
      }
    fprintf(fp2, "\n");
  }*/
 
// add in laterz fprintf(fp2,"%f%f", radius, velocity);//
                 
   fclose(f3);
   fclose(fp);
}
 
 
 
//Main Function //
     
    int main (void)
    {
        char path[200], basename[200], input_fname[200]; 
        // Stores path & basename of file, input_fname: combines path and basename//
        char str[50] = {0}; //stores filename
         
        printf("please input the file name: ");
        scanf("%s", str); // gets input from user, %s reads characters, variable i//
          
        sprintf(path, "/home/raj/Desktop/Ant_sel"); //Change pathway as needed //
        snprintf(basename, 50, "%s", str); // stores basename from i//
        sprintf (input_fname, "%s/%s", path, basename); //combines path and basename to get input_fname//
         
        printf("Using file: %s\n", input_fname); //tells user which file is being used
 
        load_data(input_fname); //function to load input data //
         
                    
                        
        return 0;
    }