#include"sock.h"
const char* MSG1 = "hello MSG1";
const char* MSG3 = "hELLO MSG2";

int main(int argc ,char *argv[])

{

     int port = -1 ,rc;
     if(argc < 2)
     {
       cerr << "usage: " << argv[0] << "<socknamelport> [<host>]\n";
       return 1;
     }

   (void)sscanf(argv[1], "%d",&port);

   char buf[80] ,*host = (port == -1) ? argv[1] : argv[2] ,socknm[80];
  
   sock sp(port!= -1 ? AF_INET :AF_UNIX ,SOCK_STREAM);
   
   if(!sp.good()) return 1;

   if(sp.connect(host,port) < 0) return 8;
   
   if(sp.write(MSG1,strlen(MSG1)+1) < 0)
     return 9;
   
   if(sp.read(buf,sizeof(buf)) < 0 )return 10;
   cerr << "client:recv" << buf << "\n";

  if((rc = sp.writeto(MSG3,strlen(MSG3)+1 ,0,host ,port,-1)) < 0) 
      return  11;

  if((rc = read(sp.fd(),buf,sizeof(buf))) == -1)
      return 12;
    cerr << "client:read msg: " << buf << "\n";

   sp.shutdown();
}    
  
