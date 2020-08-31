/* A simple server in the internet domain using TCP
   demonstrating how to send structure over sockets ******/
#include"server1.h"

int readable_timeo(int fd, int sec)
{
     fd_set rset;
     struct timeval tv;

      FD_ZERO(&rset);
      FD_SET(fd, &rset);

      tv.tv_sec = sec;
     tv.tv_usec = 0;

     return (select(fd + 1, &rset, NULL, NULL, &tv));
        /* > 0 if descriptor is readable */
}

/***** TIMESTAMP function ****/

char* tp(char *tstamp)
{
 char stamp1[26], stamp2[21];
 time_t t1;
   time(&t1);
   ctime_r(&t1, stamp1);
 //  fprintf(stderr,"%s\n",stamp1);
   stamp2[0] = stamp1[8];
   stamp2[1] = stamp1[9];
   stamp2[2] = '-';
   stamp2[3] = stamp1[4]; 
   stamp2[4] = stamp1[5]; 
   stamp2[5] = stamp1[6];
   stamp2[6] = '-'; 
   stamp2[7] = stamp1[20];
   stamp2[8] = stamp1[21];
   stamp2[9] = stamp1[22];
   stamp2[10] = stamp1[23];
   stamp2[11]= ' ';
   stamp2[12] = stamp1[11];
   stamp2[13] = stamp1[12];
   stamp2[14] = stamp1[13];
   stamp2[15] = stamp1[14];
   stamp2[16] = stamp1[15];
   stamp2[17] = stamp1[16];
   stamp2[18] = stamp1[17];
   stamp2[19] = stamp1[18];
   stamp2[20] = '\0'; 
   strcpy(tstamp,stamp2);
 // fprintf(stderr,"%s\n",stamp2);
  return (tstamp);
}
/******TIMESTAMP function ****/

/******* Sentinel *******/
void sentinel(cmd *c1)
{
   int op;
   char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);
  // strcpy(c1->timestamp,stamp1);
   strcpy(c1->system_name,"sentinel");
    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;
      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=1;
               strcpy(c1->parameter_name[0],"dmask");
               strcpy(c1->Argument_Ch1[0],"ffff");
               strcpy(c1->Argument_Ch2[0],"5555"); 
               break;
      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");
               c1->number_param=0;
               break;
      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/*********** sentinel ******/


/******* fiber_optics *******/
void fiber_optics(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
    char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);
   strcpy(c1->system_name,"fiber_optics");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=1;
               strcpy(c1->parameter_name[0],"rf_attn");
               strcpy(c1->Argument_Ch1[0],"25");
               strcpy(c1->Argument_Ch2[0],"35"); 
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/************** fiber_optics *****/

/******* back_end *******/
void back_end(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
   char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);
   strcpy(c1->system_name,"back_end");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
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
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/************** back_end *****/

/******* front_end *******/
void front_end(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
    char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);
   strcpy(c1->system_name,"front_end");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=7;

                       strcpy(c1->parameter_name[0],"cal_ns");
                       strcpy(c1->parameter_name[1],"rf");
                       strcpy(c1->parameter_name[2],"filter");
                       strcpy(c1->parameter_name[3],"fltr_bnd");
                       strcpy(c1->parameter_name[4],"band_sel");
                       strcpy(c1->parameter_name[5],"slr_attn");
                       strcpy(c1->parameter_name[6],"channel");

                       strcpy(c1->Argument_Ch1[0],"LO");
                       strcpy(c1->Argument_Ch1[1],"on");
                       strcpy(c1->Argument_Ch1[2],"1");
                       strcpy(c1->Argument_Ch1[3],"1060");
                       strcpy(c1->Argument_Ch1[4],"50");
                       strcpy(c1->Argument_Ch1[5],"44");
                       strcpy(c1->Argument_Ch1[6],"swap");
                       
    
                       strcpy(c1->Argument_Ch2[0],"Medium"); 
                       strcpy(c1->Argument_Ch2[1],"off");
                       strcpy(c1->Argument_Ch2[2],"4");
                       strcpy(c1->Argument_Ch2[3],"1170");
                       strcpy(c1->Argument_Ch2[4],"150");
                       strcpy(c1->Argument_Ch2[5],"30");
                       strcpy(c1->Argument_Ch2[6],"unswap");
                      
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/************** front_end *****/

