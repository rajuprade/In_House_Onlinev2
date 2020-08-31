/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include<stdlib.h>
#include<iostream>
#include<ctype.h>
#include<string.h>
#include<malloc.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<qfile.h>
#include<time.h>
#include<qtimer.h>
#include<qstring.h>
#include<qprocess.h>
#include<qmessagebox.h>
#include<qstringlist.h>
#include<regex.h>
#include<qdialog.h>

#include"gpu.h"

using namespace std;

// Variable Delcarations
/*
static int gpumode, gpulta,gpugain,gpuchan,gpustokes;
static int gpuifbw,gpufinbw,gpufstop,gpucntrl,range;
static float gpubw;
static double gpuedgefrq;
const char * gpuchannum;
const char * gpubeam1;
const char * gpubeam2;
*/
int status,pid;

QProcess * process ;

// Enum data type declarations
enum modeunits {
    RAWDUMP,
    REALTIME,
};

// load parameters from file "gpu.hdr"
void EditPreference::init()
{
    //QTimer *timer = new QTimer(this);
    // connect(timer, SIGNAL(timeout()), this, SLOT(DasConsole_started()));
    //timer->start(200, FALSE);	// 100msec timer with Single Shot Disabled

  load();
  //DasConsole_stateChanged();
  return void();
}

// GpuMode
void EditPreference::GpuMode( const QString &  )
{
    const char * Mode;
    Mode = (comboBoxMode->currentText());
    
    if ((comboBoxMode->currentText()) == "REALTIME") {
	gpu->gpumode = 0;
    }
    if ((comboBoxMode->currentText()) == "RAWDUMP") {
	gpu->gpumode = 1;
    }  
    //printf(" %d\t %s\n", gpumode, Mode);
    
    return void();
}

// GpuLta
void EditPreference::GpuLta( const QString & )
{
    const char * Lta;
    Lta = (comboBoxLta->currentText());
    
    if ((comboBoxLta->currentText()) == "32") {
	gpu->gpulta = 32;
    }
    if ((comboBoxLta->currentText()) == "16") {
	gpu->gpulta = 16;
    }  
    if ((comboBoxLta->currentText()) == "8") {
	gpu->gpulta = 8;
    }
    if ((comboBoxLta->currentText()) == "4") {
	gpu->gpulta = 4;
    }  
    if ((comboBoxLta->currentText()) == "2") {
	gpu->gpulta = 2;
    }
    if ((comboBoxLta->currentText()) == "1") {
	gpu->gpulta = 1;
    }  
    //printf(" %d\t %s\n", gpulta, Lta);
    
    return void();
}

// GpuAcqBw
void EditPreference::GpuAcqBw( const QString & )
{
    const char * Acq;
    Acq = (comboBoxAcqBw->currentText());
    
    if ((comboBoxAcqBw->currentText()) == "400.0000") {
	gpu->gpubw = 400.0000;
    }
    if ((comboBoxAcqBw->currentText()) == "200.0000") {
	gpu->gpubw = 200.0000;
    }  
    if ((comboBoxAcqBw->currentText()) == "150.0000") {
	gpu->gpubw = 150.0000;
    }
    if ((comboBoxAcqBw->currentText()) == "100.0000") {
	gpu->gpubw = 100.0000;
    }
    if ((comboBoxAcqBw->currentText()) == "50.0000") {
	gpu->gpubw = 50.0000;
    }
    //printf(" %5.4f\t %s\n", gpubw, Acq);
    
    return void();
}

// GpuChanMax and GpuChanNum
void EditPreference::GpuChan( const QString & )
{
    const char * Chan;
    Chan = (comboBoxChan->currentText());
    
    if ((comboBoxChan->currentText()) == "512") {
	gpu->gpuchan = 512;

    }
    if ((comboBoxChan->currentText()) == "1024") {
	gpu->gpuchan = 1024;
    }
    if ((comboBoxChan->currentText()) == "2048") {
	gpu->gpuchan = 2048;
    }
    //range = gpu->gpuchan-1;
    //printf(" %d\t %s\t 0:%d:1\n ", gpuchan, Chan, range);
    
    return void();
}

// GpuStokes
void EditPreference::GpuStokes( const QString & )
{
    const char * Stokes;
    Stokes = (comboBoxStokes->currentText());
    
    if ((comboBoxStokes->currentText()) == "Single POL USB-130") {
	gpu->gpustokes = 1;
    }
    if ((comboBoxStokes->currentText()) == "2 STOKES") {
	gpu->gpustokes = 2;
    }
    if ((comboBoxStokes->currentText()) == "4 STOKES") {
	gpu->gpustokes = 4;
    }
    //printf(" %d\t %s\n", gpustokes, Stokes);
    
    return void();
}

