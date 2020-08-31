
#include"server.h"
/******* Sentinel *******/
void sentinel(cmd *c1)
{
   int op;
 /*  char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);*/
  // strcpy(c1->timestamp,stamp1);
   strcpy(c1->system_name,"sentinel");
    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;
      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=1;
               strcpy(c1->parameter_name[0],"dmask");
               strcpy(c1->Argument_Ch1[0],"ffff");
               strcpy(c1->Argument_Ch2[0],"5555"); 
               break;
      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");
               c1->number_param=0;
               break;
      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/*********** sentinel ******/


/******* fiber_optics *******/
void fiber_optics(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
  /*  char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);*/
   strcpy(c1->system_name,"fiber_optics");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=1;
               strcpy(c1->parameter_name[0],"rf_attn");
               strcpy(c1->Argument_Ch1[0],"25");
               strcpy(c1->Argument_Ch2[0],"35"); 
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/************** fiber_optics *****/

/******* back_end *******/
void back_end(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
  /* char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);*/
   strcpy(c1->system_name,"back_end");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=8;

                       strcpy(c1->parameter_name[0],"lo");
                       strcpy(c1->parameter_name[1],"attn");
                       strcpy(c1->parameter_name[2],"filter");
                       strcpy(c1->parameter_name[3],"lpf");
                       strcpy(c1->parameter_name[4],"source");
                       strcpy(c1->parameter_name[5],"ant_ns");
                       strcpy(c1->parameter_name[6],"drct_mxr");
                       strcpy(c1->parameter_name[7],"channel");

                       strcpy(c1->Argument_Ch1[0],"1600000");
                       strcpy(c1->Argument_Ch1[1],"10");
                       strcpy(c1->Argument_Ch1[2],"8");
                       strcpy(c1->Argument_Ch1[3],"0");
                       strcpy(c1->Argument_Ch1[4],"siggen");
                       strcpy(c1->Argument_Ch1[5],"antenna");
                       strcpy(c1->Argument_Ch1[6],"direct");
                       strcpy(c1->Argument_Ch1[7],"1");
    
                       strcpy(c1->Argument_Ch2[0],"1600000"); 
                       strcpy(c1->Argument_Ch2[1],"12");
                       strcpy(c1->Argument_Ch2[2],"6");
                       strcpy(c1->Argument_Ch2[3],"1");
                       strcpy(c1->Argument_Ch2[4],"synthesizer");
                       strcpy(c1->Argument_Ch2[5],"noise");
                       strcpy(c1->Argument_Ch2[6],"mixer");
                       strcpy(c1->Argument_Ch2[7],"2");
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/************** back_end *****/

/******* front_end *******/
void front_end(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
  /*  char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp);*/
   strcpy(c1->system_name,"front_end");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=7;

                       strcpy(c1->parameter_name[0],"cal_ns");
                       strcpy(c1->parameter_name[1],"rf");
                       strcpy(c1->parameter_name[2],"filter");
                       strcpy(c1->parameter_name[3],"fltr_bnd");
                       strcpy(c1->parameter_name[4],"band_sel");
                       strcpy(c1->parameter_name[5],"slr_attn");
                       strcpy(c1->parameter_name[6],"channel");

                       strcpy(c1->Argument_Ch1[0],"LO");
                       strcpy(c1->Argument_Ch1[1],"on");
                       strcpy(c1->Argument_Ch1[2],"1");
                       strcpy(c1->Argument_Ch1[3],"1060");
                       strcpy(c1->Argument_Ch1[4],"50");
                       strcpy(c1->Argument_Ch1[5],"44");
                       strcpy(c1->Argument_Ch1[6],"swap");
                       
    
                       strcpy(c1->Argument_Ch2[0],"Medium"); 
                       strcpy(c1->Argument_Ch2[1],"off");
                       strcpy(c1->Argument_Ch2[2],"4");
                       strcpy(c1->Argument_Ch2[3],"1170");
                       strcpy(c1->Argument_Ch2[4],"150");
                       strcpy(c1->Argument_Ch2[5],"30");
                       strcpy(c1->Argument_Ch2[6],"unswap");
                      
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}

/************** front_end *****/

/***************self_test **********/
void self_test(cmd *c1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(c1->timestamp,stamp1); */
 /*   char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(c1->timestamp,tstamp); */
   strcpy(c1->system_name,"self_test");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op);
    switch(op)
    {
      case 0:  c1->seq= 10;
               strcpy(c1->op_name,"mon");
               c1->number_param=0;
               break;

      case 1:  c1->seq= 11;
               strcpy(c1->op_name,"set");
               c1->number_param=3;
               strcpy(c1->parameter_name[0],"ss");// set spectrum spreader
               strcpy(c1->Argument_Ch1[0],"0");   // Range : 0,1,2,3
               strcpy(c1->parameter_name[1],"fdb");// set frequency doubler
               strcpy(c1->Argument_Ch1[1],"1");   // Range 0 or 1 
               strcpy(c1->parameter_name[2],"fdv");// set frequency divider
               strcpy(c1->Argument_Ch1[2],"2");   // Range 1,2,4,6,8   
               break;

      case 2:  c1->seq= 12;
               strcpy(c1->op_name,"init");      
               c1->number_param=0;
               break;

      case 3:  c1->seq= 13;
               strcpy(c1->op_name,"reset");
               c1->number_param=0;
               break;   
    }
     
}


/**************self_test **********/

void exec_cmd(int n,cmd *c1)
{

   switch(n)
   { 
     case 0:sentinel(c1); break;
     case 1:front_end(c1); break;
     case 2:fiber_optics(c1); break;
     case 3:back_end(c1); break;
     case 4:self_test(c1); break;
     default: break;
   }
}

