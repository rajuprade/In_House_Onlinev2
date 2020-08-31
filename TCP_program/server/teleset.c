/* A simple server in the internet domain using TCP
   The port number is passed as an argument
   This version runs forever, forking off a separate
   process for each connection
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 5123
struct employee
{
  int id;
  char name[10];
};
typedef struct employee EMP;
void dostuff(int); /* function prototype */
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
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while (1) {
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     } /* end of while */
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
   int n;
   EMP e1;
   EMP *ptr;
   ptr = &e1;

  /* char buffer[256];

   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   printf("Here is the message: %s\n",buffer);

    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sock,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");*/
     
     //  bzero(&e1,sizeof(e1));
      n = read(sock,&e1,sizeof(e1));
       if(n < 0)
        printf("error reading from socket");
        printf("2.read:%2d %s\n",ptr->id,ptr->name);
         sleep(1);
     //   bzero(&e1,sizeof(e1));
     
  //    ptr = &e1;  
      ptr->id = 20;
      strcpy(ptr->name, "mangeshsir");  
      n =  write(sock,&e1,sizeof(e1));
      if(n < 0)
        printf("error writing to socket");
        printf("1.wrote:%2d %s\n",ptr->id,ptr->name);

}

