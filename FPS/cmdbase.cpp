/***************************************************

  cmdbase.cpp
  Teleset program, version 1.1
  L.Pommier, March 2006.

***************************************************/

#include <iostream>
#include <fstream>

#include "cmdbase.h"   
#include <math.h>  

/******************************************************************************
 CmdBase class functions
******************************************************************************/
CmdBase::CmdBase(LogFile *FileRec0, SetData *SetShare0, int UserIndx0, int SysNo0)
{
  SetShare = SetShare0;
  SysNo = SysNo0;
  UserIndx = UserIndx0;
  FileRec = FileRec0;
}

CmdBase::~CmdBase() {;}

int CmdBase::GetCmd(MSG *Tx0, ifstream *fdinput0)
{
  int siz = Tx0->Length;
  Fdinput = fdinput0;
  Tx = Tx0;
  Tx->Length += 2;
  Txpush(SysNo);
  FileRec->TimeStamp();
  *FileRec->fd << "System ";
  switch (SysNo) {
    case 1: *FileRec->fd << "ABC" << endl; break;
    case 2: *FileRec->fd << "SSC" << endl; break;
    case 3: *FileRec->fd << "LO" << endl; break;
    case 4: *FileRec->fd << "IF" << endl; break;
    case 5: *FileRec->fd << "FE" << endl; break;
    case 6: *FileRec->fd << "FPS" << endl; break;
    case 7: *FileRec->fd << "EXP" << endl; break;
    case 8: *FileRec->fd << "SENTINAL"<<endl;
  }
  if (!GetPacket()) return 0;
  Tx->Msg[siz] = (Tx->Length - siz) & 0x00ff;
  Tx->Msg[siz+1] = (Tx->Length - siz) >> 8;
  return 1;
}

void CmdBase::StoreArrMem(int indx, const float param)
{
  SetShare->UserArray[UserIndx].Setparam[SysNo][indx] = param;   
  SetShare->UserArray[UserIndx].TimeStamp();
  *FileRec->fd << "Setting param: index " << indx << ", value: " << param << endl;
}

void CmdBase::StoreAbcMem(int antnb, int indx, const float param)
{
  SetShare->AntLoad[antnb][SysNo][indx] = param;
  *FileRec->fd << "Loading param: ant " << antnb << ", indx " << indx << ", value: " << param << endl;
}

/******************************************************************************
 CmdAbc class functions
******************************************************************************/
CmdAbc::CmdAbc(LogFile *FileRec0, SetData *SetShare0, int UserIndx0) : CmdBase(FileRec0, SetShare0, UserIndx0, ABCINDX) {;}
CmdAbc::~CmdAbc() {;}

int CmdAbc::GetPacket()
{
  char strbuf[9];
  string user;
  int buf, i;

  if (Fdinput->is_open()) *Fdinput >> user;
  else cin >> user;
  *FileRec->fd << "Command: " << user << endl;
  if (user == "state") Txpush(0x00);
  else if (user == "askparam") Txpush(0x02);
  else if (user == "settime") {
    cout << "Enter time (format: Wed Nov 30 01:35:57 IST 2005): ";
    Txpush(0x04);
    for (i=0;i<6;i++) {
      if (Fdinput->is_open()) *Fdinput >> strbuf;
      else cin >> strbuf;
      Txpush(strbuf);
      *FileRec->fd << strbuf << endl;
    }
  }
  else if (user == "exit") {
    cin >> *dec >> buf;           //not through file
    cout << "Antenna connection will end, Confirm? (y/n): ";
    cin >> strbuf;
    if (strbuf[0] != 'y') {*FileRec->fd << "unconfirmed."; return 0;}
    *FileRec->fd << "ABCcom number: " << buf << endl;
    Txpush(0x06);
    Txpush(buf);
  }
  else if (user == "startlocal") {Txpush(0x08); UpdateFlag(0x08);}
  else if (user == "stoplocal") {Txpush(0x0a); UpdateFlag(0x0a);}  
  else if (user == "startexp") {
    Txpush(0x0c);
    cin >> *dec >> buf;       //not through file
    *FileRec->fd << buf;
    Txpush(buf);       //mcmaddr
    UpdateFlag(0x0c);
  }
  else if (user == "stopexp") {Txpush(0x0e); UpdateFlag(0x0e);}
  else return 0;
  return 1;
}

