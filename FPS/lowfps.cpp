/***************************************************

  lowmcm.cpp
  ABCcom program, version 1.1
  L.Pommier, Jan 2006.
  
***************************************************/

#include <iostream>
#include <fstream>

#include "lowfps.h"


/******************************************************************************
 LowfWrite class functions
******************************************************************************/ 
LowfWrite::LowfWrite(ofstream *fdrec0) {fdrec = fdrec0;}
LowfWrite::~LowfWrite() {;}

/******* Add Check Sum function *********************
 * Add CS at the end of the buffer
 * CS does no include MCM Address                  */
void LowfWrite::AddCksum(unsigned char *buff)
{
  int length, i;
  char cs = 0;

  length = *(buff+1) + (*(buff+2)<<8);
  for(i=1; i<length; i++) cs += *(buff+i);
  cs = ~cs+1;
  buff[length] = cs;
}

/******* Make buffer function ***********************
 * Prepare Cmd buffer ccording to Cmd Number
 * call sub functions for argument setting
 * set MCM address in the buffer
 * add CS                                          */
void LowfWrite::MakeBuffer(CMD Cmd, unsigned char FpsAddr, MSG* const Buf)
{
  buf_ptr0 = Buf->Msg;
  *buf_ptr0 = FpsAddr; *fdrec << "Mcm : " << (int)FpsAddr << "\t";
  if (Cmd.CmdNum == 1) {                //null
    char buff[]={0,8,0,0,0,0,0,0,0};
    InitBuff(buff);
  }
  else if (Cmd.CmdNum < 11) {           //set
    if ((Cmd.CmdNum == 2)||(Cmd.CmdNum == 4)||(Cmd.CmdNum == 9)||(Cmd.CmdNum == 10))
      set_twob_arg(Cmd.CmdNum, Cmd.Argument);
    else set_oneb_arg(Cmd.CmdNum, Cmd.Argument);
  }
  else if (Cmd.CmdNum < 21) {           //read
    char buff[]={0,9,0,0,2,0,1,0,0,0};
    buff[8] = Cmd.CmdNum - 11;
    InitBuff(buff);
  }
  else switch (Cmd.CmdNum) {
    case 21 : {
      char buff[]={0,9,0,0,3,0,1,0,0,0};
      InitBuff(buff); break;
    }
    case 22 : run_free(Cmd.Argument); break;
    case 23 : run_preset(Cmd.Argument); break;
    case 24 : run_fine(Cmd.Argument); break;
    case 25 : {
      char buff[]={0,9,0,0,3,0,1,0,4,0};
      InitBuff(buff); break;
    }
    case 26 : {
      char buff[]={0,8,0,0,5,0,0,0,0};
      InitBuff(buff); break;
    }
    case 27 : {
      char buff[]={0,8,0,0,6,0,0,0,0};
      InitBuff(buff);
    }
  }
  AddCksum(buf_ptr0);
  Buf->Length = *(buf_ptr0+1) + (*(buf_ptr0+2)<<8) + 1;
}

/******* Init buffer function ***********************
 * Make buffer sub function
 * convenient for buffer implementation            */
void LowfWrite::InitBuff(char buff[])
{
  int i, length;
  length = buff[1] + (buff[2]<<8);
  for (i=1; i<length; i++) *(buf_ptr0+i) = buff[i];
}

void LowfWrite::set_oneb_arg(int CmdNum, const unsigned char Arg[])
{
  char buff[]={0,0xa,0,0,1,0,2,0,0,0,0};

  buff[8] = CmdNum-2;
  buff[9] = Arg[0];
  InitBuff(buff);
}

void LowfWrite::set_twob_arg(int CmdNum, const unsigned char Arg[])
{
  char buff[]={0,0xb,0,0,1,0,3,0,0,0,0,0};

  buff[8] = CmdNum-2;
  buff[9] = Arg[0]; buff[10] = Arg[1];
  InitBuff(buff);
}

void LowfWrite::run_free(const unsigned char Arg[])
{
  char buff[]={0,0xa,0,0,3,0,2,0,1,0,0};

  buff[9] = Arg[0];
  InitBuff(buff);
}

void LowfWrite::run_preset(const unsigned char Arg[])
{
  char buff[]={0,0xb,0,0,3,0,3,0,2,0,0,0};

  buff[9] = Arg[0]; buff[10] = Arg[1];
  InitBuff(buff);
}

void LowfWrite::run_fine(const unsigned char Arg[])
{
  char buff[]={0,0xc,0,0,3,0,4,0,3,0,0,0,0};

  buff[9] = Arg[0]; buff[10] = Arg[1]; buff[11] = Arg[2];
  InitBuff(buff);
}


/******************************************************************************
 LowfRead class functions
******************************************************************************/ 
LowfRead::LowfRead(ofstream *fdrec0) {fdrec = fdrec0; Watchdogflag = Overcurrentflag = 0;}
LowfRead::~LowfRead(void) {;}      

/******* First Decode function ***********************
 * Decode MCM response main header
 * Check CS                                         */
int LowfRead::DecodeBuffer(const MSG CmdRx)
{
  char CmdStatus[8][100];
  int nbCmdStt=0, i;
 
  if (CmdRx.Msg[0] != 14)
    {sprintf(CmdStatus[nbCmdStt++], "Not FPS 14 packet"); return 0xff;}
 
  if (CmdRx.Msg[4] & 0x01) sprintf(CmdStatus[nbCmdStt++], "FPS detected timeout");
  if (CmdRx.Msg[4] & 0x02) sprintf(CmdStatus[nbCmdStt++], "FPS detected CS error");
  if (CmdRx.Msg[4] & 0x04) sprintf(CmdStatus[nbCmdStt++], "FPS received unknown cmd");
  if (CmdRx.Msg[4] & 0x08) sprintf(CmdStatus[nbCmdStt++], "FPS received too long packet");
  if (CmdRx.Msg[4] & 0x10) sprintf(CmdStatus[nbCmdStt++], "FPS received correct packet but rejected cmd");
  if (CmdRx.Msg[4] & 0x20) {
    if (!Watchdogflag) sprintf(CmdStatus[nbCmdStt++], "Watchdog reset");
    Watchdogflag = 1;
  }
  else Watchdogflag = 0;
  if (CmdRx.Msg[4] & 0x40) {
    if (!Overcurrentflag) sprintf(CmdStatus[nbCmdStt++], "Over Current");
    Overcurrentflag = 1;
  }
  else Overcurrentflag = 0;                                           
  for (i=0;i<nbCmdStt;i++) *fdrec << "\t\t\t" << CmdStatus[i] << endl;
  return CmdRx.Msg[4];
}



    


