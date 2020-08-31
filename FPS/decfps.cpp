/***************************************************

  decfps.cpp
  Teleset program, version 1.1
  L.Pommier, March 2006.

***************************************************/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
                    
#include "decfps.h"

/******************************************************************************
 DecFps class functions
******************************************************************************/
DecFps::DecFps(LogFile *FileRec0) : DecBase<SysBlock<FpsState> >(FileRec0)
{Watchdogflag = Overcurrentflag = 0;}

DecFps::~DecFps() {;}

void DecFps::AnsName(int code)
{
  switch (code) {
    case 0x05: *FileRec->fd << "init "; break;
    case 0x07: *FileRec->fd << "loadcnt "; break;
    case 0x09: *FileRec->fd << "mvpos "; break;
    case 0x0b: *FileRec->fd << "montime "; break;
    case 0x0d: *FileRec->fd << "cmd "; break;
    default: *FileRec->fd << "unknown, error "; 
  }
}

int DecFps::AnalyseState(int siz)  
{
  int i, monck=0;
  unsigned char current;
  string str;
  
  MemDat = 0;
  while (!MemDat) MemDat = MemBlock->List.GetWrState(); 
  ReadMcmTimOut();
  for (i=0;i<3;i++) {
    switch (i) {
      case 0: str = "Init: "; break;
      case 1: str = "MvIndx: "; break;
      case 2: str = "Direct Cmd: ";
    }
    TOpop(&current);
    if ((current == 0x00) || ((i==1)&&(current & 0x80))) str += "--";
    if (current & 0x01) str += "in process";
    if (current & 0x02) {
      str += "failed";
      if ((i == 1) && !(current & 0x80)) str += ", no load param";
    }
    if (current & 0x04) str += "done";
    if (current & 0x08) str += "discarded";
    if (str.length() < 40) strcpy(MemDat->CmdState[i], str.c_str());
    *FileRec->fd << str << endl;
  }

  TOpop(MemDat->Montime);
  for (i=0;i<8;i++) {monck += MemDat->Montime[i];} //cout << Sys0->Montime[i] << endl;}
  if (monck) {
    TOpop(&MemDat->EncCount, 2);
    *FileRec->fd << "EncCount " << MemDat->EncCount;
    TOpop(&MemDat->Rpm);
    *FileRec->fd << "Rpm " << MemDat->Rpm;
    DecCmdStatus();
    DecFpsStatus();
  }
  DecodePack();
  MemBlock->List.WrInc();
  return 1;
}
  

void DecFps::DecFpsStatus()
{
  unsigned char current;
  string str;

  TOpop(&current);
  switch(current) {
    case(0x42): str += "280 Limit Hit  "; break;
    case(0x43): str += "-10 Limit Hit   ";
  }
  current &= 0xfe;
  switch(current) {
    case(0x00): str += "Feed Calibrated & Idle  "; break;
    case(0x40): str += "Feed Un-Calibrated   "; break;
    case(0x08): str += "Busy - Preset Run  "; break;
    case(0x10): str += "Busy - Free Run  "; break;
    case(0x4a): str += "Busy - Passworded Run  "; break;
    case(0x0c0): str += "Busy - In Calibration  "; break;
    case(0x28): str += "Jammed - Preset Run  "; break;
    case(0x30): str += "Jammed - Free Run  "; break;
    case(0x0e0): str += "Jammed - In Calibration  "; break;
    case(0x62): str += "Jammed - Passworded Run  "; break;
    case(0x20): str += "Jammed   "; break;
    case(0x0ff): str += "Ua0 Offset Progressing  ";
  }
  if (str.length() < 100) strcpy(MemDat->FpsStatus, str.c_str());
  *FileRec->fd << str << endl; 
}


void DecFps::DecCmdStatus()
{
  unsigned char current;
  string str;
                       
  TOpop(&current);
  if (current == 0) str += "Exec. Ok";
  if (current & 0x01) str += "FPS detected timeout";
  if (current & 0x02) str += "FPS detected CS error";
  if (current & 0x04) str += "FPS received unknown cmd";
  if (current & 0x08) str += "FPS received too long packet";
  if (current & 0x10) str += "FPS received correct packet but rejected cmd";
  if (current & 0x20) {
    if (!Watchdogflag) str += "Watchdog reset";
    Watchdogflag = 1;
  }
  else Watchdogflag = 0;
  if (current & 0x40) {
    if (!Overcurrentflag) str += " Over Current";
    Overcurrentflag = 1;
  }
  else Overcurrentflag = 0;
  if (str.length() < 200) strcpy(MemDat->CmdStat, str.c_str());
  *FileRec->fd << str << endl;
}


