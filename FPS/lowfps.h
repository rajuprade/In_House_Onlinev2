/*******************************************************

  lowfps.h
  ABCcom program, version 1.1
  L.Pommier, Jan 2006.
  
*******************************************************/

#ifndef H_LOWFPS_H
#define H_LOWFPS_H

#include "common.h"


/******************************************************************************
 LowfWrite class declaration
 prepare and send command packets to FPS
******************************************************************************/ 
class LowfWrite {
  public :
    LowfWrite(ofstream *fdrec0);
    ~LowfWrite(void); 
    void MakeBuffer(CMD Cmd, unsigned char FpsAddr, MSG* const Buf);      
  private :
    ofstream *fdrec;
    unsigned char *buf_ptr0;     
    void AddCksum(unsigned char *buff);
    void InitBuff(char buff[]);
    void set_oneb_arg(int CmdNum, const unsigned char Arg[]);
    void set_twob_arg(int CmdNum, const unsigned char Arg[]);
    void run_free(const unsigned char Arg[]);
    void run_preset(const unsigned char Arg[]);
    void run_fine(const unsigned char Arg[]);
};


/******************************************************************************
 LowfRead class declaration
 read FPS answer and decode its link structure
******************************************************************************/
class LowfRead {
  public :
    LowfRead(ofstream *fdrec0);
    ~LowfRead(void);
    int DecodeBuffer(const MSG CmdRx);
    char Watchdogflag, Overcurrentflag;
  private :
    ofstream *fdrec;
};

#endif //H_LOWFPS_H


