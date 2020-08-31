#include"sock.h"
#define QUIT_CMD 2

int main(int argc ,char* argv[])
{
   if(argc < 2)
     {
         cerr <<"usage:" << argv[0] << "<sockname | port> [host> ]\n";
         return 1;
     }

     int port = -1 ,rc;

     (void)sscanf(argv[1] ,"%d",&port);
     
     char buf[80] ,*host = (port == -1) ? argv[1] :argv[2] ,socknm[80];
     
     sock sp(port!= -1 ? AF_INET : AF_UNIX,SOCK_STREAM);
     
     if(sp.connect(host,port) < 0) return 8;
     
     for( int cmd = 0 ;cmd < 3 ;cmd++)
      {
          sprintf(buf ,"%d" ,cmd);
          if(sp.write(buf,strlen(buf)+1) < 0) return 9;
     
          if(cmd == QUIT_CMD)
            break;
            
          if(sp.read(buf,sizeof buf) < 0 )return 10;
             cerr << "client: recv " << buf << "\n";
       }
       sp.shutdown();
       return 0;
} 
