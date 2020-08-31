/*******************************************************

  fpssystm.h
  ABCcom program, version 1.1
  L.Pommier, Jan 2006.
  
*******************************************************/

  
#ifndef H_FPSSYSTM_H
#define H_FPSSYSTM_H

const int INITINDX = 0;
const int MVINDX = 1;
const int DIRECTINDX = 2;      // < 4 max limit as CmdState[4] in sysbase.h.

#include "common.h"
#include "lowfps.h"
#include "sysbase.h"


/******************************************************************************
 Fpssystm class declaration
 FPS system operations
******************************************************************************/ 
class Fpssystm : public SysBase<LowfWrite, LowfRead> {
  public:
    Fpssystm(FileMcm *file0);
    virtual ~Fpssystm();
    int EncCount;
    float Rpm;
    unsigned char AnsStatus, FpsStatus;
  private:
    pthread_t thFps;
    void Write(int indx);
    virtual void AnalyseCom();
    virtual void Reconfigure(int);
    virtual void AutoSys();
    virtual void PostRead(int indx, int fail, int warn, ListMcm* list_ptr);
    void DecodeStatus(const char stat);
    void DecodeList(ListMcm* list_ptr);
    int Initfps();
    int Mvfps();
};

#endif //H_FPSSYSTM_H
      
                                   


