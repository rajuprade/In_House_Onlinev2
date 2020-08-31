#include"server.h"

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

int main(int argc, char *argv[])
{
     int n;
     setdata *set;  
     set = (setdata *)malloc(sizeof(setdata));
     cmd *c1;
     c1 = malloc(sizeof(cmd));
     resp *r1;
     r1 = malloc(sizeof(resp));
     char *tstamp;
     tstamp = malloc(25);
      int sockfd, newsockfd,yes=1;
      socklen_t clilen;
      struct sockaddr_in serv_addr, cli_addr;
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
       fprintf(stderr,"ERROR opening socket\n");
    if(setsockopt(sockfd, SOL_SOCKET , SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
          fprintf(stderr,"Error\n");
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
    while(1)
   {
     
      fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");

       newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); 
      //   for(;;)
       // {
            printf("Enter 0 for file input and 1 for user input\n");
            scanf("%d",&n);
            exec(set,n);
            write_us_shm(set);
          printf("\n\nEnter the system number from the list\n");
          printf("0.sentinal\n");
          printf("1.front_end\n");
          printf("2:fiber_optics\n");
          printf("3:back_end\n");
           printf("4:self_test\n\n");                                                  
          scanf("%d",&n);
           exec_cmd(n,c1);
           for(;;)
         {
           tstamp = tp(tstamp);
           strcpy(c1->timestamp,tstamp); 
          // write_read(newsockfd,c1,r1);
            write(newsockfd,c1,sizeof(cmd));
            sleep(2);
           fprintf(stderr,"\nNow Reading on Socket\n"); 
           if (readable_timeo(newsockfd, 5) == 0)
             {
               fprintf(stderr, "SOCKET TIMEOUT\n");
               close(newsockfd);
               //goto again;
              // continue;
                 break;
             }
           else
         {
           read(newsockfd,r1,sizeof(resp));
           write_shm(c1,r1); 
           printcmd(c1);
           printresp(r1);
           write_command_xml(c1);
           write_response_xml(r1);
         }
       } 
          
      
  } 
     
     return 0; 

}
#else
int main(void) {
    fprintf(stderr, "server2 support not compiled in\n");
    exit(1);
}
#endif

