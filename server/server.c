
#include"server.h"
char* tp(char *tstamp)
{

 char stamp1[26], stamp2[21];
 time_t t1;
   time(&t1);
   ctime_r(&t1, stamp1);
 //  fprintf(stderr,"%s\n",stamp1);
   stamp2[0] = stamp1[8];
   stamp2[1] = stamp1[9];
   stamp2[2] = '-';
   stamp2[3] = stamp1[4]; 
   stamp2[4] = stamp1[5]; 
   stamp2[5] = stamp1[6];
   stamp2[6] = '-'; 
   stamp2[7] = stamp1[20];
   stamp2[8] = stamp1[21];
   stamp2[9] = stamp1[22];
   stamp2[10] = stamp1[23];
   stamp2[11]= ' ';
   stamp2[12] = stamp1[11];
   stamp2[13] = stamp1[12];
   stamp2[14] = stamp1[13];
   stamp2[15] = stamp1[14];
   stamp2[16] = stamp1[15];
   stamp2[17] = stamp1[16];
   stamp2[18] = stamp1[17];
   stamp2[19] = stamp1[18];
   stamp2[20] = '\0'; 
   strcpy(tstamp,stamp2);
 // fprintf(stderr,"%s\n",stamp2);
  return (tstamp);
}

void write_command_xml(cmd *c2)
{

   xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
   // xmlDtdPtr dtd = NULL;       /* DTD pointer */
    char buff[2000];
    char buf[200][100];
    int i;
   // char *finalxml;
   char responsefile[5000]="/home/teleset/Desktop/CS.xml";
   /*  xmlChar *xmlbuff;
    xmlbuff = (xmlChar *)malloc(sizeof(204800));
    finalxml = (char *)malloc(sizeof(204800));
    int buffersize=0; */
    LIBXML_TEST_VERSION;

    /* 
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "commands");
    xmlDocSetRootElement(doc, root_node);

    /*
     * Creates a DTD declaration. Isn't mandatory. 
     */
   // dtd = xmlCreateIntSubset(doc, BAD_CAST "responses", NULL, BAD_CAST "server2.dtd");

    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
  
   // xmlNewChild(root_node, NULL, BAD_CAST "response", NULL);

    /* 
     * xmlNewProp() creates attributes, which is "attached" to an node.
     * It returns xmlAttrPtr, which isn't used here.
     */
    node = xmlNewNode(NULL, BAD_CAST "command");

    xmlAddChild(root_node, node);
  
    
   
    bzero(buff,2000);sprintf(buff,"%d",c2->seq);
    xmlNewChild(node, NULL, BAD_CAST "seq",BAD_CAST buff);

    bzero(buff,2000);sprintf(buff,"%s",c2->timestamp);
    xmlNewChild(node, NULL, BAD_CAST "timestamp",BAD_CAST buff);
    
    bzero(buff,2000);sprintf(buff,"%s",c2->system_name);
    xmlNewChild(node, NULL, BAD_CAST "system_name",BAD_CAST buff);

    bzero(buff,2000);sprintf(buff,"%s",c2->op_name);
    xmlNewChild(node, NULL, BAD_CAST "operation_name",BAD_CAST buff);
 
     node1 = xmlNewNode(NULL, BAD_CAST "Data");

    xmlAddChild(node, node1);
    
    for(i=0;i<c2->number_param;i++)
    {
      bzero(buf,sizeof(buf));
      strcpy(buf[i],c2->parameter_name[i]);
      xmlNewChild(node1, NULL, BAD_CAST "param_name",BAD_CAST buf[i]);
      bzero(buf,sizeof(buf));
      strcpy(buf[i],c2->Argument_Ch1[i]);
      xmlNewChild(node1, NULL, BAD_CAST "Argument_Ch1",BAD_CAST buf[i]);
      bzero(buf,sizeof(buf));
      strcpy(buf[i],c2->Argument_Ch2[i]);
      xmlNewChild(node1, NULL, BAD_CAST "Argument_Ch2",BAD_CAST buf[i]);
    }

      
    
    /* 
     * Dumping document to stdio or file
     */
    xmlSaveFormatFileEnc(responsefile, doc, "UTF-8", 1);
    //  xmlDocDumpFormatMemoryEnc(doc, &xmlbuff,&buffersize,"UTF-8",0);
     // strcpy(finalxml,(char *)xmlbuff);
     // printf("The XML file %s\n",finalxml);
     puts(responsefile);

    /*free the document */
    xmlFreeDoc(doc);
   //  xmlFree(xmlbuff);
   //  free(finalxml);
    
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
}