// GpuControl
void EditPreference::GpuControl()
{
    gpu->gpucntrl = 1;
    return void();
}

//GpuIFBandWidth
void EditPreference::GpuIfBw( const QString & )
{
    gpu->gpubw = 0;
    return void();
}

// GpuFinalBandWidth
void EditPreference::GpuFinBw( const QString & )
{
    gpu->gpufinbw = 0;
    gpu->gpuedgefrq = 0;
    return void();
}

// GpuBeams
void EditPreference::GpuBeams( const QString & )
{
    const char * Beams;
    Beams = (comboBoxBeams->currentText());
    
    if ((comboBoxBeams->currentText()) == "OFF") {
	gpu->gpubeam1 = "0:1";
	gpu->gpubeam2 = "0:1";
    }
    //printf(" %s\t%s\t%s\n", gpubeam1,gpubeam2, Beams);
    
    return void();
}

// GupGain
void EditPreference::GpuGain_clicked()
{
   switch ( radioButtonGain->isOn()) {
   case TRUE:
       gpu->gpugain = 1;
       radioButtonGain->setText("GAIN ON");
       radioButtonGain->setPaletteBackgroundColor( QColor( 85, 170, 0 ) );
       break;
   case FALSE:
       gpu->gpugain = 0;
       radioButtonGain->setText("GAIN OFF");
       radioButtonGain->setPaletteBackgroundColor( QColor( 255, 85, 0 ) );
       break;
    }
    //printf("***GAIN : %d\n",gpugain);
    return void();
}

// GpunFstop
void EditPreference::GpuFstop_clicked()
{
   switch ( radioButtonFstop->isOn()) {
   case TRUE:
       gpu->gpufstop =1;
       radioButtonFstop->setText("FSTOP ON");
       radioButtonFstop->setPaletteBackgroundColor( QColor( 85, 170, 0 ) );
       break;
   case FALSE:
       gpu->gpufstop = 0;
       radioButtonFstop->setText("FSTOP OFF");
       radioButtonFstop->setPaletteBackgroundColor( QColor( 255, 85, 0 ) );
       break;
    }
   //printf("***FSTOP : %d\n",gpufstop);
    return void();
}


// Gpu DasConsole
void EditPreference::dasconsole()
{
/*
  QStringList args;
  args << "./dasconsole";   //args = "dasconsole";

  process = new QProcess(args);
  if ( !process->start() ) { 	// error handling
        QMessageBox::critical( 0,
                tr("Fatal error"),
                tr("Could not start uic command. "),
                tr("Quit") );
        exit( -1 );
  }
  status = process->isRunning();
  cout << process->isRunning() << "\t" << process->processIdentifier() << endl;
  DasConsole_stateChanged();

  return void();
*/
}


void EditPreference::DasConsole_stateChanged()
{
      pid = process->processIdentifier();
      if ( pid >=  0 ) {	 //status = 1;
  	   printf("Process running\n");
           connect( pushButtonDasConsole, SIGNAL( clicked() ), this, SLOT( DasConsole_started() ) );
           }
      if ( !process->normalExit() == TRUE ) {
     	   printf("Process Not running\n");
    	   connect( pushButtonDasConsole, SIGNAL( clicked() ), this, SLOT( DasConsole_exited() ) );
      }
  return void();
}