void CmdAbc::UpdateFlag(const char cmd)
{
  int addr[32], nbant=0, i;

  for (i=0;i<4;i++) {
    if (Tx->Msg[i+2] & 0x01) addr[nbant++] = 0+i*8;
    if (Tx->Msg[i+2] & 0x02) addr[nbant++] = 1+i*8;
    if (Tx->Msg[i+2] & 0x04) addr[nbant++] = 2+i*8;
    if (Tx->Msg[i+2] & 0x08) addr[nbant++] = 3+i*8;
    if (Tx->Msg[i+2] & 0x10) addr[nbant++] = 4+i*8;
    if (Tx->Msg[i+2] & 0x20) addr[nbant++] = 5+i*8;
    if (Tx->Msg[i+2] & 0x40) addr[nbant++] = 6+i*8;
    if (Tx->Msg[i+2] & 0x80) addr[nbant++] = 7+i*8;
  }
  for (i=0;i<nbant;i++) {
    if (cmd == 0x0c) StoreAbcMem(addr[i], 0, 1);          //exp on
    else if (cmd == 0x0e) StoreAbcMem(addr[i], 0, 0);     //exp off
    else if (cmd == 0x08) StoreAbcMem(addr[i], 1, 1);     //local on
    else if (cmd == 0x0a) StoreAbcMem(addr[i], 1, 0);     //local off
  }
}


/******************************************************************************
 CmdSsc class functions
******************************************************************************/
CmdSsc::CmdSsc(LogFile *FileRec0, SetData *SetShare0, int UserIndx0) : CmdBase(FileRec0, SetShare0, UserIndx0, SSCINDX) {;}
CmdSsc::~CmdSsc() {;}     

int CmdSsc::GetPacket()
{
  string user;

  if (Fdinput->is_open()) *Fdinput >> user;
  else cin >> user;
  *FileRec->fd << "Command: " << user << endl;
  if (user == "state") Txpush(0x00);
  else if (user == "askparam") Txpush(0x02);
  else if (user == "trkon") {Txpush(0x04); Trkon();}
  else if (user == "trkoff") Txpush(0x06);
  else if (user == "trkset") {Txpush(0x08); Trkset();}
  else if (user == "trkaz") {
    Txpush(0x0a);
    if (Fdinput->is_open()) *Fdinput >> user;
    else cin >> user;
    if (user == "in") Txpush(0);
    else Txpush(1);           // "out" default
  }
  else if (user == "trkrate") {Txpush(0x0c); Trkrate();}
  else if (user == "cmd") {Txpush(0x0e); ServoCmd();}
  else return 0;
  return 1;
}     

void CmdSsc::Trkrate()
{
  char buf[10], str[5];
  float fbuf;
  int i;

  if (Fdinput->is_open()) *Fdinput >> fbuf;
  else {
    cout << " RA rate ('/m):";
    cin >> fbuf;  
  }
  fbuf *= 60;  // deg/hour
  Txpush(fbuf);
  StoreArrMem(2, fbuf);
  if (Fdinput->is_open()) *Fdinput >> fbuf;
  else {
    cout << " DEC rate ('/m):";
    cin >> fbuf; 
  }
  fbuf *= 60;
  Txpush(fbuf);
  StoreArrMem(3, fbuf); 
  if (Fdinput->is_open()) *Fdinput >> buf;
  else {
    cout << " Time ref t0 (hh:mm:ss):";
    cin >> buf;
  }
  for (i=0;i<2;i++) str[i] = buf[i];
  str[3] = '\0'; fbuf = atol(str);
  for (i=0;i<2;i++) str[i] = buf[i+3];
  str[3] = '\0'; fbuf += atol(str)/60;
  for (i=0;i<2;i++) str[i] = buf[i+6];
  str[3] = '\0'; fbuf += atol(str)/3600;
  Txpush(fbuf);
  StoreArrMem(4, fbuf);
}