/********** Using LIBXML it write Response XML file ********/
void write_response_xml(resp *r2)
{

    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, node = NULL;/* node pointers */
    //xmlDtdPtr dtd = NULL;       /* DTD pointer */
    char buff[2000];
    char buf[200][100];
    int i;
   // char *finalxml;
   char responsefile[5000]="/home/teleset/Desktop/RS.xml";
   /*  xmlChar *xmlbuff;
    xmlbuff = (xmlChar *)malloc(sizeof(204800));
    finalxml = (char *)malloc(sizeof(204800));
    int buffersize=0; */
    LIBXML_TEST_VERSION;

    /* 
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "responses");
    xmlDocSetRootElement(doc, root_node);

    /*
     * Creates a DTD declaration. Isn't mandatory. 
     */
   // dtd = xmlCreateIntSubset(doc, BAD_CAST "responses", NULL, BAD_CAST "server2.dtd");

    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
  
   // xmlNewChild(root_node, NULL, BAD_CAST "response", NULL);

    /* 
     * xmlNewProp() creates attributes, which is "attached" to an node.
     * It returns xmlAttrPtr, which isn't used here.
     */
    node = xmlNewNode(NULL, BAD_CAST "response");

    xmlAddChild(root_node, node);
  
    
    bzero(buff,2000);sprintf(buff,"%d",r2->response_type);
    xmlNewChild(node, NULL, BAD_CAST "response_type",BAD_CAST buff);
    bzero(buff,2000);sprintf(buff,"%d",r2->seq);
    xmlNewChild(node, NULL, BAD_CAST "seq",BAD_CAST buff);

    bzero(buff,2000);sprintf(buff,"%s",r2->timestamp);
    xmlNewChild(node, NULL, BAD_CAST "timestamp",BAD_CAST buff);
    
    bzero(buff,2000);sprintf(buff,"%s",r2->system_name);
    xmlNewChild(node, NULL, BAD_CAST "system_name",BAD_CAST buff);
 
     bzero(buf,sizeof(buf));
     for(i=0;i<64;i++)
      {
       strcpy(buf[i],r2->Mon_raw[i]);
        xmlNewChild(node, NULL, BAD_CAST "Mon_raw",BAD_CAST buf[i]); 
      }
  //   xmlNewChild(node, NULL, BAD_CAST "Mon_raw",BAD_CAST buf); 

    bzero(buff,2000);
    strcpy(buff,r2->Mon_sum[0]);
    xmlNewChild(node, NULL, BAD_CAST "Mon_sum",BAD_CAST buff);

   bzero(buf,sizeof(buf));
    for(i=0;i<r2->num_resp_msg;i++)
    {
     strcpy(buf[i],r2->response_message[i]);
     xmlNewChild(node, NULL, BAD_CAST "response_message",BAD_CAST buf[i]);
    }

      
    
    /* 
     * Dumping document to stdio or file
     */
    xmlSaveFormatFileEnc(responsefile, doc, "UTF-8", 1);
    //  xmlDocDumpFormatMemoryEnc(doc, &xmlbuff,&buffersize,"UTF-8",0);
     // strcpy(finalxml,(char *)xmlbuff);
     // printf("The XML file %s\n",finalxml);
     puts(responsefile);

    /*free the document */
    xmlFreeDoc(doc);
   //  xmlFree(xmlbuff);
   //  free(finalxml);
    
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
}

void printcmd(cmd *c1)
{
   int i;
        printf("we wrote on the socket %d %s %s %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("%s %s %s\n",c1->parameter_name[i],c1->Argument_Ch1[i],c1->Argument_Ch2[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
}

void printresp(resp *r1)
{
   int i;
   printf(" Size of Response Struct is ######## %d\n",sizeof(resp));
         printf("$$$$$$$$$$$$$$$$$ got from Client\n");
         printf("##############Response Message from MCM setting##########\n %d\n %d\n %s\n %s\n ",r1->response_type,r1->seq,r1->timestamp,r1->system_name);
 
         for(i=0; i<32;i++)
          {
             printf("%s ",r1->Mon_sum[i]);
          }
 
        for(i=0; i<64;i++)
          {
             printf("%s ",r1->Mon_raw[i]);
          }
        
        for(i=0; i<r1->num_resp_msg;i++)
          {
            printf(" %s\n",r1->response_message[i]);
          }

}
/************* write_shm() *****/
void write_shm(cmd *c1, resp *r1)
{
 int shmid1,shmid2;
  key_t key1,key2;
 
   cmd  *c2;
   resp *r2;
   key1 = 5800;
   key2 = 5801;

 
  if( (shmid1 = shmget(key1,SHMSZ1,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (c2 = (cmd *)shmat(shmid1,NULL,0)) == (cmd *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
        
     if( (shmid2 = shmget(key2,SHMSZ2,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (r2 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
 
/*       c2= c1;
         r2= r1;
*/
    memcpy(c2, c1, sizeof(cmd));
    memcpy(r2, r1, sizeof(resp));
    fprintf(stderr," ************************Writing on shared Memory***********\n");         
    printcmd(c2);
    printresp(r2);
    write_command_xml(c2);
    write_response_xml(r2);
   /* bzero(c1,sizeof(cmd));
    bzero(c2,sizeof(cmd));
    bzero(r1,sizeof(resp));
    bzero(r2,sizeof(resp)); */
         
}
/*************write_shm ********/
int readable_timeo(int fd, int sec)
{
     fd_set rset;
     struct timeval tv;

      FD_ZERO(&rset);
      FD_SET(fd, &rset);

      tv.tv_sec = sec;
     tv.tv_usec = 0;

     return (select(fd + 1, &rset, NULL, NULL, &tv));
        /* > 0 if descriptor is readable */
}
