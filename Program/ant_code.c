#include<stdio.h>

int main()
{
  int AbcAns[4]={0,0,10,0},tmp[4]={0,0,0,0};
  int j=0;
  int addr=-1;
  if(AbcAns[0] | tmp[0])
     addr =1;
   else if(AbcAns[1] | tmp[1])
     addr =9;  
  else if(AbcAns[2] | tmp[2])
     addr =20;
   else if(AbcAns[3] | tmp[3])
     addr =25;
  else
       printf(" No antenna in the sub array\n");
  if (addr < 8) j = 0;
  else if (addr < 16) {j = 1; addr -= 8;}
  else if (addr < 24) {j = 2; addr -= 16;}
  else if (addr < 32) {j = 3; addr -= 24;}

  switch (addr) {
    case 1: if((AbcAns[j] |= 0x01))printf("Antenna Number is C01\n");break;
    case 2: AbcAns[j] |= 0x02; break;
    case 3: AbcAns[j] |= 0x04; break;
    case 4: AbcAns[j] |= 0x08;printf("Antenna Number is C04\n"); break;
    case 5: AbcAns[j] |= 0x10; break;
    case 6: AbcAns[j] |= 0x20; break;
    case 7: AbcAns[j] |= 0x40; break;
    case 8: AbcAns[j] |= 0x80;
  }
 return 0;
}
