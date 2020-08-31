/* A simple server in the internet domain using TCP
   This version runs forever, forking off a separate
   process for each connection
*/
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 5123

typedef struct _msg
{
  int length;
  unsigned char Msg[2000];
} MSG ;

int dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd,clilen, pid;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
     {
       error("ERROR opening socket");
       exit(1);
     }
     else 
     {
       fprintf(stderr, " Sockfd : %d \n", sockfd);

       bzero((char *) &serv_addr, sizeof(serv_addr));
       serv_addr.sin_family = AF_INET;
       serv_addr.sin_addr.s_addr = INADDR_ANY;
       serv_addr.sin_port = htons(PORT);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
      {
       error("ERROR on binding");
      } 
      else 
      {
          listen(sockfd,5);
          clilen = sizeof(cli_addr);

          fprintf(stderr, " Waiting for Client ....\n");

          while (1)
           {
              newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                 if (newsockfd < 0) 
                 {
                   error("ERROR on accept");
                   exit(1);
                 } 
                 else 
                 {
       
                    fprintf(stderr, " Client Accepted successfully...\n");
                    pid = fork();
                    if (pid < 0) 
                      {
                         error("ERROR on fork");
                      }
                     else if (pid == 0)  
                      {
                          dostuff(newsockfd);
                          close(newsockfd);
                            exit(0);
                       } 
                          
                  }
           }

      }
   } 
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
int dostuff (int sock)
{
   int n;
   MSG *buffer;

   buffer = (MSG * ) malloc ( sizeof( MSG ));
   if ( buffer == NULL)
            exit(1);

   buffer->length = 10;
   strcpy(buffer->Msg ,"Hi I m the TELESET program \n");
   n = write(sock,buffer,sizeof(MSG));
   if(n < 0 ) 
     {
          printf("error writing to socket");
          free(buffer);
          close(sock);
          exit(1);

     } 
    else 
       {
         printf("1.wrote:%2d %s\n",buffer->length,buffer->Msg);
       }  
         
     sleep(1);
     n = read(sock,buffer,sizeof(MSG));
      if(n < 0 ) 
       {
          printf("error reading to socket");
          free(buffer);
          close(sock);
          exit(1); 
       } 
      else 
       {
         printf("1.read:%2d %s\n",buffer->length,buffer->Msg);
       }
       return 0;
}
