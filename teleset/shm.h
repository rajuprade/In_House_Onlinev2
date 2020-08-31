#ifndef H_SERVER_H
#define H_SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ1 sizeof(cmd)
#define SHMSZ2 sizeof(resp) 
//#define SHMSZ 400
#define PORT 5000
#pragma pack(push,1)

typedef struct 
{
  int seq;
  char timestamp[64];
  char system_name[16];
  char op_name[16];
  short int number_param;
  char parameter_name[32][16];
  char Argument_Ch1[32][16];
  char Argument_Ch2[32][16];
 } cmd;

typedef struct
{ 
 int response_type;
 int seq;
 char timestamp[64];
 char system_name[16];
 char Mon_raw[64][8];
 char Mon_sum[32][64];   
 short int num_resp_msg;
 char response_message[32][64];  
} resp;

#pragma pack(pop)

#endif //H_SERVER_H
