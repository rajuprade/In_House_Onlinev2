#include<stdio.h>


typedef enum {SENTINAL,SIGCON,FRONTEND,BACKEND,DATASERVER,SERVO } system;
void devSentinal();
void devFrontend();
void devDataserver();
void devBackend();
void devServo();
void devSigcon();

void devSentinal()
{
   fprintf(stderr,"SENTINEL SYSTEM\n");
}

void devFrontend()
{
   fprintf(stderr,"Frontend SYSTEM\n");
}
void devDataserver()
{
   fprintf(stderr,"Dataserver SYSTEM\n");
}

void devBackend()
{
   fprintf(stderr,"Backend SYSTEM\n");
}
void devServo()
{
   fprintf(stderr,"Servo SYSTEM\n");
}
void devSigcon()
{
   fprintf(stderr,"Sigcon SYSTEM\n");
}
int main()
{
     int systemid;
     void  ( * devSpecProcessing )(); 
     fprintf(stderr,"Enter systemid for the system\n");
     scanf("%d",&systemid);
     switch(systemid) {
          case   SENTINAL : devSpecProcessing = devSentinal ;
                            break;
          case   SIGCON   : devSpecProcessing = devSigcon;
                            break;
          case   FRONTEND : devSpecProcessing = devFrontend ; 
                            break;
          case   BACKEND   :devSpecProcessing = devBackend ;
                            break;
          case   DATASERVER : devSpecProcessing = devDataserver ; 
                             break;
          case   SERVO : devSpecProcessing = devServo ; 
                              break;
          default : devSpecProcessing = devSentinal ; break;
          }
   (* devSpecProcessing)();

  return 0;
}
