#ifndef H_SHARED_MEM_H
#define H_SHARED_MEM_H
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ1 sizeof(cmd)
#define SHMSZ2 sizeof(resp) 
typedef struct
{
   int sub_num;
   int num_in_sub;
   char ant_name[32][8];
 }sub;

typedef struct
{
   int usernb;
   sub s_a[4];
   char timestamp[26];
} user;

typedef struct
{
   user Tx[4];

} setdata;

#endif 