void CmdSsc::Trkon()
{
  char ra0[20], dec0[20], buff[200];
  string filename[2];
  float ra[3], dec[3], rarad, decrad;

  if (Fdinput->is_open()) *Fdinput >> filename[0];
  else cin >> filename[0];                    //add checkings
  filename[1] = SRC; filename[1] += filename[0];
  ifstream fd(filename[1].c_str());             //05h31m30.00s	-21d58'0.00"
  if (!fd) return;
  
  do fd.getline(buff, 200);
  while (buff[0]=='#');
  fd >> buff >> ra0 >> dec0;
  sscanf(ra0, "%fh%fm%fs", &ra[0], &ra[1], &ra[2]);
  sscanf(dec0, "%fd%f\'%f\"", &dec[0], &dec[1], &dec[2]);
  //cout << "test: " << ra0 << " " << dec0 << endl;
  rarad = (ra[0] + ra[1]/60. + ra[2]/3600.)*M_PI/12.;           // 12 h - PI rad - 180 deg
  decrad = (dec[0] + dec[1]/60. + dec[2]/3600.)*M_PI/180.;
  Txpush(rarad);
  Txpush(decrad);
  StoreArrMem(0, rarad);
  StoreArrMem(1, decrad);
}

void CmdSsc::Trkset()
{
  char buff[200];  
  string filename[2];
  int var[3], ant, antbuf;
  float fbuf;

  if (Fdinput->is_open()) *Fdinput >> filename[0];
  else cin >> filename[0];
  filename[1] = SRC; filename[1] += filename[0];
  ifstream fd(filename[1].c_str());
  if (!fd) return;
  
  do fd.getline(buff, 200);
  while (buff[0]=='#');
  if (Fdinput->is_open()) *Fdinput >> ant;
  else cin >> ant;
  Txpush(ant);    
  fd >> antbuf;                     //add checkings
  while (antbuf != ant) {fd.getline(buff, 200); fd >> antbuf;}

  fd >> buff;
  sscanf(buff, "%d:%d:%d", &var[0], &var[1], &var[2]);     // az offset (+/-ddd:mm:ss)
  if (var[0] < 0) {var[1] = -var[1]; var[2] = -var[2];}
  fbuf = var[0] + var[1]/60. + var[2]/3600.;
  Txpush(fbuf);
  StoreAbcMem(ant, 0, fbuf);

  fd >> buff;
  sscanf(buff, "%d:%d:%d", &var[0], &var[1], &var[2]);     // el offset (+/-ddd:mm:ss)
  if (var[0] < 0) {var[1] = -var[1]; var[2] = -var[2];}
  fbuf = var[0] + var[1]/60. + var[2]/3600.;
  Txpush(fbuf);
  StoreAbcMem(ant, 1, fbuf);
 
  fd >> fbuf;
  fbuf = fbuf * M_PI / 180.; Txpush(fbuf);     // latitude in rad
  StoreAbcMem(ant, 2, fbuf);
  fd >> fbuf; Txpush(fbuf);      // longitude         //store also sharemem
  StoreAbcMem(ant, 3, fbuf);
}


void CmdSsc::ServoCmd()
{
  int cmd;
  unsigned char e='E';

  if (Fdinput->is_open()) *Fdinput >> hex >> cmd;
  else cin >> hex >> cmd;
  Txpush(cmd);
  Txpushcoma();
  if ((cmd == 0x46)||(cmd == 0x48))
    {AskAx(); Txpopcoma();}
  else if ((cmd == 0x4c)||(cmd == 0x4e))
    Txpush(e);
  else if ((cmd == 0x42)||(cmd == 0x56)||(cmd == 0x58)) {
    AskAx();
    AskAng();
    if (Tx->Msg[Tx->Length-1] == 'B') AskAng();
    Txpopcoma();
  }
  else if (cmd == 0x44) {
    AskAx();
    AskTime();
    AskAng();
    if (Tx->Msg[Tx->Length-1] == 'B') AskAng();
    Txpopcoma();
  }
  else if (cmd == 0x52) {
    AskTime();
    AskDate();
    Txpopcoma();
  }
  else if (cmd == 0x54) {AskAng(); Txpopcoma();}
  else if (cmd == 0x5a) {AskWindvel(); Txpopcoma();}
  else Tx->Length--;
}

