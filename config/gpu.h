#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ 10000

typedef struct
{

 static int  gpumode;
 static int  gpulta;
 static double  gpubw;
 static int  gpufinbw;
 static double  gpuedgefrq;
 static int  gpuchan;
 static int  gpustokes;
 static int  gpucntrl;
 static int  gpufstop;
 static char  gpubeam1;
 static char  gpubeam2;
 static int  gpugain;

 static char time ;
 static char timestamp[26];
} setgpu;

  setgpu *gpu;