/***************self_test **********/
void self_test(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
    char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);
   strcpy(c1->system_name,"self_test");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=3;
               strcpy(c1->parameter_name[0],"ss");// set spectrum spreader
               strcpy(c1->Argument_Ch1[0],"0");   // Range : 0,1,2,3
               strcpy(c1->parameter_name[1],"fdb");// set frequency doubler
               strcpy(c1->Argument_Ch1[1],"1");   // Range 0 or 1 
               strcpy(c1->parameter_name[2],"fdv");// set frequency divider
               strcpy(c1->Argument_Ch1[2],"2");   // Range 1,2,4,6,8   
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}


/**************self_test **********/

/* exec_cmd() *****/

void exec_cmd(int n,cmd *c1)
{

   switch(n)
   { 
     case 0:sentinel(c1); break;
     case 1:front_end(c1); break;
     case 2:fiber_optics(c1); break;
     case 3:back_end(c1); break;
     case 4:self_test(c1); break;
     default: break;
   }
}

printcmd(cmd *c1)
{
   int i;
        printf("we wrote on the socket %d %s %s %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("%s %s %s\n",c1->parameter_name[i],c1->Argument_Ch1[i],c1->Argument_Ch2[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
}

printresp(resp *r1)
{
   int i;
   printf(" Size of Response Struct is ######## %d\n",sizeof(resp));
         printf("$$$$$$$$$$$$$$$$$ got from Client\n");
         printf("##############Response Message from MCM setting##########\n %d\n %d\n %s\n %s\n ",r1->response_type,r1->seq,r1->timestamp,r1->system_name,r1->Mon_sum[0]);
 
         for(i=0; i<32;i++)
          {
             printf("%s ",r1->Mon_sum[i]);
          }
 
        for(i=0; i<64;i++)
          {
             printf("%s ",r1->Mon_raw[i]);
          }
        
        for(i=0; i<r1->num_resp_msg;i++)
          {
            printf(" %s\n",r1->response_message[i]);
          }

}
/*********exec_cmd() ******/

/* Write-Read ****/
void write_read(int newsockfd,cmd *c1, resp *r1)
{
      
         write(newsockfd,c1,sizeof(cmd));
         printcmd(c1);
         sleep(2);
         if (readable_timeo(newsockfd, 5) == 0)
          {
               fprintf(stderr, "socket timeout\n");
               close(newsockfd);
         }
       else 
          {
             read(newsockfd,r1,sizeof(resp));
             printresp(r1);
          }

}

/************************write_read*****************/

int main(int argc, char *argv[])
{
       int n;
       cmd *c1;
       c1 = malloc(sizeof(cmd));
       resp *r1;
       r1 = malloc(sizeof(resp));

      int sockfd, newsockfd,yes=1,i=0;
      socklen_t clilen;
      struct sockaddr_in serv_addr, cli_addr;
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
       fprintf(stderr,"ERROR opening socket\n");
    if(setsockopt(sockfd, SOL_SOCKET , SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
          error(" Error\n");
    } 
     bzero((char *) &serv_addr, sizeof(serv_addr));
    // portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);

     if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
              { 
               fprintf(stderr,"ERROR binding socket\n");
              }

     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");
      newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
  
    for(;;)
      {
        printf("\n\nEnter the system number from the list\n");
        printf("0.sentinal\n");
        printf("1.front_end\n");
        printf("2:fiber_optics\n");
        printf("3:back_end\n");
        printf("4:self_test\n\n");                                                  
        scanf("%d",&n); 
        exec_cmd(n,c1);
     /*   fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");
          newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); */
        write_read(newsockfd,c1,r1);
      //  close(newsockfd);
      }                          
                                     
      return 0; 
}
