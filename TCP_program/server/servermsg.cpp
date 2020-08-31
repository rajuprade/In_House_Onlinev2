#include"sock.h"
#include<sys/times.h>
#include<sys/types.h>
#define MSG1 "invalid cmd to message server "
typedef enum { LOCAL_TIME ,GMT_TIME ,QUIT_CMD ,ILLEGAL_CMD } CMDS;

int process_cmd(int fd)
{
  
  char buf[80];
  time_t tim;
  char* cptr;

  while(read(fd ,buf,sizeof buf ) > 0 )
  {
     int cmd = ILLEGAL_CMD;
     (void)sscanf(buf, "%d",&cmd);
      switch(cmd)
      {
        case LOCAL_TIME:
           tim = time(0);
           cptr = ctime(&tim);
           write(fd ,cptr ,strlen(cptr)+1);
           break;
    
         case GMT_TIME:
           tim = time(0);
           cptr = asctime(gmtime(&tim));
           write(fd,cptr ,strlen(cptr)+1);
           break;
         
         case QUIT_CMD:
              return cmd;
        
         default:
           write(fd ,MSG1 ,sizeof MSG1);
       }
    }
   return 0;
}

int main(int argc ,char *argv[])
{
  
   char buf[80] ,socknm[80];
   int port = -1 ,nsid,rc;
   fd_set select_set;
   struct timeval timeRec;
   
   if(argc < 2)
   {
     cerr << "usage: " << argv[0] << "<socknamelport>  [<host>]\n";
   }
   
   (void)sscanf(argv[1] ,"%d",&port);

   sock sp(port!= -1 ? AF_INET :AF_UNIX ,SOCK_STREAM);
   
  if(!sp.good()) return 1;
  
  if(sp.bind(port == -1 ? argv[1] :argv[2] ,port ) < 0 )return 2;
  
  /* poll for client connection ,polling timeout after one second */
  
   for(;;)
    {
      timeRec.tv_sec = 1;
      timeRec.tv_usec = 0;
      FD_ZERO(&select_set);
      FD_SET(sp.fd() ,&select_set);

      rc = select(FD_SETSIZE ,&select_set ,0 ,0, &timeRec);
      if(rc > 0 && FD_ISSET(sp.fd(),&select_set))
         {
            if((nsid = sp.accept(0,0)) < 0) return 1;
 
             if(process_cmd(nsid) == QUIT_CMD)
               break;

            close(nsid);
         }
      }
    sp.shutdown();
    return 0;
}
  
 






