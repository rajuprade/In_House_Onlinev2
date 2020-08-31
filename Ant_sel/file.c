#include <stdio.h>
#include <stdlib.h>
#include<strings.h> 
#include<string.h>
int main()
{
   char ch, file_name[25];
   FILE *fp;
   int bytes_read;
  int nbytes = 100;
  char *my_string;
  char buffer[20];
   my_string = (char *) malloc (nbytes + 1);
     printf("Enter the name of file you wish to see\n");
   gets(file_name);
 
   fp = fopen(file_name,"r"); // read mode
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   printf("The contents of %s file are :\n", file_name);
 
   while( ( ch = fgetc(fp) ) != EOF )
    {
     if(ch =='#')
      {
        bytes_read = getline (&my_string, &nbytes,fp);
        bzero(my_string,(nbytes+1));
       // printf("USEless\n");
       // continue;
      }
      else
       {
       // printf("%c",ch);
        bzero(buffer,20);
        sprintf(buffer,"%c",ch);
       //buffer[1]=='\0';
       //strcpy(buffer,ch);
       printf("%s",buffer);
        bzero(buffer,20);
        }
      // bytes_read = getline (&my_string, &nbytes,fp);
      // puts(my_string);
    }
   fclose(fp);
   return 0;
}
