/****************************************************************************
** Form implementation generated from reading ui file 'editpreference.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "editpreference.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "editpreference.ui.h"
/*
 *  Constructs a EditPreference as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
EditPreference::EditPreference( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "EditPreference" );

    pushButtonPhasing = new QPushButton( this, "pushButtonPhasing" );
    pushButtonPhasing->setGeometry( QRect( 340, 260, 120, 31 ) );

    pushButtonPulsarConsole = new QPushButton( this, "pushButtonPulsarConsole" );
    pushButtonPulsarConsole->setGeometry( QRect( 340, 300, 120, 31 ) );

    textLabelAcqBw = new QLabel( this, "textLabelAcqBw" );
    textLabelAcqBw->setGeometry( QRect( 20, 100, 130, 31 ) );
    textLabelAcqBw->setFrameShape( QLabel::Box );

    textLabelChan = new QLabel( this, "textLabelChan" );
    textLabelChan->setGeometry( QRect( 20, 140, 130, 31 ) );
    textLabelChan->setFrameShape( QLabel::Box );

    textLabelStokes = new QLabel( this, "textLabelStokes" );
    textLabelStokes->setGeometry( QRect( 20, 180, 130, 31 ) );
    textLabelStokes->setFrameShape( QLabel::Box );

    textLabelIfBw = new QLabel( this, "textLabelIfBw" );
    textLabelIfBw->setGeometry( QRect( 20, 220, 130, 31 ) );
    textLabelIfBw->setFrameShape( QLabel::Box );

    textLabelFinBw = new QLabel( this, "textLabelFinBw" );
    textLabelFinBw->setGeometry( QRect( 20, 260, 130, 31 ) );
    textLabelFinBw->setFrameShape( QLabel::Box );

    textLabelBeams = new QLabel( this, "textLabelBeams" );
    textLabelBeams->setGeometry( QRect( 20, 300, 130, 31 ) );
    textLabelBeams->setFrameShape( QLabel::Box );

    pushButtonPowerEq = new QPushButton( this, "pushButtonPowerEq" );
    pushButtonPowerEq->setGeometry( QRect( 340, 220, 120, 31 ) );

    comboBoxChan = new QComboBox( FALSE, this, "comboBoxChan" );
    comboBoxChan->setGeometry( QRect( 160, 140, 150, 31 ) );

    comboBoxIfBw = new QComboBox( FALSE, this, "comboBoxIfBw" );
    comboBoxIfBw->setGeometry( QRect( 160, 220, 150, 31 ) );

    comboBoxFinBw = new QComboBox( FALSE, this, "comboBoxFinBw" );
    comboBoxFinBw->setGeometry( QRect( 160, 260, 150, 31 ) );

    pushButtonDataMon = new QPushButton( this, "pushButtonDataMon" );
    pushButtonDataMon->setGeometry( QRect( 340, 180, 120, 31 ) );

    comboBoxAcqBw = new QComboBox( FALSE, this, "comboBoxAcqBw" );
    comboBoxAcqBw->setGeometry( QRect( 160, 100, 150, 31 ) );

    comboBoxStokes = new QComboBox( FALSE, this, "comboBoxStokes" );
    comboBoxStokes->setGeometry( QRect( 160, 180, 150, 31 ) );

    comboBoxBeams = new QComboBox( FALSE, this, "comboBoxBeams" );
    comboBoxBeams->setGeometry( QRect( 160, 300, 150, 31 ) );

    comboBoxLta = new QComboBox( FALSE, this, "comboBoxLta" );
    comboBoxLta->setGeometry( QRect( 160, 60, 150, 31 ) );

    pushButtonOnline = new QPushButton( this, "pushButtonOnline" );
    pushButtonOnline->setGeometry( QRect( 341, 100, 120, 31 ) );

    radioButtonGain = new QRadioButton( this, "radioButtonGain" );
    radioButtonGain->setEnabled( TRUE );
    radioButtonGain->setGeometry( QRect( 350, 25, 100, 20 ) );
    radioButtonGain->setPaletteBackgroundColor( QColor( 85, 170, 0 ) );
    radioButtonGain->setMouseTracking( TRUE );
    radioButtonGain->setChecked( TRUE );

    textLabelMode = new QLabel( this, "textLabelMode" );
    textLabelMode->setGeometry( QRect( 20, 20, 130, 30 ) );
    textLabelMode->setFrameShape( QLabel::Box );

    textLabelLta = new QLabel( this, "textLabelLta" );
    textLabelLta->setGeometry( QRect( 20, 60, 130, 31 ) );
    textLabelLta->setAcceptDrops( FALSE );
    textLabelLta->setFrameShape( QLabel::Box );

    pushButtonQuit = new QPushButton( this, "pushButtonQuit" );
    pushButtonQuit->setGeometry( QRect( 360, 360, 100, 31 ) );
    pushButtonQuit->setAcceptDrops( TRUE );
    pushButtonQuit->setToggleButton( FALSE );
    pushButtonQuit->setOn( FALSE );
    pushButtonQuit->setAutoDefault( FALSE );

    pushButtonDefault = new QPushButton( this, "pushButtonDefault" );
    pushButtonDefault->setGeometry( QRect( 250, 360, 100, 31 ) );

    pushButtonLoad = new QPushButton( this, "pushButtonLoad" );
    pushButtonLoad->setGeometry( QRect( 130, 360, 100, 31 ) );

    pushButtonSave = new QPushButton( this, "pushButtonSave" );
    pushButtonSave->setGeometry( QRect( 20, 360, 100, 31 ) );

    comboBoxMode = new QComboBox( FALSE, this, "comboBoxMode" );
    comboBoxMode->setEnabled( TRUE );
    comboBoxMode->setGeometry( QRect( 160, 20, 150, 31 ) );
    comboBoxMode->setMouseTracking( TRUE );

    radioButtonFstop = new QRadioButton( this, "radioButtonFstop" );
    radioButtonFstop->setGeometry( QRect( 350, 60, 100, 20 ) );
    radioButtonFstop->setPaletteBackgroundColor( QColor( 85, 170, 0 ) );
    radioButtonFstop->setMouseTracking( TRUE );
    radioButtonFstop->setChecked( TRUE );

    pushButtonDasConsole = new QPushButton( this, "pushButtonDasConsole" );
    pushButtonDasConsole->setGeometry( QRect( 340, 140, 120, 31 ) );
    pushButtonDasConsole->setToggleButton( FALSE );
    pushButtonDasConsole->setOn( FALSE );
    languageChange();
    resize( QSize(487, 407).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( pushButtonDasConsole, SIGNAL( clicked() ), this, SLOT( dasconsole() ) );
    connect( pushButtonSave, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( pushButtonLoad, SIGNAL( clicked() ), this, SLOT( load() ) );
    connect( pushButtonDefault, SIGNAL( clicked() ), this, SLOT( defaultpara() ) );
    connect( pushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( radioButtonGain, SIGNAL( clicked() ), this, SLOT( GpuGain_clicked() ) );
    connect( comboBoxMode, SIGNAL( activated(const QString&) ), this, SLOT( GpuMode(const QString&) ) );
    connect( radioButtonFstop, SIGNAL( clicked() ), this, SLOT( GpuFstop_clicked() ) );
    connect( comboBoxLta, SIGNAL( activated(const QString&) ), this, SLOT( GpuLta(const QString&) ) );
    connect( comboBoxAcqBw, SIGNAL( activated(const QString&) ), this, SLOT( GpuAcqBw(const QString&) ) );
    connect( comboBoxChan, SIGNAL( activated(const QString&) ), this, SLOT( GpuChan(const QString&) ) );
    connect( comboBoxStokes, SIGNAL( activated(const QString&) ), this, SLOT( GpuStokes(const QString&) ) );
    connect( comboBoxIfBw, SIGNAL( activated(const QString&) ), this, SLOT( GpuIfBw(const QString&) ) );
    connect( comboBoxFinBw, SIGNAL( activated(const QString&) ), this, SLOT( GpuFinBw(const QString&) ) );
    connect( comboBoxBeams, SIGNAL( activated(const QString&) ), this, SLOT( GpuBeams(const QString&) ) );
    connect( pushButtonOnline, SIGNAL( clicked() ), this, SLOT( GpuControl() ) );
    connect( radioButtonFstop, SIGNAL( stateChanged(int) ), this, SLOT( radioButtonFstop_stateChanged(int) ) );
    connect( radioButtonGain, SIGNAL( stateChanged(int) ), this, SLOT( radioButtonGain_stateChanged(int) ) );
    connect( comboBoxMode, SIGNAL( textChanged(const QString&) ), this, SLOT( GpuMode_textChanged(const QString&) ) );
    connect( pushButtonDasConsole, SIGNAL( clicked() ), pushButtonDasConsole, SLOT( toggle() ) );
    connect( pushButtonSave, SIGNAL( clicked() ), this, SLOT( write_shm() ) );

    // tab order
    setTabOrder( comboBoxMode, comboBoxLta );
    setTabOrder( comboBoxLta, comboBoxAcqBw );
    setTabOrder( comboBoxAcqBw, comboBoxChan );
    setTabOrder( comboBoxChan, comboBoxStokes );
    setTabOrder( comboBoxStokes, comboBoxIfBw );
    setTabOrder( comboBoxIfBw, comboBoxFinBw );
    setTabOrder( comboBoxFinBw, comboBoxBeams );
    setTabOrder( comboBoxBeams, radioButtonGain );
    setTabOrder( radioButtonGain, radioButtonFstop );
    setTabOrder( radioButtonFstop, pushButtonOnline );
    setTabOrder( pushButtonOnline, pushButtonDasConsole );
    setTabOrder( pushButtonDasConsole, pushButtonDataMon );
    setTabOrder( pushButtonDataMon, pushButtonPowerEq );
    setTabOrder( pushButtonPowerEq, pushButtonPhasing );
    setTabOrder( pushButtonPhasing, pushButtonPulsarConsole );
    setTabOrder( pushButtonPulsarConsole, pushButtonSave );
    setTabOrder( pushButtonSave, pushButtonLoad );
    setTabOrder( pushButtonLoad, pushButtonDefault );
    setTabOrder( pushButtonDefault, pushButtonQuit );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditPreference::~EditPreference()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void EditPreference::languageChange()
{
    setCaption( tr( "GPU CONFIG GUI" ) );
    pushButtonPhasing->setText( tr( "PHASING" ) );
    pushButtonPhasing->setAccel( QKeySequence( QString::null ) );
    pushButtonPulsarConsole->setText( tr( "PULSAR CONSOLE" ) );
    pushButtonPulsarConsole->setAccel( QKeySequence( QString::null ) );
    textLabelAcqBw->setText( tr( "<p align=\"center\"> ACQ BW (MHz) </p>" ) );
    textLabelChan->setText( tr( "<p align=\"center\">CHANNELS</p>" ) );
    textLabelStokes->setText( tr( "<p align=\"center\">STOKES</p>" ) );
    textLabelIfBw->setText( tr( "<p align=\"center\">IF BW (MHz)</p>" ) );
    textLabelFinBw->setText( tr( "<p align=\"center\">FINAL BW (MHz)</p>" ) );
    textLabelBeams->setText( tr( "<p align=\"center\">BEAM DATA</p>" ) );
    pushButtonPowerEq->setText( tr( "POWER EQ" ) );
    comboBoxChan->clear();
    comboBoxChan->insertItem( tr( "512" ) );
    comboBoxChan->insertItem( tr( "1024" ) );
    comboBoxChan->insertItem( tr( "2048" ) );
    pushButtonDataMon->setText( tr( "DATA MON" ) );
    comboBoxAcqBw->clear();
    comboBoxAcqBw->insertItem( tr( "400.0000" ) );
    comboBoxAcqBw->insertItem( tr( "200.0000" ) );
    comboBoxAcqBw->insertItem( tr( "150.0000" ) );
    comboBoxAcqBw->insertItem( tr( "100.0000" ) );
    comboBoxAcqBw->insertItem( tr( "50.0000" ) );
    comboBoxStokes->clear();
    comboBoxStokes->insertItem( tr( "4 STOKES" ) );
    comboBoxStokes->insertItem( tr( "2 STOKES" ) );
    comboBoxStokes->insertItem( tr( "Single POL USB-130" ) );
    comboBoxBeams->clear();
    comboBoxBeams->insertItem( tr( "OFF" ) );
    comboBoxLta->clear();
    comboBoxLta->insertItem( tr( "32" ) );
    comboBoxLta->insertItem( tr( "16" ) );
    comboBoxLta->insertItem( tr( "8" ) );
    comboBoxLta->insertItem( tr( "4" ) );
    comboBoxLta->insertItem( tr( "2" ) );
    comboBoxLta->insertItem( tr( "1" ) );
    pushButtonOnline->setText( tr( "Control ONLINE" ) );
    radioButtonGain->setText( tr( "GAIN ON" ) );
    textLabelMode->setText( tr( "<p align=\"center\">MODE</p>" ) );
    textLabelLta->setText( tr( "<p align=\"center\">LTA</p>" ) );
    pushButtonQuit->setText( tr( "QUIT" ) );
    pushButtonQuit->setAccel( QKeySequence( tr( "Ctrl+Q" ) ) );
    pushButtonDefault->setText( tr( "DEFAULT" ) );
    pushButtonDefault->setAccel( QKeySequence( tr( "Ctrl+D" ) ) );
    pushButtonLoad->setText( tr( "LOAD" ) );
    pushButtonLoad->setAccel( QKeySequence( tr( "Ctrl+L" ) ) );
    pushButtonSave->setText( tr( "SAVE" ) );
    pushButtonSave->setAccel( QKeySequence( tr( "Ctrl+S" ) ) );
    comboBoxMode->clear();
    comboBoxMode->insertItem( tr( "REALTIME" ) );
    comboBoxMode->insertItem( tr( "RAWDUMP" ) );
    QToolTip::add( comboBoxMode, tr( "Select GPU mode." ) );
    radioButtonFstop->setText( tr( "FSTOP ON" ) );
    pushButtonDasConsole->setText( tr( "DAS CONSOLE" ) );
}