// Save Function
void EditPreference::save()
{
/*
    // Variable declaration //
    static char * mode;
    static char * stokes;
    static char * beams;
    static int lta,acqbw,chan;
    static char * gain;
    static char * fstop;

    // Variable assignments //
    mode = "REALTIME";
    lta = 32;
    acqbw = 400;
    chan = 512;
    stokes = "SinglePoleUsb130";
    beams = "OFF";
    gain = "ON";
    fstop = "ON";
*/

    setgpu *gpu;
    gpu = (setgpu *)malloc(sizeof(setgpu));

    time_t *t1;
    t1 = (time_t *)malloc((time_t)sizeof(time_t));
    time(t1);

    FILE * gpuconfig;
    gpuconfig = fopen("gpu.hdr", "w+");
        

    /* printing values ...*/
    fprintf(gpuconfig,"{ Corrsel.def\n");    
    fprintf(gpuconfig,"GPU_MODE    = %d               /* 0 - Realtime, 1 - RawDump          */\n",gpu->gpumode);
    fprintf(gpuconfig,"GPU_LTA     = %d              /* 8 - fixed value                    */\n",gpu->gpulta);
    fprintf(gpuconfig,"GPU_ACQ_BW  = %4.4f        /* 16.666666 or 33.333333             */\n",gpu->gpubw);
    fprintf(gpuconfig,"GPU_FINAL_BW= %d             /* 0,4,8,16,32,64,128 As frac of Nyq, Val = OFF */\n",gpu->gpufinbw);
    fprintf(gpuconfig,"GPU_EDGE_FRQ= %2.6f        /* Freq Entry in steps of Nyq, Val = 0 */\n",gpu->gpuedgefrq);
    fprintf(gpuconfig,"GPU_CHAN_MAX= %d             /* 256/512                            */\n",gpu->gpuchan);
    fprintf(gpuconfig,"GPU_CHAN_NUM= 0:%d:1         /* any range i:j:1;for i,j<chan_max   */\n",gpu->gpuchan-1);
    fprintf(gpuconfig,"GPU_STOKES  = %d               /* 2 Total_Intensity; 4 Full_Stokes   */\n",gpu->gpustokes);
    fprintf(gpuconfig,"GPU_CNTRL   = %d               /* 0 -LOCAL, 1 -ONLINE, 2 -MANUAL     */\n",gpu->gpucntrl);
    fprintf(gpuconfig,"GPU_FSTOP   = %d               /* 1 - ON, 0 - OFF                    */\n",gpu->gpufstop);
    fprintf(gpuconfig,"GPU_BEAM_1  = %s             /* 0-OFF,1-IA,2-PA,3-Volt:time res 1=30/2=60 */\n",gpu->gpubeam1);
    fprintf(gpuconfig,"GPU_BEAM_2  = %s             /* 0-OFF,1-PA,2-PA,3-Volt:time res 1=30/2=60 */\n",gpu->gpubeam2);
    fprintf(gpuconfig,"GPU_GAINEQ  = %d               /* 1 - ON, 0 - OFF                       */\n",gpu->gpugain);
    fprintf(gpuconfig,"GPU_BB_LO   = 149000000.0:156000000.0          /* 32-149:156,16 -138:167,6-133:172   */\n");
    fprintf(gpuconfig,"}Corrsel\n");
    fprintf(gpuconfig,"*\n");
    fprintf(gpuconfig,"END_OF_HEADER			/*  VERSION RELEASED */\n");
    
    fclose(gpuconfig);
    fprintf(stderr,"\n File saved as gpu.hdr\n");

    ctime_r(t1,gpu->timestamp);
    fprintf(stderr," Timestamp=> %s",ctime(t1));

    //write_shm(gpu);
    
    return void();
}

