#ifndef SOCK_H
#define SOCK_H
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<memory.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
//#include<sys/systeminfo.h>
const int BACKLOG = 5;

using namespace std;
class sock
{
   private:
        int sid;
        int domain;
        int socktype;
        int rc;
   
    int constr_name(struct sockaddr_in& addr ,const char* hostnm,int port)
     {
        addr.sin_family = domain;
        if (!hostnm)
        addr.sin_addr.s_addr = INADDR_ANY;
        else
          {
            struct hostent *hp = gethostbyname(hostnm);
            if(hp == 0)
             {
               fprintf(stderr ,"gethostbyname");
               return -1;
             }
            memcpy((char*)&addr.sin_addr,(char*)hp->h_addr,hp->h_length);
          }
         addr.sin_port = htons(port);
         return sizeof(addr);
      };
    
   int constr_name(struct sockaddr& addr ,const char* pathnm)
     {
        addr.sa_family = domain;
        strcpy(addr.sa_data ,pathnm);
        return sizeof(addr.sa_family) + strlen(pathnm) + 1;
     };      

     char* ip2name(const struct in_addr in)
     {
       u_long laddr;
       if ((int)(laddr = inet_addr(inet_ntoa(in))) == -1 )
           return 0;
         struct hostent *hp = gethostbyaddr((char*)&laddr,sizeof(laddr),AF_INET);
         if(!hp)
         return 0;
         for(char **p = hp->h_addr_list; *p!= 0; p++)
          {
            if(hp->h_name)
            return hp->h_name;
          }
          return 0;
       };    

   public:


       sock(int dom ,int type ,int protocol = 0):domain(dom),socktype(type)
        {
           if((sid = socket(dom ,type ,protocol)) < 0)
             fprintf(stderr,"socket");
        };
 
       ~sock()
         {
             shutdown();
             close(sid);
         };

        int fd()
          {return sid; };
       
        int good()
         {  return sid >= 0; };

        int bind(const char* name ,int port = -1)
         {
               if(port == -1)
               {
                   struct sockaddr addr;
                   socklen_t len = constr_name(addr,name);
                   if((rc= ::bind(sid,&addr,len)) < 0)
                   fprintf(stderr,"bind");
               }
               else
                {
                   struct sockaddr_in addr;
                   socklen_t len = constr_name(addr,name,port);
                   if((rc= ::bind(sid,(struct sockaddr*)&addr,len)) < 0 ||(rc=getsockname(sid,(struct sockaddr*)&addr,&len) < 0))
                     fprintf(stderr,"bind or getsockname");
                   else cout <<"Socket port :" << ntohs(addr.sin_port) << endl;
                }
            if(rc!= -1 && socktype!=SOCK_DGRAM && (rc=listen(sid,BACKLOG)) < 0)
                fprintf(stderr,"listen");
                return rc;
          }; 
         
          int accept(char *name ,int* port_p)
          {
            if(!name)return ::accept(sid,0,0);
            if(!port_p || *port_p == -1)
             {
                 struct sockaddr addr;
                 socklen_t size = sizeof(addr);
                 if((rc = ::accept(sid ,&addr,&size)) > -1)
                 strncpy(name ,addr.sa_data,size),name[size] = '\0';
             }

            else
             {
               struct sockaddr_in addr;
               int size = sizeof(addr);
               if((rc= ::accept(sid ,(struct sockaddr*)&addr ,(socklen_t*)&size)) > -1)            
               {
                 if(name)
                 strcpy(name,ip2name(addr.sin_addr));
                 if(port_p)
                 *port_p = ntohs(addr.sin_port);
               }
             }
             return rc;
           };
        
           int connect (const char* hostnm,int port = -1)
            {
                if(port == -1)
                 {
                    struct sockaddr addr;
                    socklen_t len = constr_name(addr,hostnm);
                    if((rc = ::connect(sid,&addr,len)) > 0)
                    fprintf(stderr ,"connect");
                 }
                else
                 {
                    struct sockaddr_in addr;
                    socklen_t len = constr_name(addr ,hostnm,port);
                    if((rc= ::connect(sid,(struct sockaddr*)&addr,len)) < 0)
                    fprintf(stderr ,"connect");
                 }
                 return rc;
             };            
           
            int write(const char* buf,int len ,int flag = 0 ,int nsid = -1)
            {
               return ::send(nsid == -1 ? sid : nsid,buf,len ,flag);
            };
            
            int read(char* buf,int len ,int flag = 0 ,int nsid = -1)
            {
               return ::recv(nsid == -1 ? sid : nsid,buf,len ,flag);
            };
     
           int writeto(const char* buf,int len ,int flag,const char* name,const int port ,int nsid = -1)
            {
                if(port == -1)
                {
                  struct sockaddr addr;
                  int size = constr_name(addr,name);
                  return ::sendto(nsid == -1 ? sid :nsid,buf,len,flag,&addr,size);
                }
                else
                {
                  struct sockaddr_in addr;
                  char buf1[80];
                  if(!name)
                   {
                     //if(sysinfo(SI_HOSTNAME,buf1,sizeof(buf1)) == -1L )
                       fprintf(stderr,"sysinfo");
                       name = buf1;
                   }
                    int size = constr_name(addr,name,port);
                    return ::sendto(nsid == -1 ? sid : nsid,buf,len,flag,(struct sockaddr *)&addr,size);
                  }
              };
         
             int readfrom(char* buf ,int len ,int flag ,char* name,int *port_p,int nsid = -1)
               {
                  if(!port_p || *port_p == -1)
                  {
                    struct sockaddr addr;
                    int size = sizeof(addr);
                    if((rc= ::recvfrom(nsid == -1 ? sid : nsid,buf ,len ,flag,&addr ,(socklen_t*)&size)) > -1 && name)  
                      strncpy(name ,addr.sa_data,rc),name[rc] = '\0';
                  }
                  else
                  {
                    struct sockaddr_in addr;
                    int size = sizeof(addr);
                    if(( rc= ::recvfrom(nsid == -1 ? sid : nsid,buf,len,flag,(struct sockaddr*)&addr,(socklen_t*)&size)) > -1)
                     {
                       if(name)strcpy(name,ip2name(addr.sin_addr));
                       if(port_p) *port_p = ntohs(addr.sin_port);
                     }
                   }
                  return rc;
                };
            
              int shutdown(int mode = 2)
               {
                  return ::shutdown(sid,mode);
               };
   };

#endif      
