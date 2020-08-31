/* A simple server in the internet domain using TCP
   demonstrating how to send structure over sockets ******/
#include"server.h"
int main(int argc, char *argv[])
{
     int sockfd, newsockfd,n,yes=1,i=0;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     char argname[32][32],stamp1[26];
     time_t t1;
     char buffer[100];
      cmd *c1;
      c1 = malloc(sizeof(cmd));
      resp *r1;
      r1 = malloc(sizeof(resp));

    /* printf("Enter CH1 bandwidth\n");
     scanf("%s", &argdata); */
     printf("Enter system name:sentinal/front_end/fibre_optics/back_end/test_sys\n");
     scanf("%s", &argname[0]);
     printf(" Enter operation name which you want to perform on system: set/mon/init/reset\n");
     scanf("%s", &argname[1]);

    
     c1->seq= 10;

 /******* BACK END CONTRAOl and Monitor start Here *****************************/
  
    if(!strcmp(argname[0],"back_end"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
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
                 }
             else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
 /******* BACK END CONTRAOl and Monitor end Here *****************************/        
 
/**********************FRONT END CONTROL AND MONITOR START HERE ******************/

else if(!strcmp(argname[0],"front_end"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
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
                      
                 }
            else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
/********************* fRONT END CONTROL AND MONITOR END HERE ********************/ 

/*********************Sentinal control and monitor start here ********************/
else if(!strcmp(argname[0],"sentinel"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
                       strcpy(c1->op_name,"set");      
                       c1->number_param=1;
                       strcpy(c1->parameter_name[0],"dmask");
                       strcpy(c1->Argument_Ch1[0],"ffff");
                       strcpy(c1->Argument_Ch2[0],"5555"); 
                  }
          else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
/**********************sentinal control and monitor end here *********************/

/*********************Fibre_optics Control and monitor start here ***************/

else if(!strcmp(argname[0],"fiber_optics"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
                       strcpy(c1->op_name,"set");      
                       c1->number_param=1;
                       strcpy(c1->parameter_name[0],"rf_attn");
                       strcpy(c1->Argument_Ch1[0],"25");
                       strcpy(c1->Argument_Ch2[0],"35"); 
                  }
          else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
/******************* Fibre_optics Control and monitor end here  ****************/

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
 while(1)
 {
        if (newsockfd < 0) 
           fprintf(stderr,"ERROR Accept socket\n");
           fprintf(stderr,"\n Now Writing on Socket\n");
            time(&t1);
            ctime_r(&t1,stamp1);
            strcpy(c1->timestamp,stamp1);

          n = write(newsockfd,c1,sizeof(cmd));

       if (n < 0)
                fprintf(stderr,"ERROR writing socket\n");
       else
        printf("we wrote on the socket %d %s %s %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("%s %s %s\n",c1->parameter_name[i],c1->Argument_Ch1[i],c1->Argument_Ch2[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
         sleep(2);
         fprintf(stderr,"\nNow Reading on Socket\n");
         read(newsockfd,r1,sizeof(resp));
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
       // close(newsockfd);
       // close(sockfd);
     return 0; 
}