void EditPreference::write_shm()
{

    int shmid1; 	//  int i=0,j,k,m,flag=0;
    key_t key1;
    setgpu *gpu;
    key1 = 9100;

    time_t *t1;
    t1 = (time_t *)malloc((time_t)sizeof(time_t));
    time(t1);


    // printf("I am in shm\n");
    if( (shmid1 = shmget(key1,sizeof(setgpu),IPC_CREAT | 0777)) < 0 )
    {
       printf("shmget");
       // exit(1);
    }
    if ( (gpu = (setgpu *)shmat(shmid1,NULL,0)) ==(setgpu *)-1)
    {
       printf("shmat");
       //exit(1);
    }

    memcpy(gpu,gpu,sizeof(setgpu));
    // sleep(30);
    fprintf(stderr,"successfully copied in SHM\n");

    /* printing values ...*/
    fprintf(stderr,"{ Corrsel.def\n");
    fprintf(stderr,"GPU_MODE    = %d               /* 0 - Realtime, 1 - RawDump          */\n",gpu->gpumode);
    fprintf(stderr,"GPU_LTA     = %d              /* 8 - fixed value                    */\n",gpu->gpulta);
    fprintf(stderr,"GPU_ACQ_BW  = %4.4f        /* 16.666666 or 33.333333             */\n",gpu->gpubw);
    fprintf(stderr,"GPU_FINAL_BW= %d             /* 0,4,8,16,32,64,128 As frac of Nyq, Val = OFF */\n",gpu->gpufinbw);
    fprintf(stderr,"GPU_EDGE_FRQ= %2.6f        /* Freq Entry in steps of Nyq, Val = 0 */\n",gpu->gpuedgefrq);
    fprintf(stderr,"GPU_CHAN_MAX= %d             /* 256/512                            */\n",gpu->gpuchan);
    fprintf(stderr,"GPU_CHAN_NUM= 0:%d:1         /* any range i:j:1;for i,j<chan_max   */\n",gpu->gpuchan-1);
    fprintf(stderr,"GPU_STOKES  = %d               /* 2 Total_Intensity; 4 Full_Stokes   */\n",gpu->gpustokes);
    fprintf(stderr,"GPU_CNTRL   = %d               /* 0 -LOCAL, 1 -ONLINE, 2 -MANUAL     */\n",gpu->gpucntrl);
    fprintf(stderr,"GPU_FSTOP   = %d               /* 1 - ON, 0 - OFF                    */\n",gpu->gpufstop);
    fprintf(stderr,"GPU_BEAM_1  = %s             /* 0-OFF,1-IA,2-PA,3-Volt:time res 1=30/2=60 */\n",gpu->gpubeam1);
    fprintf(stderr,"GPU_BEAM_2  = %s             /* 0-OFF,1-PA,2-PA,3-Volt:time res 1=30/2=60 */\n",gpu->gpubeam2);
    fprintf(stderr,"GPU_GAINEQ  = %d               /* 1 - ON, 0 - OFF                    */\n",gpu->gpugain);
    fprintf(stderr,"GPU_BB_LO   = 149000000.0:156000000.0          /* 32-149:156,16 -138:167,6-133:172   */\n"); //gpu->bblo);
    fprintf(stderr,"}Corrsel\n");
    fprintf(stderr,"*\n");
    fprintf(stderr,"END_OF_HEADER                    /*  VERSION RELEASED */\n");

    //shmdt(gpu);
    ctime_r(t1,gpu->timestamp);
    fprintf(stderr," Timestamp=> %s",ctime(t1));

}

// Load Previously saved configuration to GUI
void EditPreference::load()
{
    QStringList lines;
    int i = 1;
    QFile file("gpu.hdr");
    if ( !file.open( IO_ReadOnly ) ) {
	printf( QString( "Failed to load \'%1\'" ).arg( "gpu.hdr" ), 2000 );
	return;
    }
    
    //if ( file.open( IO_ReadOnly ) ) 
    QTextStream stream( &file );
    QString line;
    while ( !stream.atEnd() ) {
	line = stream.readLine(); // line of text excluding '\n' //printf( "%3d: %s\n", i++, line.latin1() );
	QStringList tline1 = QStringList::split("=",line);
	QStringList tline2 = QStringList::split(" ",tline1[1]);
/*
	//cout << tline1.join(", ") << endl;
	//cout << tline2.join(", ") << endl;
	if (tline2[0].latin1() == NULL) {
		printf ("NULL\n");
	}
	else {
		//printf (" %s\t%s\n",tline2[0].latin1(),tline1[1].latin1() );
		printf (" %s\n",tline2[0].latin1() );
	}
*/
	if (i == 2) {
	    // printf(" MODE : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpumode=tmp;
	    if ( tmp == 0) { comboBoxMode->setCurrentText("REALTIME"); }
	    if ( tmp == 1) { comboBoxMode->setCurrentText("RAWDUMP"); }
	}
	if(i == 3) {
	    // printf(" LTA : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpulta=tmp;
	    if ( tmp == 32) { comboBoxLta->setCurrentText("32"); }
	    if ( tmp == 16) { comboBoxLta->setCurrentText("16"); }
	    if ( tmp == 8) { comboBoxLta->setCurrentText("8"); }
	    if ( tmp == 4) { comboBoxLta->setCurrentText("4"); }
	    if ( tmp == 2) { comboBoxLta->setCurrentText("2"); }
	    if ( tmp == 1) { comboBoxLta->setCurrentText("1"); }
	}
	if(i == 4) {
	    // printf(" ACQ BW : %s\n",tline2[0].latin1());
	    double tmp; bool ok;
	    tmp = tline2[0].toDouble(&ok);gpu->gpubw=tmp;
	    if ( tmp == 400.0000) { comboBoxAcqBw->setCurrentText("400.0000"); }
	    if ( tmp == 200.0000) { comboBoxAcqBw->setCurrentText("200.0000"); }
	    if ( tmp == 150.0000) { comboBoxAcqBw->setCurrentText("150.0000"); }
	    if ( tmp == 100.0000) { comboBoxAcqBw->setCurrentText("100.0000"); }
	    if ( tmp == 50.0000) { comboBoxAcqBw->setCurrentText("50.0000"); }
	}
	if(i == 5) {
	}
	if(i == 6) {
	}
	if(i == 7) {
	    // printf(" CHAN : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpuchan=tmp;
	    if ( tmp == 512) { comboBoxChan->setCurrentText("512"); }
	    if ( tmp == 1024) { comboBoxChan->setCurrentText("1024"); }
	    if ( tmp == 2048) { comboBoxChan->setCurrentText("2048"); }
	}
	if(i == 8) {
	}
	if(i == 9) {
	    // printf(" STOKES : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpustokes=tmp;
	    if ( tmp == 1) { comboBoxStokes->setCurrentText("Single POL USB-130"); }
	    if ( tmp == 2) { comboBoxStokes->setCurrentText("2 STOKES"); }
	    if ( tmp == 4) { comboBoxStokes->setCurrentText("4 STOKES"); }
	}
	if(i == 10) {
	}
	if(i == 11) {
	    // printf(" FSTOP : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpufstop=tmp;
	    radioButtonFstop_stateChanged( tmp );
	}
	if(i == 12 || i == 13) {
	    // printf(" BEAMS : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpubeam1=gpu->gpubeam2="0:1";
	    if ( tmp == 0) { comboBoxBeams->setCurrentText("OFF");}
	}
	if(i == 14) {
	    // printf(" GAIN : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpugain=tmp;
	    radioButtonGain_stateChanged( tmp );
	}
	i = i+1;
	lines += line;
    }
    file.close();
    printf("\n Loaded data from gpu.hdr\n");
    return void();
}


