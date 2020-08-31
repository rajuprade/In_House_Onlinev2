
/**************************************************

  decfps.h
  Teleset program, version 1.1
  L.Pommier, March 2006.

***************************************************/

#ifndef H_DECFPS_H
#define H_DECFPS_H      

#include "decode.h"
#include "sharemem.h"
  

/******************************************************************************
 DecFps class declaration
 decode FPS answer and write result in Shared Memory
******************************************************************************/ 
class DecFps : public DecBase<SysBlock<FpsState> > {
  public:
    DecFps(LogFile *FileRec0);
    virtual ~DecFps();
  private:
    int Watchdogflag, Overcurrentflag;
    FpsState *MemDat;
    virtual int AnalyseState(int siz);
    virtual void AnsName(int code);
    void DecFpsStatus();
    void DecCmdStatus();
    void DecodePack();
    void DecodeNull(string* sptr);
    void DecodeSet(string* sptr);
    void DecodeRead(string* sptr);
    void DecodeArg(unsigned char current, string* sptr);
};         
    

#endif //H_DECFPS_H


