void CmdSsc::AskDate()
{
  char buf[11];
  if (Fdinput->is_open()) *Fdinput >> buf;
  else {
    cout << "Enter Date (dd-mm-yyyy) :\n> ";
    cin >> buf;
  }
  Txpush(buf);
}

void CmdSsc::AskWindvel()
{
  char buf[9];
  if (Fdinput->is_open()) *Fdinput >> buf;
  else {
    cout << "Enter Windvel (xxx.xxxx) :\n> ";
    cin >> buf;
  }
  Txpush(buf);
}

void CmdSsc::AskAx()
{
  unsigned char c;
  if (Fdinput->is_open()) *Fdinput >> c;
  else {
    cout << "Enter Axis (A/E/B) :\n> ";
    cin >> c;
  }
  Txpush(c); Txpushcoma();
}

void CmdSsc::AskAng()
{
  char buf[11];
  if (Fdinput->is_open()) *Fdinput >> buf;
  else {
    cout << "Enter Ang (+/-ddd:mm:ss) :\n> ";
    cin >> buf;
  }
  Txpush(buf);
}

void CmdSsc::AskTime()
{
  char buf[9];
  if (Fdinput->is_open()) *Fdinput >> buf;
  else {
    cout << "Enter Time (hh:mm:ss) :\n> ";
    cin >> buf;
  }
  Txpush(buf);
}


/******************************************************************************
 CmdExp class functions
******************************************************************************/
CmdExp::CmdExp(LogFile *FileRec0, SetData *SetShare0, int UserIndx0) : CmdBase(FileRec0, SetShare0, UserIndx0, EXPINDX) {;}
CmdExp::~CmdExp() {;}

int CmdExp::GetPacket()         //not through file
{
  string user;
  int buf, i;

  if (!CheckFlag()) return 0;
  cin >> user;
  *FileRec->fd << "Command: " << user << endl;
  if (user == "state") {Txpush(0x00); return 1;}
  else if (user != "cmd") {return 0;}
  Txpush(0x04);
  cout << "\nEnter Command:\t";
  cin >> *dec >> buf;
  while ((buf < 0) || (buf > 19)) {
    cout << "1:Null Cmd\t\t2:Set Idle Mode\t\t3:Set Scan Mode\n";
    cout << "4:Set Mean Mode\t\t5:Set Anl Mask\n";
    cout << "6:Set Dig Mask 16b\t7:Set Dig Mask 32b\t8:Set Dig Mask 64b\n";
    cout << "9:Read Anl Mask\t\t10:Read Dig Mask 16b\t11:Read Dig Mask 32\n";
    cout << "12:Read Dig Mask 64b\t13:Read Version\t\t14:Read mode\n";
    cout << "15:Reboot\t\t16:FE Control (old)\t17:FE Control (new)\n";
    cout << "18:FE-Box Monitor\t19:Common Box Monitor\n";
    cout << "\nEnter Command:\t";
    cin >> *dec >> buf;
  }
  Txpush(buf);
  *FileRec->fd << "MCM Cmd no: " << buf << endl;
  switch (buf) {
    case 5 :
      cout << "\nEnter Anl Mask (xx xx xx xx xx xx xx xx):\t";
      for (i=0;i<8;i++) {cin >> hex >> buf; Txpush(buf);}
      break;
    case 6 :
      cout << "\nEnter Dig Mask 16 (xx xx):\t";
      for (i=0;i<2;i++) {cin >> hex >> buf; Txpush(buf);}
      break;
    case 7 :
      cout << "\nEnter Dig Mask 32 (xx xx xx xx):\t";
      for (i=0;i<4;i++) {cin >> hex >> buf; Txpush(buf);}
      break;
    case 8 :
      cout << "\nEnter Dig Mask 64 (xx xx xx xx xx xx xx xx):\t";
      for (i=0;i<8;i++) {cin >> hex >> buf; Txpush(buf);}
      break;
    case 4 :
      cout << "\nEnter Avg Factor:\t";
      cin >> *dec >> buf; Txpush(buf);
      break;
    case 16 :
      cout << "\nEnter Feed data mask (xx):\t";
      cin >> hex >> buf; Txpush(buf);
      break;
    case 17 :
      cout << "\nEnter Feed data mask(xx xx):\t";
      for (i=0;i<2;i++) {cin >> hex >> buf; Txpush(buf);}
      break;
    case 18 :
      cout << "\nEnter Feed box number:\t";
      cin >> *dec >> buf; Txpush(buf);
  }
  return 1;
}