// Default Parameter Function
void EditPreference::defaultpara()
{
    QStringList lines;
    int i = 1;
    QFile file("default.hdr");
    if ( !file.open( IO_ReadOnly ) ) {
	printf( QString( "Failed to load \'%1\'" ).arg( "default.hdr" ), 2000 );
	return;
    }
    
    //if ( file.open( IO_ReadOnly ) ) 
    QTextStream stream( &file );
    QString line;
    while ( !stream.atEnd() ) {
	line = stream.readLine(); // line of text excluding '\n' //printf( "%3d: %s\n", i++, line.latin1() );
	QStringList tline1 = QStringList::split("=",line);
	QStringList tline2 = QStringList::split(" ",tline1[1]);
/*	
	cout << tline1.join(", ") << endl;
	cout << tline2.join(", ") << endl;
	if (tline2[0].latin1() == NULL) {
		printf ("NULL\n");
	}
	else {
		//printf (" %s\t%s\n",tline2[0].latin1(),tline1[1].latin1() );
		printf (" %s\n",tline2[0].latin1() );
	}
*/
	if (i == 2) {
	    // printf(" MODE : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpumode=tmp;
	    if ( tmp == 0) { comboBoxMode->setCurrentText("REALTIME"); }
	    if ( tmp == 1) { comboBoxMode->setCurrentText("RAWDUMP"); }
	}
	if(i == 3) {
	    // printf(" LTA : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpulta=tmp;
	    if ( tmp == 32) { comboBoxLta->setCurrentText("32"); }
	    if ( tmp == 16) { comboBoxLta->setCurrentText("16"); }
	    if ( tmp == 8) { comboBoxLta->setCurrentText("8"); }
	    if ( tmp == 4) { comboBoxLta->setCurrentText("4"); }
	    if ( tmp == 2) { comboBoxLta->setCurrentText("2"); }
	    if ( tmp == 1) { comboBoxLta->setCurrentText("1"); }
	}
	if(i == 4) {
	    // printf(" ACQ BW  : %s\n",tline2[0].latin1());
	    double tmp; bool ok;
	    tmp = tline2[0].toDouble(&ok);gpu->gpubw=tmp;
	    if ( tmp == 400.0000) { comboBoxAcqBw->setCurrentText("400.0000"); }
	    if ( tmp == 200.0000) { comboBoxAcqBw->setCurrentText("200.0000"); }
	    if ( tmp == 150.0000) { comboBoxAcqBw->setCurrentText("150.0000"); }
	    if ( tmp == 100.0000) { comboBoxAcqBw->setCurrentText("100.0000"); }
	    if ( tmp == 50.0000) { comboBoxAcqBw->setCurrentText("50.0000"); }
	}
	if(i == 5) {
	}
	if(i == 6) {
	}
	if(i == 7) {
	    // printf(" CHAN : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpuchan=tmp;
	    if ( tmp == 512) { comboBoxChan->setCurrentText("512"); }
	    if ( tmp == 1024) { comboBoxChan->setCurrentText("1024"); }
	    if ( tmp == 2048) { comboBoxChan->setCurrentText("2048"); }
	}
	if(i == 8) {
	}
	if(i == 9) {
	    // printf(" STOKES : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpustokes=tmp;
	    if ( tmp == 1) { comboBoxStokes->setCurrentText("Single POL USB-130"); }
	    if ( tmp == 2) { comboBoxStokes->setCurrentText("2 STOKES"); }
	    if ( tmp == 4) { comboBoxStokes->setCurrentText("4 STOKES"); }
	}
	if(i == 10) {
	}
	if(i == 11) {
	    // printf(" FSTOP : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpufstop=tmp;
	    radioButtonFstop_stateChanged( tmp );
	}
	if(i == 12 || i == 13) {
	    // printf(" BEAMS : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
    	    tmp = tline2[0].toInt(&ok,10);gpu->gpubeam1=gpu->gpubeam2="0:1";
	    if ( tmp == 0) { comboBoxBeams->setCurrentText("OFF");}
	}
	if(i == 14) {
	    // printf(" GAIN : %s\n",tline2[0].latin1());
	    int tmp; bool ok;
	    tmp = tline2[0].toInt(&ok,10);gpu->gpugain=tmp;
	    radioButtonGain_stateChanged( tmp );
	}
	i = i+1;
	lines += line;
    } 
    file.close();
    printf("\n Loaded data from default.hdr\n");
    return void();
}


