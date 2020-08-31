#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct
{
  char dep[30];
  char desg[20];
} detail;

typedef struct
{
  char name[20];
  int emp_id;
  detail *det;
 
} emp;

int main()
{
  emp *e1[30];
  int i;
 
   for(i=0;i<30;i++)
   {
    e1[i]= (emp *)malloc(sizeof(emp)); // It first allocates memory for the employee structure
   
    bzero(e1[i],sizeof(emp));
    
   }
   for(i=0;i<30;i++)
   { 
     e1[i]->det = malloc(sizeof(detail)); // It then allocates memory inside the employee memory for detail structure.
    } 

   strcpy(e1[1]->name,"Raj singh");
   e1[1]->emp_id = 001;
   strcpy(e1[1]->det->dep,"Telemetry");
   strcpy(e1[1]->det->desg,"ENG-C");

   fprintf(stderr,"######### %s %d %s %s\n",e1[1]->name,e1[1]->emp_id,e1[1]->det->dep,e1[1]->det->desg);

   strcpy(e1[2]->name,"sheetal singh");
   e1[2]->emp_id = 002;
   strcpy(e1[2]->det->dep,"Telemetry");
   strcpy(e1[2]->det->desg,"ENG-C");

   fprintf(stderr,"######## %s %d %s %s\n ",e1[2]->name,e1[2]->emp_id,e1[2]->det->dep,e1[2]->det->desg); 
   return 0;
}
