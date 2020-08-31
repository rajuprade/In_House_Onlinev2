/*****************************************************

  comsys.cpp
  ABCcom program, version 1.1
  L.Pommier, Jan 2006.
  
***************************************************/

#include <fstream>
#include <iostream>
#include <unistd.h>

#include "comsys.h"
#include "losystm.h"
#include "ifsystm.h"
#include "fesystm.h"
#include "sysbase.h"
#include "fpssystm.h"

#include "sentisystm.h"

/******************************************************************************
 Comsys class functions
******************************************************************************/ 
Comsys::Comsys(MSG* ToOnl0, int SysNo0, ofstream* fd0, int AbcAddr0)
 : Comsysbase<SystM>(ToOnl0, SysNo0, fd0, AbcAddr0)
{;}

Comsys::~Comsys()
{;}

// returns 0 if error, 1 if ans ack only, 2 if ans with param
int Comsys::Cmdpacket()
{  
  int cmd;

  if (Sys == NULL) {*fd << "Sys missing\n"; return 0;}
  *fd << "Command to ";
  switch (Sys->SystNum) {
    case 3: *fd << "LO: "; break;
    case 4: *fd << "IF: "; break;
    case 5: *fd << "FE: "; break;
    case 8: *fd << "SENTINAL: ";
  }  
  FromOnl->Length += 3;
  FOpop(&cmd);
  switch (cmd) {
    case 0x00: *fd << "AnswerState.\n";  AnswerState(); return 2;
    case 0x02: *fd << "AskParam.\n";  AskParam(); return 2;
    case 0x04: *fd << "Reboot.\n";  Sys->CmdCode |= 0x04; break;
    case 0x06:
      *fd << "Setnew.\n";
      if (Setparam()) break;
      else return 0;
    case 0x08: *fd << "Doset.\n";  Sys->CmdCode |= 0x02; break;
    case 0x0a: *fd << "Domon.\n";  Sys->CmdCode |= 0x01; break;
    case 0x0c:
      *fd << "Montime.\n";
      FOpop(&Sys->MonInterval, 2); Sys->HardRecordOn();
  }
  if (cmd > 0x0c) return SubCmdpacket(cmd);    
  return 1;
}


void Comsys::AnswerState()
{
  int i, monck=0, sizptr;

  ToOnl->Msg[5]++;  
  sizptr = ToOnl->Length;
  ToOnl->Length += 2;
  TOpush(Sys->SystNum);
  TOpush(1);
  AnsTimOut();
  for (i=0;i<4;i++) {TOpush(Sys->CmdState[i]);}// cout << hex << (int)Sys0->CmdState[i] <<  endl;}
  TOpush(Sys->CmdSys);    
  TOpush(Sys->StateSys); //cout << hex << (int)Sys0->StateSys <<  endl;  
  for (i=0;i<8;i++) {monck += Sys->Montime[i];} //cout << Sys0->Montime[i] << endl;}
  TOpush(Sys->Montime);     
  if (monck) {
    TOpush(Sys->MonResult);
    if (Sys->MonResult != 0) {
      TOpush(Sys->DataPlus.Length, 2);  
      for (i=0;i<Sys->DataPlus.Length;i++)
        TOpush(Sys->DataPlus.Msg[i]);               
    }
    TOpush(Sys->NbVolt);  //cout << Sys0->NbVolt << endl;
    for (i=0;i<Sys->NbVolt;i++)
      TOpush(Sys->Monvolt[i]);
    for (i=0;i<8;i++) Sys->Montime[i] = 0;
  }    
  ToOnl->Msg[sizptr] = (ToOnl->Length - sizptr) & 0x00ff;
  ToOnl->Msg[sizptr+1] = (ToOnl->Length - sizptr) >> 8;
}


/******************************************************************************
 Comlo class functions
******************************************************************************/ 
Comlo::Comlo(FileMcm *file1, FileMcm *file2, MSG* ToOnl0, ofstream* fd0, int AbcAddr0)
 : Comsys(ToOnl0, LOINDX, fd0, AbcAddr0)
{
  Sys = new Losystm(file1, file2);
}

Comlo::~Comlo() {;}

int Comlo::SubCmdpacket(int cmd)
{
  switch (cmd) {
    case 0x0e: *fd << "cmd 0e rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 1; break;
    case 0x10: *fd << "cmd 10 rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 2; break;
    default: return 0;
  }
  return 1;
}


/******************************************************************************
 Comif class functions
******************************************************************************/ 
Comif::Comif(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0)
 : Comsys(ToOnl0, IFINDX, fd0, AbcAddr0)
{
  Sys = new Ifsystm(file);
}

Comif::~Comif() {;}

int Comif::SubCmdpacket(int cmd)
{
  int i;
  
  switch (cmd) {
    case 0x0e: *fd << "cmd 0e rx\n"; Loadparam(); break;
    case 0x10:
      *fd << "cmd 10 rx\n";
      for (i=0;i<4;i++) FOpop(&Sys->Setparam[i+6]);      
      Sys->CmdCode |= 0x10; Sys->CmdSys = 1; break;
    default: return 0;
  }
  return 1;
}



/******************************************************************************
 Comsenti class functions
******************************************************************************/
Comsenti::Comsenti(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0)
 : Comsys(ToOnl0, SENTINDX, fd0, AbcAddr0)
{
  Sys = new Sentisystm(file);
}

Comsenti::~Comsenti() {;}

int Comsenti::SubCmdpacket(int cmd)
{
  int i;

  switch (cmd) {
    case 0x0e: *fd << "cmd 0e rx\n"; Loadparam(); break;
    case 0x10:
      *fd << "cmd 10 rx\n";
      for (i=0;i<4;i++) FOpop(&Sys->Setparam[i+6]);
      Sys->CmdCode |= 0x10; Sys->CmdSys = 1; break;
    default: return 0;
  }
  return 1;
}