void DecFps::DecodePack()
{
  unsigned char current;
  int siz, next;
  string s;

  TOpop(&siz, 2);
  if (!siz) {s = " -- "; return;}
  TOpop(&siz, 2);
  TOpop(&current);
  if (current == 0) {s = "Null Cmd "; DecodeNull(&s);}
  else if (current == 1) {
    s = "Set ";
    DecodeSet(&s);
  }
  else if (current == 2) {
    s = "Read ";
    DecodeRead(&s);
  }
  else if (current == 3) {
    TOpop(&next);
    s ="Run ";
    switch (next) {
      case 0 : s += "to Calibrate"; break;
      case 1 : s += "Free"; break;
      case 2 : s += "to Preset"; break;
      case 3 : s += "to Fine Tune"; break;
      case 4 : s += "Passworded"; break;
      case 5 : s += "to Ua0";
    }

  }
  else if (current == 5) s = "Reboot";
  else if (current == 6) s = "Stop";
  else s = "Not implemented" ;
  if (s.length() < 200) strcpy(MemDat->Message, s.c_str());
  *FileRec->fd << s << endl;
}

void DecFps::DecodeNull(string* sptr)
{
  unsigned char current;
  char s[10];
                                
  TOpop(&current);
  if (!(current & 0x01)) *sptr += "mode MAN ";
  else *sptr += "mode AUTO ";
  if (!(current & 0x02)) *sptr += "rgso OFF";
  else *sptr += "rgso ON ";
  *sptr += "\n" ;
  if (!(current & 0x04)) *sptr += "dir 270";
  else *sptr += "dir -10 ";
  if (!(current & 0x08)) *sptr += "fv OFF";
  else *sptr += "fv OK ";
  if (!(current & 0x10)) *sptr += "t80l OK ";
  else *sptr += "t80l HIT";
  *sptr += "\n" ;
  if (!(current & 0x20)) *sptr += "t70l OK ";
  else *sptr += "t70l HIT";
  if (!(current & 0x40)) *sptr += "n5l OK ";
  else *sptr += "n5l HIT";
  if (!(current & 0x80)) *sptr += "n10l OK ";
  else *sptr += "n10l HIT";

  TOpop(&current);
  sprintf(s, "%f", (float)((current)/12.5));
  *sptr += "Motor cur "; *sptr += s;
/* //not activated yet:
  buf++;
  sptr->append( "Brake cur %f", (float)((current)/127.5));
  buf++;
  sptr->append( "CPU 5vdc %f", (float)((current)/51.0));
  buf++;
  sptr->append( "Enc 5vdc %f", (float)((current)/51.0)); */   
}

void DecFps::DecodeSet(string* sptr)
{
  unsigned char current;

  TOpop(&current);
  DecodeArg(current, sptr);
  if (current == 9) sptr->append( " Write Addr");
  else if (current == 10) sptr->append( " Load Count");
}

void DecFps::DecodeRead(string* sptr)
{
  int temp;
  unsigned char current;
  char s[10];

  TOpop(&current);
  DecodeArg(current, sptr);
  if (current == 9) {
    TOpop(&temp);
    sprintf(s, "%f", (float)temp/10);
    *sptr += " Version: "; *sptr += s;
  }
  else if (current == 10) {
    TOpop(&temp, 2);
    sprintf(s, "%d", temp*2);
    *sptr +=  " Ua0 position: "; *sptr += s;
  }
}

void DecFps::DecodeArg(unsigned char current, string* sptr)
{
  int temp, tp0, tp1;
  char s[10], s2[10];

  switch((int)current) {
    case 0:
      TOpop(&temp, 2);
      sprintf(s, "%d", temp*2);
      *sptr += " Turning Point, target: "; *sptr += s; break;
    case 1:
      TOpop(&temp);
      sprintf(s, "%d", temp*5);
      *sptr += " Ramp Down Count, slope: "; *sptr += s; break;
    case 2:
      TOpop(&tp0); TOpop(&tp1);
      temp = (int)((tp1/0.2048*1800.0/(tp0*5)));
      sprintf(s, "%d", temp); sprintf(s2, "%d", tp0*5);
      *sptr += " Lower Rpm Limit, "; *sptr += s; *sptr += ", int "; *sptr += s2; break;
    case 3:
      TOpop(&temp);
      sprintf(s, "%d", temp*2);
      *sptr += " Break Count Diff, "; *sptr += s; break;
    case 4:
      TOpop(&temp);
      sprintf(s, "%d", temp*5);
      *sptr += " Rampup Count, "; *sptr += s; break;
    case 5:
      TOpop(&temp);
      sprintf(s, "%d", temp*5);
      *sptr += " Stop Count, "; *sptr += s; break;
    case 6:
      TOpop(&temp);
      sprintf(s, "%x", temp);
      *sptr += " Max PWM Count, "; *sptr += s; break;
    case 7:
      TOpop(&temp, 2);
      sprintf(s, "%d", temp*2);
      *sptr += " Max Angle, "; *sptr += s; break;
    case 8:
      TOpop(&temp, 2);
      sprintf(s, "%d", temp*2);
      *sptr += " Min Angle, "; *sptr += s; break;
  }
  sptr->append( s );
}                     
                                 








