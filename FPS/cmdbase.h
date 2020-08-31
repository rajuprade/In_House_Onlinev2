/***************************************************

  cmdbase.h
  Teleset program, version 1.1
  L.Pommier, March 2006.

***************************************************/

#ifndef H_CMDBASE_H
#define H_CMDBASE_H

#include "common.h"
#include "sharemem.h"

/******************************************************************************
 CmdBase class declaration
 abstract base class to push data in packets to ABCcom
 and to write in Shared Memory
 inherited by: CmdSys, CmdAbc, CmdFps, CmdExp, CmsSsc
******************************************************************************/ 
class CmdBase {
  public:
    CmdBase(LogFile *FileRec0, SetData *SetShare0, int UserIndx0, int SysNo0);
    virtual ~CmdBase();
    int GetCmd(MSG *Tx0, ifstream *fdinput0);
    ifstream *Fdinput;
  protected:
    int SysNo, UserIndx;
    MSG* Tx;
    LogFile *FileRec;
    SetData *SetShare;
    virtual int GetPacket() = 0;
    inline void Txpush(char *str);
    inline void Txpush(unsigned char param);
    inline void Txpush(int param);
    inline void Txpush(int param, int len);
    inline void Txpush(float param);
    inline void Txpushcoma();
    inline void Txpopcoma();         //for SSC 
    void StoreArrMem(int indx, const float param);
    void StoreAbcMem(int antnb, int indx, const float param);
};


/******************************************************************************
 CmdSsc class declaration
 compose commands to Servo system
******************************************************************************/ 
class CmdSsc : public CmdBase {
  public:
    CmdSsc(LogFile *FileRec0, SetData *SetShare0, int UserIndx0);
    ~CmdSsc();
  private:
    virtual int GetPacket();
    void Trkon();
    void Trkrate();
    void Trkset();
    void ServoCmd();
    void AskAx();
    void AskAng();
    void AskTime();
    void AskDate();
    void AskWindvel();
};


/******************************************************************************
 CmdAbc class declaration
 compose commands to ABC system
******************************************************************************/ 
class CmdAbc : public CmdBase {
  public:
    CmdAbc(LogFile *FileRec0, SetData *SetShare0, int UserIndx0);
    ~CmdAbc();
  private:
    virtual int GetPacket();
    void UpdateFlag(const char cmd);
};


/******************************************************************************
 CmdExp class declaration
 compose commands to EXP system
******************************************************************************/ 
class CmdExp : public CmdBase {
  public:
    CmdExp(LogFile *FileRec0, SetData *SetShare0, int UserIndx0);
    virtual ~CmdExp();
  private:
    virtual int GetPacket();
    int CheckFlag() const;
};  


/******************************************************************************
 CmdFps class declaration
 compose commands to FPS system
******************************************************************************/
class CmdFps : public CmdBase {
  public:
    CmdFps(LogFile *FileRec0, SetData *SetShare0, int UserIndx0);
    virtual ~CmdFps();
  private:
    virtual int GetPacket();
    int FpsDirect();
    int GetFpsLoad();
};      
            

/******************************************************************************
 CmdBase class inline functions
******************************************************************************/ 
inline void CmdBase::Txpush(char *str)
{
  unsigned int i;
  for (i=0;i<strlen(str);i++) Tx->Msg[Tx->Length++] = str[i];
  Txpushcoma();
}

inline void CmdBase::Txpush(unsigned char param) {Tx->Msg[Tx->Length++] = param;}

inline void CmdBase::Txpush(float param)
{
  if ((param > +99999.9999)||(param < -99999.9999)) param = 0;    
  sprintf((char *)&Tx->Msg[Tx->Length], "%+12.4f,", param);
  //if small error, float limitation -> go for double
  Tx->Length += 13;
}

inline void CmdBase::Txpush(int param, int len)
{
  Tx->Msg[Tx->Length++] = param & 0x00ff;
  if (len == 2) Tx->Msg[Tx->Length++] = param >> 8;
}

inline void CmdBase::Txpush(int param) {
Txpush(param, 1);
}

inline void CmdBase::Txpushcoma() {Tx->Msg[Tx->Length++] = ',';}

inline void CmdBase::Txpopcoma() {Tx->Length--;}


#endif //H_CMDBASE_H