int CmdExp::CheckFlag() const
{
  int addr[32], nbant=0, i;

  for (i=0;i<4;i++) {
    if (Tx->Msg[i+2] & 0x01) addr[nbant++] = 0+i*8;
    if (Tx->Msg[i+2] & 0x02) addr[nbant++] = 1+i*8;
    if (Tx->Msg[i+2] & 0x04) addr[nbant++] = 2+i*8;
    if (Tx->Msg[i+2] & 0x08) addr[nbant++] = 3+i*8;
    if (Tx->Msg[i+2] & 0x10) addr[nbant++] = 4+i*8;
    if (Tx->Msg[i+2] & 0x20) addr[nbant++] = 5+i*8;
    if (Tx->Msg[i+2] & 0x40) addr[nbant++] = 6+i*8;
    if (Tx->Msg[i+2] & 0x80) addr[nbant++] = 7+i*8;
  }
  for (i=0;i<nbant;i++) {
    if (SetShare->AntLoad[addr[i]][ABCINDX][0] != 1) return 0;
  }
  return 1;
}


/******************************************************************************
 CmdFps class functions
******************************************************************************/
CmdFps::CmdFps(LogFile *FileRec0, SetData *SetShare0, int UserIndx0) : CmdBase(FileRec0, SetShare0, UserIndx0, FPSINDX) {;}
CmdFps::~CmdFps() {;}

int CmdFps::GetPacket()
{
  string user;
  float pos;
  int time;

  if (Fdinput->is_open()) *Fdinput >> user;
  else cin >> user;
  *FileRec->fd << "Command: " << user << endl;
  if (user == "state") Txpush(0x00);
  else if (user == "askparam") Txpush(0x02);
  else if (user == "init") Txpush(0x04);
  else if (user == "loadcnt") {
    Txpush(0x06);
    if (!GetFpsLoad()) return 0;
  }
  else if (user == "mvpos") {
    if (Fdinput->is_open()) *Fdinput >> *dec >> pos;
    else cin >> *dec >> pos;
    if ((pos != 150)&&(pos != 610)&&(pos != 325)&&(pos != 1420)) return 0;
    Txpush(0x08);
    Txpush(pos);
    StoreArrMem(0, pos);
  }
  else if (user == "autotime") {
    if (Fdinput->is_open()) *Fdinput >> *dec >> time;
    else cin >> *dec >> time;
    Txpush(0x0a);
    Txpush(time, 2);
    StoreArrMem(1, (float)time);
  }
  else if (user == "cmd") {
    Txpush(0x0c);
    if (!FpsDirect()) return 0;
  }
  else return 0;
  return 1;
}

