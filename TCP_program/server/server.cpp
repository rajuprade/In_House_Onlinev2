#include"sock.h"

const char* MSG2 = "HELLO MSG2";
const char* MSG4 = "HELLO MSG4";

int main(int argc ,char* argv[])
{
   char buf[80] ,socknm[80];
   
   int port = -1,nsid ,rc;
   
   if(argc < 2)
    {
      cerr << "usage: " << argv[0] << "<socknamelport> [<host>]\n";
      return 1;
    }
    
   (void)sscanf(argv[1], "%d",&port);
   
   sock sp(port!= -1 ? AF_INET : AF_UNIX ,SOCK_STREAM);
 
    if(!sp.good())
    return 1;
    
   if(sp.bind(port == -1 ? argv[1] : argv[2],port) < 0)
     return 2;
   
   if((nsid =sp.accept(0,0)) < 0) return 1;

   if(( rc =sp.read(buf,sizeof(buf),0,nsid)) < 0) return 5;
    cerr << "server : receive msg : " << buf << "\n";
   

   if(sp.write(MSG2,strlen(MSG2)+1 ,0,nsid) < 0)
   return 6;
   
   if(sp.readfrom(buf ,sizeof(buf),0,socknm,&port ,nsid) > 0)
   cerr << "server : recvfrom " << socknm << "msg: " << buf << "\n ";

   if(write(nsid ,MSG4 ,strlen(MSG4)+1) == -1)
    return 7;
}

   
    
