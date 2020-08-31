/* A simple server in the internet domain using TCP
   demonstrating how to send structure over sockets ******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<fcntl.h>
#define PORT 5000

int so_block(int sockfd,int flag)
{ int flg;
     flg = fcntl(sockfd, F_GETFL, &flg);
     if (flg < 0) return flg;
     if (flag){ flg |= O_NDELAY; }
     else { flg &= ~O_NDELAY; }
     return fcntl(sockfd, F_SETFL, flg);
}

#pragma pack(push,1)

typedef struct 
{
  int seq;
  char timestamp[64];
  char system_name[16];
  char op_name[16];
  char parameter_name[32][16];
  char Argument_Ch1[32][16];
  char Argument_Ch2[32][16];
 } cmd;

typedef struct
{ 
 int response_type;
 int seq;
 char timestamp[64];
 char system_name[16];
 char Mon_raw[64][8];
 char Mon_sum[64][16];
 char response_message[32][32];
} resp;

#pragma pack(pop)
int main(int argc, char *argv[])
{
     int sockfd, newsockfd,n,yes=1,i=0;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     char argdata[32],stamp1[26];
     time_t t1;
     char buffer[100];

    /* printf("Enter CH1 bandwidth\n");
     scanf("%s", &argdata); */
     cmd *c1;
     
     c1 = malloc(sizeof(cmd));
     resp *r1;
     r1 = malloc(sizeof(resp));
     c1->seq= 10;
     time(&t1);
     ctime_r(&t1,stamp1);
     strcpy(c1->timestamp,stamp1);
     strcpy(c1->system_name,"Sentinel");
     strcpy(c1->op_name,"SET");
     strcpy(c1->parameter_name[0],"BW ATTN PG ALC");
   /*  c1->Argument_Ch1[0]= 16;
     c1->Argument_Ch2[0] = 32; */
     // sprintf(argdata,"%s","16MHZ");
     // strcpy(c1->Argument_Ch1,argdata);
     strcpy(c1->Argument_Ch1[0],"16MHZ 12MHZ");
    // c1->Argument_Ch1[0][strlen(argdata)]='\0';
     strcpy(c1->Argument_Ch2[0],"16MHZ 12MHZ"); 
    
       // printf("%s %d\n",e1->name,e1->emp_code);
   /*  if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     } */
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
         n = write(newsockfd,c1,sizeof(cmd));

       if (n < 0)
                fprintf(stderr,"ERROR writing socket\n");
       else
        printf("we wrote on the socket %d %s %s %s %s %s %s \n",c1->seq,c1->timestamp,c1->system_name,c1->op_name,c1->parameter_name,c1->Argument_Ch1,c1->Argument_Ch2);
        printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
          if (n < 0)
                fprintf(stderr,"ERROR reading socket\n");
       else
               //so_block(newsockfd,1);
         sleep(2);
         read(newsockfd,r1,sizeof(resp));
               //so_block(newsockfd,0);
         printf(" Size of Response Struct is ######## %d\n",sizeof(resp));
        printf("$$$$$$$$$$$$$$$$$ got from Client\n");
        printf("we read on the socket %d %d %s %s %s %s %s \n",r1->response_type,r1->seq,r1->timestamp,r1->system_name,r1->Mon_raw,r1->Mon_sum,r1->response_message);
        //printf("Message %s\n",r1->response_message[0]);
      //  sleep(10);
       }
        close(newsockfd);
        close(sockfd);
     return 0; 
}