void EditPreference::radioButtonFstop_stateChanged( int t)
{
   switch ( t ) {
   case 1:
       gpu->gpufstop =1;
       radioButtonFstop->setText("FSTOP ON");
       radioButtonFstop->setPaletteBackgroundColor( QColor( 85, 170, 0 ) );
       break;
   case 0:       
       gpu->gpufstop = 0;
       radioButtonFstop->setText("FSTOP OFF");
       radioButtonFstop->setPaletteBackgroundColor( QColor( 255, 85, 0 ) );
       break;
}
   return void();
}


void EditPreference::radioButtonGain_stateChanged( int t)
{
   switch ( t ) {
   case 1:
       gpu->gpugain = 1;
       radioButtonGain->setText("GAIN ON");
       radioButtonGain->setPaletteBackgroundColor( QColor( 85, 170, 0 ) );
       break;
   case 0:
       gpu->gpugain = 0;
       radioButtonGain->setText("GAIN OFF");
       radioButtonGain->setPaletteBackgroundColor( QColor( 255, 85, 0 ) );
       break;
}
   return void();
}

// Close GUI Window
void EditPreference::close()
{
 exit ( 0 );
}


void EditPreference::GpuMode_textChanged( const QString & )
{
    const char * Mode;
    Mode = (comboBoxMode->currentText());
    
    if ((comboBoxMode->currentText()) == "REALTIME") {
	gpu->gpumode = 0;
    }
    if ((comboBoxMode->currentText()) == "RAWDUMP") {
	gpu->gpumode = 1;
    }
    return void();
}


void EditPreference::DasConsole_started()
{
    pushButtonDasConsole->setEnabled(FALSE);
    pushButtonDasConsole->setDisabled(TRUE);

    pid = process->processIdentifier();
    while ( !process->normalExit() == TRUE ) {
    connect( pushButtonDasConsole, SIGNAL( clicked() ), this, SLOT( DasConsole_exited() ) );
    }
    return void();
}


void EditPreference::DasConsole_exited()
{
      pid = process->processIdentifier();
      if ( pid >=  0 ) {	 //status = 1;
	switch( QMessageBox::question(0, tr("DasConsole"), 
             tr("Program is running.\nQuit signal detected\nDo you want to kill Dasconsole processes?"),
	     3,4,0 ) )
       {
           case QMessageBox::Yes:
               qDebug( "yes" );
               process->kill();
               pushButtonDasConsole->setEnabled(TRUE);
               pushButtonDasConsole->setDisabled(FALSE);
           break;
           case QMessageBox::No:
               qDebug( "no" );
               pushButtonDasConsole->setEnabled(FALSE);
               pushButtonDasConsole->setDisabled(TRUE);
           break;
           default:
             qDebug( "close" );
           break;
       }
    }
    return void();
}

