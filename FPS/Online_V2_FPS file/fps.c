#include"fps.h"

void fps_cmd_list(int cd,ANT_CMD *a1,cmd *c1)
{
   int x,y;

   /* cmd  *c1;
   c1 = malloc(sizeof(cmd));*/

      switch(cd)
     {

       case FPSINIT :  /*  int angle, x , y;
                      CurrentCmd.CmdNum = 20; Copy(1, INITINDX);           //read version

                     angle = 1000/2;                 //counts!
                       CurrentCmd.Argument[0] = angle & 0x00ff;
                      CurrentCmd.Argument[1] = angle>>8;
                           CurrentCmd.CmdNum = 10;
                            Copy(0, INITINDX);           //set min angle -16 deg

                          angle = 17000/2;
                          CurrentCmd.Argument[0] = angle & 0x00ff;
                           CurrentCmd.Argument[1] = (angle>>8);
                               CurrentCmd.CmdNum = 9;
                              Copy(0, INITINDX);           //set max angle 270 deg

                            x = 550; y = 0;        //time interval 0?
                               CurrentCmd.Argument[0] = x/5;
                         CurrentCmd.Argument[1] = (int) (y*0.2048*x/1800.0);
                             CurrentCmd.CmdNum = 4;
                             Copy(0, INITINDX);           //set lower rpm limit

                                    Copy(-1, INITINDX); */
       case LOADPARAM : // LOAD FPS related parameters for 4 feed 610 1420 150 325
                           loadparam();
                          fprintf(stderr,"=> %d %d %d %d \n",loadpara[0],
                                    loadpara[1],loadpara[2],loadpara[3]);break;
      /* case MVPOS :      // Depending on user input MY pos to that encoder number 
                        fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                         scanf("%d",&setparam);
                          if(setparam==610)
                          { pos = loadpara[0];} 
                          else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                               pos /= 2;
                              CurrentCmd.Argument[0] = pos & 0x00ff;
                               CurrentCmd.Argument[1] = pos>>8;
                               CurrentCmd.CmdNum = 23;
                               Copy(1, MVINDX);           //run to preset
                           break; */

       case FPSNULL:  a1->CMD.seq= 10;
                      strcpy(a1->CMD.op_name,"FPSNULL");   
                      a1->CMD.number_param=0;
                      c1=&a1->CMD;
                      printcmd(c1);
                      break;

      case SET_TPOINT:  a1->CMD.seq= 11;
                        strcpy(a1->CMD.op_name,"set_tpoint"); 
                        a1->CMD.number_param=1;
                         strcpy(a1->CMD.parameter_name[0],"set_tpoint");
                         fprintf(stderr,"\nEnter turning point position difference:\n");
                         scanf("%d",&x);
                         x = x/2;
                         y= x & 0x00ff;
                         sprintf(a1->CMD.Argument_Ch1[0],"%d",y);  //strcpy will not work ,sprintf will work
                         x = x >> 8;
                         sprintf(a1->CMD.Argument_Ch2[0],"%d",x);
                         c1=&a1->CMD;
                         printcmd(c1);
                         break;

      case SET_RAMPDCNT: a1->CMD.seq= 12;
                         strcpy(a1->CMD.op_name,"set_rampdcnt"); 
                         a1->CMD.number_param=1;
                         fprintf(stderr,"Enter Time interval:\n");
                         scanf("%d",&x);
                         strcpy(a1->CMD.parameter_name[0],"set_rampdcnt"); //Enter Time interval in decimal
                         sprintf(a1->CMD.Argument_Ch1[0],"%d",x/5);
                         c1=&a1->CMD;
                         printcmd(c1);
                         break;

      case SET_LOW_RPM: a1->CMD.seq= 13;
                        strcpy(a1->CMD.op_name,"set_low_rpm"); 
                        a1->CMD.number_param=1;
                        fprintf(stderr,"Enter Lower RPM limit:\n");
                        scanf("%d",&y);
                        fprintf(stderr,"Enter Check-Interval(ms)::\n");
                        scanf("%d",&x);
                        x=(x/5);
                        y= ((int) (y*0.2048*x/1800.0));
                        strcpy(a1->CMD.parameter_name[0],"set_low_rpm"); 
                        sprintf(a1->CMD.Argument_Ch1[0],"%d",x);
                        sprintf(a1->CMD.Argument_Ch2[0],"%d",y); 
                        c1=&a1->CMD;
                        printcmd(c1);
                           break;

       case SET_BRAKE_DD: a1->CMD.seq= 14;
                          strcpy(a1->CMD.op_name,"set_Brake_dd");                         
                          a1->CMD.number_param=1;
                          fprintf(stderr,"Enter Break Cnt difference::\n");
                          scanf("%d",&x);
                          x=(x/2);
                          strcpy(a1->CMD.parameter_name[0],"set_Brake_dd");
                          sprintf(a1->CMD.Argument_Ch1[0],"%d",x);
                          sprintf(a1->CMD.Argument_Ch2[0],"%d",y);
                          c1=&a1->CMD;
                          printcmd(c1);
                          break;  

       case SET_RAMPUPCNT: a1->CMD.seq= 15;
                           strcpy(a1->CMD.op_name,"set_rampupcnt");   
                           fprintf(stderr,"Enter Rampup Time Interval::\n");
                           scanf("%d",&x);
                           x=(x/5);
                           a1->CMD.number_param=1;
                           strcpy(a1->CMD.parameter_name[0],"set_rampupcnt"); 
                           sprintf(a1->CMD.Argument_Ch1[0],"%d",x);
                           sprintf(a1->CMD.Argument_Ch2[0],"%d",y);
                           c1=&a1->CMD;
                           printcmd(c1);                   
                           break; 

       case SET_STOPTIMECNT: a1->CMD.seq= 16;
                             strcpy(a1->CMD.op_name,"set_stoptimecnt");   
                             a1->CMD.number_param=1;
                             fprintf(stderr,"Enter SSLinterval:\n");
                             scanf("%d",&x);
                             x=(x/5);
                             a1->CMD.number_param=1;
                             strcpy(a1->CMD.parameter_name[0],"set_stoptimecnt"); 
                             sprintf(a1->CMD.Argument_Ch1[0],"%d",x);
                             sprintf(a1->CMD.Argument_Ch2[0],"%d",y);
                             c1=&a1->CMD;
                             printcmd(c1);
                             break;

      case SET_MAX_PWM_CNT: a1->CMD.seq= 17;
                            strcpy(a1->CMD.op_name,"set_Max_pwm_cnt"); 
                            a1->CMD.number_param=1;
                            fprintf(stderr,"Enter max PWM cnt:\n");
                            scanf("%x",&x);
                            strcpy(a1->CMD.parameter_name[0],"set_Max_pwm_cnt");
                            sprintf(a1->CMD.Argument_Ch1[0],"%x",x);
                            sprintf(a1->CMD.Argument_Ch2[0],"%d",y);
                            c1=&a1->CMD;
                            printcmd(c1);
                            break;

       case SET_MAX_ANGLE: a1->CMD.seq= 18;
                          strcpy(a1->CMD.op_name,"set_Max_angle");
                          fprintf(stderr,"\nEnter angle count:\n");
                          scanf("%d",&x);
                          x = x/2;
                          y = x & 0x00ff;
                          strcpy(a1->CMD.parameter_name[0],"set_Max_angle");
                          sprintf(a1->CMD.Argument_Ch1[0],"%d",y);  
                          x = x >> 8;
                          sprintf(a1->CMD.Argument_Ch2[0],"%d",x);
                          c1=&a1->CMD;
                          printcmd(c1);                     
                          break; 
         
      case SET_MIN_ANGLE: a1->CMD.seq= 19;
                          strcpy(a1->CMD.op_name,"set_min_angle");
                          strcpy(a1->CMD.parameter_name[0],"set_min_angle");
                          fprintf(stderr,"\nEnter angle count:\n");
                          scanf("%d",&x);
                          x = x/2;
                          y = x & 0x00ff;
                          sprintf(a1->CMD.Argument_Ch1[0],"%d",y);  
                          x = x >> 8;
                          sprintf(a1->CMD.Argument_Ch2[0],"%d",x);
                          c1=&a1->CMD;
                          printcmd(c1);
                          break; 

      case READ_TPOINT: a1->CMD.seq= 20;
                        strcpy(a1->CMD.op_name,"read_tpoint"); 
                        a1->CMD.number_param=0;
                        c1=&a1->CMD;
                        printcmd(c1);
                        break;

      case READ_RAMPDCNT: a1->CMD.seq= 21;
                          strcpy(a1->CMD.op_name,"read_rampdcnt"); 
                          a1->CMD.number_param=0; 
                          break;

      case READ_LOW_RPM: a1->CMD.seq= 22;
                         strcpy(a1->CMD.op_name,"read_low_rpm"); 
                         a1->CMD.number_param=0; 
                         c1=&a1->CMD;
                         printcmd(c1);
                         break;

     case READ_BRAKE_DD: a1->CMD.seq= 23;
                         strcpy(a1->CMD.op_name,"read_Brake_dd"); 
                         a1->CMD.number_param=0; 
                         c1=&a1->CMD;
                         printcmd(c1);
                         break;

     case READ_RAMPUPCNT: a1->CMD.seq= 24;
                          strcpy(a1->CMD.op_name,"read_rampupcnt"); 
                          a1->CMD.number_param=0; 
                          c1=&a1->CMD;
                          printcmd(c1);                    
                          break;

     case READ_VERSION: a1->CMD.seq= 25;
                        strcpy(a1->CMD.op_name,"read_version"); 
                        a1->CMD.number_param=0; 
                        c1=&a1->CMD;
                        printcmd(c1);
                        break;

      case READ_STOPTIMECNT: a1->CMD.seq= 26;
                             strcpy(a1->CMD.op_name,"read_stoptimecnt"); 
                             a1->CMD.number_param=0; 
                             c1=&a1->CMD;
                             printcmd(c1);
                             break;

      case READ_MAX_PWM_CNT: a1->CMD.seq= 27;
                             strcpy(a1->CMD.op_name,"read_Max_pwm_cnt"); 
                             a1->CMD.number_param=0; 
                             break;

      case READ_MAX_ANGLE: a1->CMD.seq= 28;
                           strcpy(a1->CMD.op_name,"read_Max_angle"); 
                           a1->CMD.number_param=0; 
                           c1=&a1->CMD;
                           printcmd(c1);
                           break;

      case READ_MIN_ANGLE: a1->CMD.seq= 29;
                           strcpy(a1->CMD.op_name,"read_Min_angle"); 
                           a1->CMD.number_param=0; 
                           break;

      case RUN_TO_CAL: a1->CMD.seq= 30;
                       strcpy(a1->CMD.op_name,"run_to_cal"); 
                       a1->CMD.number_param=0; 
                       c1=&a1->CMD;
                       printcmd(c1);
                       break;

      case FREE_RUN_TOW: a1->CMD.seq= 31;
                         strcpy(a1->CMD.op_name,"free_run_tow"); 
                         a1->CMD.number_param=1;
                         fprintf(stderr,"Enter 0-towards 270deg / 1-towards -10deg::\n");
                         scanf("%x",&x);
                         sprintf(a1->CMD.Argument_Ch1[0],"%d",x);
                         sprintf(a1->CMD.Argument_Ch2[0],"%d",y);
                         c1=&a1->CMD;
                         printcmd(c1);
                         break;

       case RUN_TO_PRESET: a1->CMD.seq= 32;
                           strcpy(a1->CMD.op_name,"run_to_preset");
                           a1->CMD.number_param=1;
                           strcpy(a1->CMD.parameter_name[0],"tar_encr_v");
                           fprintf(stderr,"\n Enter target encoder value:\n");
                           scanf("%d",&x);
                           x = x/2;
                           y = x & 0x00ff;
                           sprintf(a1->CMD.Argument_Ch1[0],"%d",y);  
                           x = x >> 8;
                           sprintf(a1->CMD.Argument_Ch2[0],"%d",x);
                           c1=&a1->CMD;
                           printcmd(c1);
                           break;

        case RUN_FINE_TUNE: a1->CMD.seq= 33;
                            strcpy(a1->CMD.op_name,"run_fine_tune"); 
                            a1->CMD.number_param=2; 
                            strcpy(a1->CMD.parameter_name[0],"tar_encr_v");
                            fprintf(stderr,"\n Enter target encoder value:\n");
                            scanf("%d",&x);
                            x = x/2;
                            y= x & 0x00ff;
                            sprintf(a1->CMD.Argument_Ch1[0],"%d",y);  
                            x = x >> 8;
                            sprintf(a1->CMD.Argument_Ch2[0],"%d",x);
                            fprintf(stderr,"\nEnter PWM cnt:\n");
                            strcpy(a1->CMD.parameter_name[1],"target_encoder_value");
                            scanf("%x",&x);
                            sprintf(a1->CMD.Argument_Ch1[1],"%x",x);  
                            sprintf(a1->CMD.Argument_Ch2[1],"%d",x);
                            c1=&a1->CMD;
                            printcmd(c1);                     
                            break;

         case PASSWORD_RUN: a1->CMD.seq= 34;
                            strcpy(a1->CMD.op_name,"password_run"); 
                            a1->CMD.number_param=0; 
                            c1=&a1->CMD;
                            printcmd(c1);
                            break;

         case REBOOT: a1->CMD.seq= 35;
                      strcpy(a1->CMD.op_name,"reboot"); 
                      a1->CMD.number_param=0; 
                      c1=&a1->CMD;
                      printcmd(c1);
                      break;

         case FPSSTOP: a1->CMD.seq= 36;
                       strcpy(a1->CMD.op_name,"stop"); 
                       a1->CMD.number_param=0; 
                       c1=&a1->CMD;
                       printcmd(c1);
                       break;
    }
     
}

void loadparam()
{
  char string[128];
  int load[4];
   char *file_name;
   FILE *f;

   file_name = "/home/teleset/Online_v2/Online/fpslist/fpspos.dat";
   
    f = fopen(file_name,"r"); // read mode
    if( f == NULL )
      {
        fprintf(stderr,"Error while opening the fpspos.dat file.\n");
        
      }
    while(fgets(string,128,f))
    {
      if(*string =='#')continue;
      sscanf(string,"%d %d %d %d",&load[0],&load[1],&load[2],&load[3]);
    }
   fprintf(stderr,"#### FPS Data for 4 feed =>  %d %d %d %d \n",load[0],load[1],load[2],load[3]);
     loadpara[0]=load[0];
     loadpara[1]=load[1];
     loadpara[2]=load[2];
     loadpara[3]=load[3];
}

