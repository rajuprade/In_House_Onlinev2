#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 5123
#include "comhlink.h"

int open_socket(struct in_addr local_address)
{
    int sockfd, pid ;
    struct sockaddr_in serv_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
      {
        error("ERROR opening socket");
         exit(0);
        
      }
   
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr = local_address;
    if(connect(sockfd,(struct sockaddr *) &serv_addr,  sizeof(serv_addr))< 0 )
       {
        printf("failed to connect");
      }
     else
      {
         fprintf(stderr, " Connected to Server Successfully...\n");
         pid = fork();
         if (pid < 0)
           {
             error("ERROR on fork");
           }
         else if (pid == 0)
            {
                 dostuff(sockfd);
                 //sleep(2); 
                 read_socket(sockfd);
                 //sleep(1);
                 write_socket(sockfd); 
                 exit(0);
            }
      }
     return 0; /* we never get here */

}
int dostuff (int sock)
{
    int n;
    MSG *buffer;

    buffer =  (MSG *)malloc ( sizeof ( MSG ) );
    if(buffer == NULL)
      exit(1);
    n = read(sock,buffer,sizeof(MSG ));

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

     sleep(1);

    buffer->length = 20;
    strcpy(buffer->Msg ," Hi I m the ABC software \n");
   //in the last parameter of write we have to pass sizeof the structure.
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
     return 0;
}
int read_socket(int sock )
{
    MSG *buffer =  (MSG *)malloc ( sizeof ( MSG ) );
    if(buffer == NULL)
      exit(1);
   int n = read(sock,buffer,sizeof(MSG ));

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
int write_socket(int sock)
{
     MSG *buffer =  (MSG *)malloc ( sizeof ( MSG ) );
     buffer->length = 20;
     strcpy(buffer->Msg ," Hi I m the ABC software \n");
   //in the last parameter of write we have to pass sizeof the structure.
    int   n = write(sock,buffer,sizeof(MSG));
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
     return 0;

}
