


  /*program to extract bits from a interger byte array...........
                    this module vl be used in lowuser.cpp of teleset program 
                     to create multiple threads by concurrent server using multithreading .................*/
 
#include <stdio.h>
#include<string.h>


int main()
{
    
     int i;
     int buf[4];
     
     printf("Enter 4 number in hexadecimal\n");
     for(i=0;i < 4 ;i++)
     {
      scanf("%x",&buf[i]);
     }
     extraction(buf);
     return 0; 
}

int extraction(int* val)
{
         int i,j ;
         unsigned char  mask[8] ,tmp[32];
           
        for(j= 0 ; j < 4 ;j++)
        printf("value in val[%d] is %x\n",j,val[j]);
        
         for(j = 0 ; j< 4 ;j++)
         {
           
           for(i=0; i<8; i++)
           if(val[j] & (1<<i))
            mask[i] = 1;
             else
             mask[i] = 0;

              switch(j)
              {
       
               case 0:  
                      for(i = 0 ;i < 8;i++)
                      tmp[i] = mask[i];
                      break;
              
               case 1:
                      for(i = 0 ;i < 8;i++)
                      tmp[i+8] = mask[i];
                      break;
           
               case 2:
                      for(i = 0 ;i < 8;i++)
                      tmp[i+16] = mask[i];
                      break;
    
                case 3:
                      for(i = 0 ;i < 8;i++)
                      tmp[i+24] = mask[i];
               }    
          } 
 
           
                     
          for(i =0; i<32; i++)
          printf("tmp[%d]  =  %d \n",i,tmp[i]);


           for(i = 0 ; i < 32 ;i++)
            {
              if(tmp[i] == 1)
              printf("\n\t Anteena number %d is selected\n",i);
            }
          
            return 0;
}

