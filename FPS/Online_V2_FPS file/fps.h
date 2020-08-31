#ifndef H_FPS_H
#define H_FPS_H
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include <math.h>
#include <unistd.h>
#include"server.h"
//#define PORT_SERVO 5500

typedef enum { FPSINIT,LOADPARAM,/*MVPOS,*/FPSNULL,SET_TPOINT,SET_RAMPDCNT,SET_LOW_RPM,SET_BRAKE_DD,SET_RAMPUPCNT
              ,SET_STOPTIMECNT,SET_MAX_PWM_CNT,SET_MAX_ANGLE,SET_MIN_ANGLE,READ_TPOINT,READ_RAMPDCNT,READ_LOW_RPM,READ_BRAKE_DD,READ_RAMPUPCNT,
                READ_STOPTIMECNT,READ_MAX_PWM_CNT,READ_MAX_ANGLE,READ_MIN_ANGLE,READ_VERSION,RUN_TO_CAL,FREE_RUN_TOW,
                RUN_TO_PRESET,RUN_FINE_TUNE,PASSWORD_RUN,REBOOT,FPSSTOP,FPSEND} FPSCMD;


//typedef enum {610=0,150=1,1420=2,325=3 } FEED;
void fps_cmd_list(int i,ANT_CMD *f1,cmd *c1);
void* fpssystem( void* parameters);
int loadpara[4];
void loadparam();
#endif //H_FPS_H
