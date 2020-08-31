/****** XML files Writing *******/
#include"xml.h"
#include"server.h"

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

