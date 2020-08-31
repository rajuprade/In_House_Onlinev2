/***************************************************

  fpssystm.cpp
  ABCcom program, version 1.1
  L.Pommier, Jan 2006.
  
***************************************************/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pthread.h>

#include "fpssystm.h"

extern "C" {
  void *HelperFSYS(void *_target);
}

void *HelperFSYS(void *_target)
{
  Fpssystm *target = (Fpssystm *)_target;
  target->Start();
  return NULL;
}


/******************************************************************************
 Fpssystm class functions
******************************************************************************/  
Fpssystm::Fpssystm(FileMcm *file0) : SysBase<LowfWrite, LowfRead>(file0, FPSINDX)
{
  NbparamSet = 1; NbparamLoad = 4;
  AnsStatus = FpsStatus = 0;
  pthread_create(&thFps, NULL, HelperFSYS, this); 
}

Fpssystm::~Fpssystm()
{
  CmdCode = 0x08;
  pthread_join(thFps, NULL);
}

void Fpssystm::AnalyseCom()
{
  if (CmdCode & 0x01) Write(INITINDX);
  if (CmdCode & 0x02) Write(MVINDX);
  if (CmdCode & 0x04) Write(DIRECTINDX);
}

void Fpssystm::Write(int indx)
{
  int ret=0, i;

  FileRec->TimeStamp();
  switch (indx) {
    case INITINDX:
      *FileRec->fd << "Init Start.\n";
      ret = Initfps();
      CmdCode &= 0xfe; break;
    case MVINDX:
      *FileRec->fd << "Mv start.\nParam: ";
      for (i=0;i<NbparamSet;i++) *FileRec->fd << " " << Setparam[i];
      *FileRec->fd << endl;
      ret = Mvfps();
      CmdCode &= 0xfd; HardRecordOn(); break;
    case DIRECTINDX:        
      ret = DirectCmd(DIRECTINDX);
      CmdCode &= 0xfb; break;
  }
  if (!ret && (indx > 0) && (CmdState[0] & 0x01)) CmdState[0] = 0x08;
  if (!ret) CmdState[indx] = 0x01;
  else CmdState[indx] = 0x02;
}

int Fpssystm::Initfps()
{
  int angle, x , y;
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

  Copy(-1, INITINDX);
  return 0;
}

int Fpssystm::Mvfps()
{
  int pos;

  if (!(CmdState[MVINDX] & 0x80)) {
    CmdState[MVINDX] |= 0x02;
    return 0;
  }
  switch ((int)Setparam[0]) {
    case 610: pos = (int)Loadparam[0]; break;
    case 150: pos = (int)Loadparam[1]; break;
    case 1420: pos = (int)Loadparam[2]; break;
    case 325: pos = (int)Loadparam[3]; break;
    default: return 1;
  }
  pos /= 2;
  CurrentCmd.Argument[0] = pos & 0x00ff;
  CurrentCmd.Argument[1] = pos>>8;
  CurrentCmd.CmdNum = 23;
  Copy(1, MVINDX);           //run to preset

  Copy(-1, MVINDX);
  return 0;
}

void Fpssystm::PostRead(int indx, int fail, int warn, ListMcm* list_ptr)
{
  SysBase<LowfWrite, LowfRead>::PostRead(indx, fail, warn, list_ptr);
  if (fail <= 0) { 
    AnsStatus = Rx->DecodeBuffer(list_ptr->Ans);
    DecodeList(list_ptr);
  }
  else DataPlus.Length = 0;
}

void Fpssystm::DecodeList(ListMcm* list_ptr)
{
  int i;

  FpsStatus = list_ptr->Ans.Msg[9];
  DecodeStatus(FpsStatus);
  EncCount = (list_ptr->Ans.Msg[10] + (list_ptr->Ans.Msg[11]<<8))*2;
  Rpm = (list_ptr->Ans.Msg[12]*5*60.0)/(2048.0) * 300.0;
  if ((int)list_ptr->Ans.Msg[5] == 2) {
    DataPlus.Length = list_ptr->Ans.Msg[13] + (list_ptr->Ans.Msg[14]<<8);
    for (i=0;i<DataPlus.Length;i++) DataPlus.Msg[i] = list_ptr->Ans.Msg[13+i];
  }
  else DataPlus.Length = 0;
  TimeStamp();     cout << "FPS list answered\n";
}

void Fpssystm::DecodeStatus(const char stat)
{
  char cur = stat;

  switch(cur) {
    case 0x42: *FileRec->fd << "280 Limit Hit "; break;
    case 0x43: *FileRec->fd << "-10 Limit Hit ";
  }
  cur &= 0xfe;
  switch(cur) {
    case 0x00: *FileRec->fd << "Feed Calibrated & Idle "; break;
    case 0x40: *FileRec->fd << "Feed Un-Calibrated "; break;
    case 0x08: *FileRec->fd << "Busy - Preset Run "; break;
    case 0x10: *FileRec->fd << "Busy - Free Run "; break;
    case 0x4a: *FileRec->fd << "Busy - Passworded Run "; break;
    case 0x0c0: *FileRec->fd << "Busy - In Calibration "; break;
    case 0x28: *FileRec->fd << "Jammed - Preset Run "; break;
    case 0x30: *FileRec->fd << "Jammed - Free Run "; break;
    case 0x0e0: *FileRec->fd << "Jammed - In Calibration "; break;
    case 0x62: *FileRec->fd << "Jammed - Passworded Run "; break;
    case 0x20: *FileRec->fd << "Jammed "; break;
    case 0x0ff: *FileRec->fd << "Ua0 Offset Progressing ";
  }
  *FileRec->fd << flush;
}

void Fpssystm::Reconfigure(int Sysno)
{  
  sleep(1);
//time to fully construct inherited obj, otherwise call set as pure virtual->error
// can be usefull also to MCMs
  CmdCode = 3;
}

void Fpssystm::AutoSys()
{
  CurrentCmd.CmdNum = 1;    //null cmd
  CmdCode |= 0x04;
}









