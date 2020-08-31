/**************************************************

  comsys.h
  ABCcom program, version 1.1
  L.Pommier, Jan 2006.
  
**************************************************/

#ifndef H_COMSYS_H
#define H_COMSYS_H
 
#include "common.h"
#include "systm.h"
#include "fpssystm.h"
#include "combase.h"

#include <fstream>
#include <iostream>
#include <unistd.h>


/******************************************************************************
 Comsysbase class declaration
 abstract base class for cmd + ans between a MCM system and Teleset
 inherited by: Comsys, Comexp, Comfps
******************************************************************************/ 
template <class S>
class Comsysbase : public Combase {
  public:
    Comsysbase(MSG* ToOnl0, int SysNo0, ofstream* fd0, int AbcAddr0);
    virtual ~Comsysbase();
    virtual void AnswerState() = 0;
  protected:
    S *Sys;
    virtual int Cmdpacket() = 0; 
    void AskParam();
    int Setparam();
    int Loadparam();
    void Directpacket(int siz);
    void AnsTimOut();
};


/******************************************************************************
 Comsys class declaration
 abstract base class for cmd + ans between a SystM object and Teleset
 inherited by: Comlo, Comif, Comfe,ComSenti.
******************************************************************************/ 
class Comsys : public Comsysbase<SystM> {
  public:
    Comsys(MSG* ToOnl0, int SysNo0, ofstream* fd0, int AbcAddr0); 
    virtual ~Comsys();
    virtual void AnswerState();
  protected:
    virtual int Cmdpacket();      
    virtual int SubCmdpacket(int cmd) = 0;
};


/******************************************************************************
 Comlo class declaration
 class for cmd + ans between Losystm and Teleset
******************************************************************************/ 
class Comlo : public Comsys {
  public:
    Comlo(FileMcm *file1, FileMcm *file2, MSG* ToOnl0, ofstream* fd0, int AbcAddr0);
    virtual ~Comlo();
  protected:
    virtual int SubCmdpacket(int cmd);
};


/******************************************************************************
 Comif class declaration
 class for cmd + ans between Ifsystm and Teleset
******************************************************************************/ 
class Comif : public Comsys {
  public:
    Comif(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0);
    virtual ~Comif();
  protected:
    virtual int SubCmdpacket(int cmd);
    int Findparam();
};


/******************************************************************************
 Comfe class declaration
 class for cmd + ans between Fesystm and Teleset
******************************************************************************/ 
class Comfe : public Comsys {
  public:
    Comfe(FileMcm *file1, FileMcm *file2, MSG* ToOnl0, ofstream* fd0, int AbcAddr0);
    virtual ~Comfe();
  protected:
    virtual int SubCmdpacket(int cmd);
};

/****************************************************************************
Com Senticlass declaration
class for Cmd ans between SentinalSystem and Teleset
********************************************************************************/

class Comsenti :public Comsys {
public:
   Comsenti(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0);
   virtual ~Comsenti();
   protected:
   virtual int SubCmdpacket(int cmd);
};


/******************************************************************************
 Comexp class declaration
 class for cmd + ans between Expsystm and Teleset
******************************************************************************/ 
class Comexp : public Comsysbase<Expsystm> {
  public:
    Comexp(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0);
    virtual ~Comexp();
    virtual void AnswerState();
  protected:
    virtual int Cmdpacket();
};


/******************************************************************************
 Comfps class declaration
 class for cmd + ans between Fpssystm and Teleset
******************************************************************************/ 
class Comfps : public Comsysbase<Fpssystm> {
  public:
    Comfps(FileMcm *file, MSG* ToOnl0, ofstream* fd0, int AbcAddr0);
    virtual ~Comfps();
    virtual void AnswerState();
  protected:
    virtual int Cmdpacket();
};


/******************************************************************************
 Comsysbase class functions
******************************************************************************/ 
template <class S>
Comsysbase<S>::Comsysbase(MSG* ToOnl0, int SysNo0, ofstream* fd0, int AbcAddr0)
 : Combase(ToOnl0, SysNo0, fd0, AbcAddr0)
{;}
template <class S>
Comsysbase<S>::~Comsysbase()
{
  delete Sys;
}

template <class S>
int Comsysbase<S>::Setparam()
{
  int i;
  float para;
  
  *fd << "Setparam received: ";              
  for (i=0;i<Sys->NbparamSet;i++) { 
    FOpop(&para);  
  cout << "\n =======> setparam " << para << endl;
    if ((para < -1)||(para > 18000)) return 0;
    Sys->Setparam[i] = para;
    *fd << Sys->Setparam[i] << "  ";
  }
  *fd << endl;
   Sys->CmdCode |= 0x02;
  return 1;
}

template <class S>
int Comsysbase<S>::Loadparam()
{
  int i, abcaddr;
  float para=0;

  FOpop(&abcaddr);     
  if (abcaddr != AbcAddr) return 0;
  *fd << "Loadparam received: ";
  for (i=0;i<Sys->NbparamLoad;i++) {
    FOpop(&para);     //cout << para << endl;
    if ((para < -1)||(para > 18000)) return 0;
    Sys->Loadparam[i] = para;
    *fd << Sys->Loadparam[i] << "  ";
  }
  *fd << endl << flush;
  return 1;
}


template <class S>
void Comsysbase<S>::AskParam()
{
  int i, sizptr;

  ToOnl->Msg[5]++;
  sizptr = ToOnl->Length;
  ToOnl->Length += 2;
  TOpush(Sys->SystNum);
  TOpush(0x03);
  TOpush(Sys->NbparamSet+1);     //MonInterval
  TOpush((float)Sys->MonInterval);    
  for (i=0;i<Sys->NbparamSet;i++) 
    TOpush(Sys->Setparam[i]); //cout << " " << Sys->Setparam[i] << endl;}  
  TOpush(Sys->NbparamLoad);
  for (i=0;i<Sys->NbparamLoad;i++)
    TOpush(Sys->Loadparam[i]); //cout << " " << Sys->Loadparam[i] << endl;}  
  ToOnl->Msg[sizptr] = (ToOnl->Length - sizptr) & 0x00ff;
  ToOnl->Msg[sizptr+1] = (ToOnl->Length - sizptr) >> 8;
}

template <class S>
void Comsysbase<S>::AnsTimOut()
{
  if (Sys->Mcm2) TOpush(2);
  else TOpush(1);
  TOpush(Sys->Mcm1->McmAddr); 
  TOpush(Sys->Mcm1->NbTimOut);
  if (Sys->Mcm2) {
    TOpush(Sys->Mcm2->McmAddr);   
    TOpush(Sys->Mcm2->NbTimOut);
  }
}

template <class S>
void Comsysbase<S>::Directpacket(int siz)
{
  int i=0;

  FOpop(&Sys->CurrentCmd.CmdNum);
  while (FromOnl->Length < siz) FOpop(&Sys->CurrentCmd.Argument[i++]);
}


#endif //H_COMSYS_H