int CmdFps::GetFpsLoad()
{
  char buff[200];
  string filename[2];
  float buf;
  int i, ant0, ant1;

  if (Fdinput->is_open()) *Fdinput >> filename[0];
  else cin >> filename[0];
  filename[1] = SRC; filename[1] += filename[0];
  ifstream fd(filename[1].c_str());
  if (!fd) return 0;

  do fd.getline(buff, 200);
  while (buff[0]=='#');
  if (Fdinput->is_open()) *Fdinput >> ant0;
  else cin >> ant0; 
  fd >> ant1;                     //add checkings
  while (ant1 != ant0) {
    if (fd.eof()) return 0;
    fd.getline(buff, 200);
    fd >> ant1;
  }
  Txpush(ant0);  
  for (i=0;i<4;i++) {
    fd >> buf;
    Txpush(buf);  
    StoreAbcMem(ant0, i, buf); 
  }
  return 1;
}

int CmdFps::FpsDirect()
{
  int buf, x, y;
                                                                                                                                
  if (Fdinput->is_open()) *Fdinput >> *dec >> buf;
  else {
    cout << "\nEnter Command:\t";
    cin >> *dec >> buf;    
    while ((buf < 0) || (buf > 27)) {
      cout << "\n1:Null Cmd\n";
      cout << "2:Set Turning Point\t3:Set Ramp down Cnt\t4:Set lower RPM limit\n";
      cout << "5:Set Brake down diff\t6:Set Ramp up Cnt\t7:Set Stop time Cnt\n";
      cout << "8:Set Max PWM Cnt\t9:Set Max Angle\t\t10:Set Min Angle\n";
      cout << "11:Read Turning Point\t12:Read Ramp down Cnt\t13:Read lower RPM limit\n";
      cout << "14:Read Brake Cnt diff\t15:Read Ramp up Cnt\t16:Read Stop Time Cnt\n";
      cout << "17:Read Max PWM Cnt\t18:Read Max Angle\t19:Read Min Angle\n";
      cout << "20:Read Version\t\t21:Run to Calibrate\t22:Free Run\n";
      cout << "23:Run to preset\t24:Run to fine tune\t25:Passworded Run\n";
      cout << "26:FPS Reboot\t\t27:FPS Stop\n";
      cout << "\nEnter Command:\t";
      cin >> *dec >> buf;
    }
  }
  Txpush(buf);
  switch (buf) {
    case 2 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter turning point position difference:\t";
        cin >> *dec >> x;
      }
      Txpush(x/2, 2);
      break;
    case 3 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter Time interval:\t";
        cin >> *dec >> x;
      }
      Txpush(x/5);
      break;
    case 4 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> y;
      else {
        cout << "\nEnter Lower RPM limit:\t";
        cin >> *dec >> y;
      }
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter Check-Interval(ms):\t";
        cin >> *dec >> x;
      }
      Txpush(x/5);
      Txpush((int) (y*0.2048*x/1800.0));
      break;
    case 5 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter Break Cnt difference:\t";
        cin >> *dec >> x;
      }
      Txpush(x/2);
      break;
    case 6 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter Rampup Time Interval:\t";
        cin >> *dec >> x;
      }
      Txpush(x/5);
      break;
    case 7 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter SSLinterval:\t";
        cin >> *dec >> x;
      }
      Txpush(x/5);
      break;
    case 8 :
      if (Fdinput->is_open()) *Fdinput >> hex >> x;
      else {
        cout << "\nEnter max PWM cnt:\t";
        cin >> hex >> x;
      }
      Txpush(x);
      break;
    case 9 :
    case 10 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter angle count:\t";
        cin >> *dec >> x;
      }
      Txpush(x/2, 2);
      break;
    case 22 :
      if (Fdinput->is_open()) *Fdinput >> x;
      else {
        cout << "\nEnter 0-towards 270deg / 1-towards -10deg:\t";
        cin >> x;
      }
      Txpush(x);
      break;
    case 23 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter target encoder value:\t";
        cin >> *dec >> x;
      }
      Txpush(x/2, 2);
      break;
    case 24 :
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter target encoder value:\t";
        cin >> *dec >> x;
      }
      Txpush(x/2, 2);
      if (Fdinput->is_open()) *Fdinput >> *dec >> x;
      else {
        cout << "\nEnter PWM cnt:\t";
        cin >> hex >> x;
      }
      Txpush(x);
  }   
  return 1;
}


















  



                        