/******************************************************************************
 Comfe class functions
******************************************************************************/ 
Comfe::Comfe(FileMcm *file1, FileMcm *file2, MSG* ToOnl0, ofstream* fd0, int AbcAddr0)
 : Comsys(ToOnl0, FEINDX, fd0, AbcAddr0)
{
  Sys = new Fesystm(file1, file2);
}

Comfe::~Comfe() {;}

int Comfe::SubCmdpacket(int cmd)
{
  switch (cmd) {
    case 0x0e: *fd << "cmd 0e rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 1; break;
    case 0x10: *fd << "cmd 10 rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 2; break;
    case 0x12: *fd << "cmd 12 rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 3; break;
    case 0x14: *fd << "cmd 14 rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 4; break;
    case 0x16: *fd << "cmd 16 rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 5; break;
    case 0x18: *fd << "cmd 18 rx\n"; Sys->CmdCode |= 0x10; Sys->CmdSys = 6; break;
    default: return 0;
  }
  return 1;
}



/******************************************************************************
 Comexp class functions
******************************************************************************/ 
Comexp::Comexp(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0)
 : Comsysbase<Expsystm>(ToOnl0, EXPINDX, fd0, AbcAddr0)
{
  Sys = new Expsystm(file);
}

Comexp::~Comexp() {;}

// returns 0 if error, 1 if ans ack only, 2 if ans with param
int Comexp::Cmdpacket()
{
  int cmd, siz;

  if (Sys == NULL) {*fd << "Sys missing\n"; return 0;}
  *fd << "Command to EXP: ";
  siz = FromOnl->Msg[0] | (FromOnl->Msg[1]<<8);
  FromOnl->Length += 3;
  FOpop(&cmd);
  switch (cmd) {
    case 0x00: *fd << "AnswerState.\n"; AnswerState(); return 2;
    case 0x04:
      *fd << "Direct Cmd.\n";
      Directpacket(siz); Sys->CmdCode |= 0x01;
      break;
    default: return 0;
  }
  return 1;
}

void Comexp::AnswerState()
{
  int i, sizptr;

  ToOnl->Msg[5]++;
  sizptr = ToOnl->Length;
  ToOnl->Length += 2;
  TOpush(Sys->SystNum);
  TOpush(1);
  AnsTimOut();
  TOpush(Sys->CmdState[0]);
  TOpush(Sys->DataPlus.Length, 2);
  if (Sys->DataPlus.Length)
    for (i=0;i<Sys->DataPlus.Length;i++) TOpush(Sys->DataPlus.Msg[i]);
  ToOnl->Msg[sizptr] = (ToOnl->Length - sizptr) & 0x00ff;
  ToOnl->Msg[sizptr+1] = (ToOnl->Length - sizptr) >> 8;
}



/******************************************************************************
 Comfps class functions
******************************************************************************/ 
Comfps::Comfps(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0)
 : Comsysbase<Fpssystm>(ToOnl0, FPSINDX, fd0, AbcAddr0)
{
  Sys = new Fpssystm(file);
}

Comfps::~Comfps() {;}

// returns 0 if error, 1 if ans ack only, 2 if ans with param
int Comfps::Cmdpacket()
{
  int cmd, siz;             

  if (Sys == NULL) {*fd << "Sys missing\n"; return 0;}
  *fd << "Command to FPS: ";
  FOpop(&siz, 2);
  FOpop(&cmd);
  FOpop(&cmd);     
  switch (cmd) {
    case 0x00: *fd << "AnswerState.\n";  AnswerState(); return 2;
    case 0x02: *fd << "AskParam.\n"; AskParam(); return 2;
    case 0x04: *fd << "Init.\n"; Sys->CmdCode |= 0x01; break;
    case 0x06:
      *fd << "Loadcnt.\n";
      Loadparam();
      Sys->CmdState[MVINDX] |= 0x80; break;
    case 0x08:
      *fd << "Mvpos.\n";
       cout << "\n ######## MVPOS #######\n";
      Setparam();
      break;
    case 0x0a:Setparam();
      FOpop(&Sys->MonInterval, 2); Sys->HardRecordOn();
      *fd << Sys->MonInterval << "Montime.\n";
    case 0x0c:
      *fd << "Direct Cmd.\n";
      Directpacket(siz); Sys->CmdCode |= 0x04;
      break;
    default: return 0;
  }
  return 1;
}     

void Comfps::AnswerState()
{
  int i, monck=0, sizptr;

  ToOnl->Msg[5]++;
  sizptr = ToOnl->Length;
  ToOnl->Length += 2;
  TOpush(Sys->SystNum);
  TOpush(1);
  AnsTimOut();
  for (i=0;i<3;i++) {TOpush(Sys->CmdState[i]);}// cout << hex << (int)Sys0->CmdState[i] <<  endl;}
  TOpush(Sys->Montime);
  for (i=0;i<8;i++) {monck += Sys->Montime[i];} //cout << Sys0->Montime[i] << endl;}
  if (monck) {
    TOpush(Sys->EncCount, 2);
    TOpush(Sys->Rpm);
    TOpush(Sys->AnsStatus);
    TOpush(Sys->FpsStatus);
  }
  TOpush(Sys->DataPlus.Length, 2);
  if (Sys->DataPlus.Length) {
    cout << "fps 2nd pack\n";
    for (i=0;i<Sys->DataPlus.Length;i++) TOpush(Sys->DataPlus.Msg[i]);
  }
  ToOnl->Msg[sizptr] = (ToOnl->Length - sizptr) & 0x00ff;
  ToOnl->Msg[sizptr+1] = (ToOnl->Length - sizptr) >> 8;
}

















